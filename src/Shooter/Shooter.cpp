/*

 * Shooter.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Daniel Owen
 */

#include <Shooter/Shooter.h>

#define RPM 50
#define SOL_ACTIVATE DoubleSolenoid::kForward
#define SOL_DEACTIVATED DoubleSolenoid::kReverse

Shooter::Shooter(Motor *motor, IXbox *xbox, IProfile *p) {
	this->xbox = xbox;
	this->motor = motor;

	c = new Compressor();

	angleSol = new DoubleSolenoid(0, 1); //1
	trigger = new DoubleSolenoid(2, 3); //2
	intakeSol = new DoubleSolenoid(4, 5); //3

	encFrontLeft = new Encoder(10, 11);
	encFrontRight = new Encoder(12, 13);

	encFrontLeft->SetReverseDirection(true); //For test board
	encFrontRight->SetReverseDirection(true); //For test board
	encFrontLeft->SetDistancePerPulse(0.001);
	encFrontRight->SetDistancePerPulse(0.001);

	runShoot = false;
	runIntake = false;
	runTrigger = false;
	angle = false;
	intakePos = false;
	intakeDirection = false;
	shot = false;
	leftSpeed = 0.0;
	rightSpeed = 0.0;
	intakeSpeed = 0.0;
	shootRPM = 0.5;
	shootPercentState = 0;

	t = NULL;
	intakeT = NULL;
	time = false;

	sState = ready;
}

Shooter::~Shooter() {
	xbox = NULL;
	motor = NULL;
	c = NULL;
	delete c;
	t = NULL;
	delete t;
	angleSol = NULL;
	delete angleSol;
	trigger = NULL;
	delete trigger;
	intakeSol = NULL;
	delete intakeSol;
}

void Shooter::AutonomousInit() {
	motor->setShoot(0.0, 0.0);
	motor->setIntake(0.0);
	runShoot = false;

	c->Start();

	angleSol->Set(SOL_DEACTIVATED);
	angle = false;
	trigger->Set(SOL_DEACTIVATED);
	runTrigger = false;
	intakeSol->Set(SOL_DEACTIVATED);
	intakePos = false;
	intakeDirection = false;
}

void Shooter::AutonomousPeriodic() {
	updateMotor2();
	setPnumatics();
	motor->setShoot(leftSpeed, rightSpeed);

	/*if (encFrontLeft->GetRate() > RPM) {
	 runTrigger = true;
	 shot = true;
	 }*/
}

bool Shooter::shoot() {
	runShoot = true;
	angle = true;

	if (t == NULL) {
		t = new Timer();
		t->Start();
	}
	if (t->Get() > 2)
		runTrigger = true;

	if(runTrigger){
		delete t;
		t = NULL;
		return true;
	}
	return false;
}

bool Shooter::hasShot() {
	if (shot == true) {
		shot = false;
		return true;
	}

	return false;
}

void Shooter::TeleopInit() {
	motor->setShoot(0.0, 0.0);
	motor->setIntake(0.0);
	runShoot = false;

	c->Start();
	c->SetClosedLoopControl(true);

	angleSol->Set(SOL_DEACTIVATED);
	angle = false;
	trigger->Set(SOL_ACTIVATE);
	runTrigger = false;
	intakeSol->Set(SOL_DEACTIVATED);
	intakePos = false;
	intakeDirection = true;

	t = NULL;
	time = false;

	sState = ready;
	iState = closed;
}

void Shooter::TeleopPeriodic() {
	readXboxComp();
	updateMotor1();
	setPnumatics();

	switch (shootPercentState) {
	case 0:
		shootRPM = 0.40;
		break;
	case 1:
		shootRPM = 0.38;
		break;
	case 2:
		shootRPM = 0.35;
		break;
	case 3:
		shootRPM = 0.33;
		break;
	case 4:
		shootRPM = 0.30;
		break;
	}

	motor->setShoot(-leftSpeed, -rightSpeed);
	motor->setIntake(intakeSpeed);

	if (Global::telemetry >= 1) { //Normal
		SmartDashboard::PutNumber("Shoot Percent", shootRPM);
		SmartDashboard::PutNumber("Intake Speed", intakeSpeed);
		SmartDashboard::PutNumber("Shoot Left", leftSpeed);
		SmartDashboard::PutNumber("Shoot Right", rightSpeed);
		SmartDashboard::PutNumber("Shoot Enc Left", encFrontLeft->GetRate());
		SmartDashboard::PutNumber("Shoot Enc Right", encFrontRight->GetRate());
		SmartDashboard::PutBoolean("Angle", angle);
		SmartDashboard::PutBoolean("Trigger", trigger);
		SmartDashboard::PutBoolean("Intake", intakePos);
	} else if (Global::telemetry >= 2) { //debug

	} else if (Global::telemetry >= 3) { //advanced debug
		SmartDashboard::PutNumber("Shoot Percent State", shootPercentState);
		if (intakeDirection) {
			SmartDashboard::PutString("Intake Direction", "Forward");
		} else {
			SmartDashboard::PutString("Intake Direction", "Reverse");
		}
	}

	/* intakeSpeed = SmartDashboard::GetNumber("Intake Speed Change", 0.7);
	 if (intakeDirection) {
	 intakeSpeed = -intakeSpeed;
	 } */

	switch (sState) {
	case ready:
		SmartDashboard::PutString("Shoot State", "Ready");
		break;
	case windup:
		SmartDashboard::PutString("Shoot State", "Wind Up");
		break;
	case goShoot:
		SmartDashboard::PutString("Shoot State", "Go Shoot");
		break;
	case winddown:
		SmartDashboard::PutString("Shoot State", "Wind Down");
		break;
	}

}

void Shooter::readXbox() {
//Toggle - not hold
	if (xbox->getRightBumperPressed()) { //Turn shooter on/off
		runShoot = !runShoot;
	}

	if (xbox->getRightTriggerPressed()) { //Toggle trigger
		runTrigger = !runTrigger;
	}

	if (xbox->getR3Pressed()) { //Up
		angle = !angle;
	}

}

void Shooter::readXboxState() {
	if (xbox->getR3Pressed()) { //Up
		angle = !angle;
	}

	if (xbox->getLeftBumperHeld()) {
		runIntake = true;
	} else {
		runIntake = false;
	}

	if (xbox->getXPressed()) {
		intakeDirection = !intakeDirection;
	}

	if (xbox->getL3Pressed()) {
		intakePos = !intakePos;
	}

	switch (sState) {
	case ready:
		if (xbox->getRightTriggerPressed()) {
			sState = windup;
		}
		break;
	case windup:
		runShoot = true;

		if (t == NULL) {
			t = new Timer();
			t->Start();
		} else {
			if (t->Get() > 1) {
				time = true;
			}

			if (xbox->getRightTriggerPressed()) { //()
				sState = goShoot;
				time = false;
				delete t;
				t = NULL;
			}
			if (xbox->getRightBumperPressed()) {
				sState = winddown;
				time = false;
				delete t;
				t = NULL;
			}
			break;
			case goShoot:
			runTrigger = true;

			if (t == NULL) {
				t = new Timer();
				t->Start();
			} else {
				if (t->Get() > 1) {
					time = true;
				}
			}

			if (time) {
				sState = winddown;
				time = false;
				delete t;
				t = NULL;
			}

			break;
			case winddown:
			runShoot = false;
			runTrigger = false;

			if (t == NULL) {
				t = new Timer();
				t->Start();
			} else {
				if (t->Get() > 1) {
					time = true;
				}
			}

			if (time) {
				sState = ready;
				time = false;
				delete t;
				t = NULL;
			}
			break;
		}
	}

	if (xbox->getYPressed()) {
		if (shootPercentState < 4) {
			shootPercentState++;
		} else {
			shootPercentState = 0;
		}
	}
}

void Shooter::readXboxComp() {
	if (xbox->getRightBumperPressed()) { //Up
		angle = !angle;
	}


	if (xbox->getAPressed()) {
		intakeDirection = !intakeDirection;
	}

	if (xbox->getXPressed()) {
		if (shootPercentState < 4) {
			shootPercentState++;
		} else {
			shootPercentState = 0;
		}
	}

	switch (iState) {
	case open:
		intakePos = true;
		runIntake = true;
		if (xbox->getLeftTriggerPressed()) {
			iState = closing;
		}
		break;
	case closing:
		intakePos = false;
		if (intakeT == NULL) {
			intakeT = new Timer();
			intakeT->Start();
		} else {
			if (intakeT->Get() > 1.5) {
				runIntake = false;
				iState = closed;
				delete intakeT;
				intakeT = NULL;
			}
		}
		break;
	case closed:
		intakePos = false;
		runIntake = false;
		if (xbox->getLeftTriggerPressed()) {
			iState = open;
		}
		break;
	}

	if (xbox->getBackHeld()) {
		runIntake = !runIntake;
	}

	switch (sState) {
	case ready:
		if (xbox->getRightTriggerPressed()) {
			sState = windup;
		}
		break;
	case windup:
		runShoot = true;
		if (xbox->getRightTriggerPressed()) {
			sState = goShoot;
		}
		if (xbox->getBPressed()) {
			sState = winddown;
		}
		break;
	case goShoot:
		runTrigger = true;

		if (t == NULL) {
			t = new Timer();
			t->Start();
		} else {
			if (t->Get() > 1) {
				time = true;
			}
		}

		if (time) {
			sState = winddown;
			time = false;
			delete t;
			t = NULL;
		}

		break;
	case winddown:
		runShoot = false;
		runTrigger = false;

		if (t == NULL) {
			t = new Timer();
			t->Start();
		} else {
			if (t->Get() > 1) {
				time = true;
			}
		}

		if (time) {
			sState = ready;
			time = false;
			delete t;
			t = NULL;
		}
		break;
	}

}

void Shooter::setPnumatics() {

	if (angle) {
		angleSol->Set(SOL_ACTIVATE); //Up
	} else {
		angleSol->Set(SOL_DEACTIVATED); //Down
	}

	if (runTrigger) {
		trigger->Set(SOL_DEACTIVATED);	//In
	} else {
		trigger->Set(SOL_ACTIVATE);	//Out
	}

	if (intakePos) {
		intakeSol->Set(SOL_ACTIVATE);	//Out
	} else {
		intakeSol->Set(SOL_DEACTIVATED);	//In
	}
}

void Shooter::updateMotor1() {

	if (runShoot) {
		leftSpeed = acceleration(shootRPM, leftSpeed);
		rightSpeed = acceleration(shootRPM, rightSpeed);
	} else {
		leftSpeed = 0;
		rightSpeed = 0;
	}

	if (runIntake) {
		if (intakeDirection) {
			intakeSpeed = 0.7;
		} else {
			intakeSpeed = -0.7;
		}
	} else {
		intakeSpeed = 0.0;
	}

#if 0
	double rateR = encFrontRight->GetRate();
	double rateL = encFrontLeft->GetRate();

	if (runShoot) {
		pChangeLeft = (shootRPM - rateL) * pVal;
		pChangeRight = (shootRPM - rateR) * pVal;

		if (shootRPM - rateL > 0 && iAccumLeft < 0) {
			iAccumLeft = 0;
		}
		if (shootRPM - rateR > 0 && iAccumRight < 0) {
			iAccumRight = 0;
		}
		if (shootRPM - rateL < 0 && iAccumLeft > 0) {
			iAccumLeft = 0;
		}
		if (shootRPM - rateR < 0 && iAccumRight > 0) {
			iAccumRight = 0;
		}

		iAccumLeft += (shootRPM - rateL);
		iAccumRight += (shootRPM - rateR);
		iChangeLeft = iAccumLeft * iVal;
		iChangeRight = iAccumRight * iVal;

		leftSpeed = pChangeLeft + iChangeLeft;
		rightSpeed = pChangeRight + iChangeRight;
	} else {
		iAccumLeft = 0;
		iAccumRight = 0;

		leftSpeed = 0;
		rightSpeed = 0;
	}
#endif
}

void Shooter::updateMotor2() {
	//float appliedSpeed = SmartDashboard::GetNumber("ShooterSpeed", 1.0);
	if (runShoot) {
		leftSpeed = acceleration(shootRPM, leftSpeed);
		rightSpeed = acceleration(shootRPM, rightSpeed);
	} else {
		leftSpeed = 0.0;
		rightSpeed = 0.0;
	}

	if (runIntake) {
		if (intakeDirection) {
			intakeSpeed = 0.7;
		} else {
			intakeSpeed = -0.7;
		}
	} else {
		intakeSpeed = 0.0;
	}
}

float Shooter::acceleration(float newS, float oldS) {
	float accel = 0.0025;

	if (fabs(newS - oldS) > accel) {
		if (oldS > newS)
			return oldS - accel;
		else
			return oldS + accel;
	}

	return newS;
}
