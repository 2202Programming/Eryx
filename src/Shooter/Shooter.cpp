/*

 * Shooter.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Daniel Owen
 */

#include <Shooter/Shooter.h>

#define RPM 2500
#define SOL_ACTIVATE DoubleSolenoid::kForward
#define SOL_DEACTIVATED DoubleSolenoid::kReverse

Shooter::Shooter(Motor *motor, IXbox *xbox, IProfile *p) {
	this->xbox = xbox;
	this->motor = motor;

	c = new Compressor();

	angleSol = new DoubleSolenoid(0, 1); //1
	trigger = new DoubleSolenoid(2, 3); //2
	intakeSol = new DoubleSolenoid(4, 5); //3

	/*
	 encFrontLeft = new Encoder(p->getInt("SHOOTERFL_ENC1"),
	 p->getInt("SHOOTERFL_ENC2"));
	 encFrontRight = new Encoder(p->getInt("SHOOTEFR_ENC1"),
	 p->getInt("SHOOTERLR_ENC2"));
	 encBackLeft = new Encoder(p->getInt("SHOOTERBL_ENC1"),
	 p->getInt("SHOOTERBL_ENC2"));
	 encBackRight = new Encoder(p->getInt("SHOOTERBR_ENC1"),
	 p->getInt("SHOOTERBR_ENC2"));
	 encFrontLeft->SetReverseDirection(p->getBool("SHOOTERFL_ENC1_INVERT")); //For test board
	 encFrontRight->SetReverseDirection(p->getBool("SHOOTERFR_ENC1_INVERT")); //For test board
	 encBackLeft->SetReverseDirection(p->getBool("SHOOTERBL_ENC1_INVERT")); //For test board
	 encBackRight->SetReverseDirection(p->getBool("SHOOTERBR_ENC1_INVERT")); //For test board */

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
	shootPercent = 0.5;
	shootPercentState = 0;

	t = NULL;
	time = false;

	sState = ready;
}

Shooter::~Shooter() {
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

void Shooter::shoot() {
	runShoot = true;
	angle = true;
}

bool Shooter::hasShot() {
	if (shot == true) {
		shot = false;
		return true;
	}

	return false;
}

void Shooter::TeleopInit() {
	SmartDashboard::PutNumber("ShooterSpeed", 1.0);
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
	intakeDirection = false;

	t = NULL;
	time = false;

	sState = ready;
}

void Shooter::TeleopPeriodic() {
	readXboxState();
	updateMotor2();
	setPnumatics();

	switch (shootPercentState) {
	case 0:
		shootPercent = 0.5;
		break;
	case 1:
		shootPercent = 0.45;
		break;
	case 2:
		shootPercent = 0.4;
		break;
	case 3:
		shootPercent = 0.3;
		break;
	}

	motor->setShoot(-leftSpeed, -rightSpeed);
	motor->setIntake(intakeSpeed);

	//Motors
	SmartDashboard::PutNumber("Shoot Left", leftSpeed);
	SmartDashboard::PutNumber("Shoot Right", rightSpeed);
	SmartDashboard::PutNumber("Intake Speed", intakeSpeed);
	SmartDashboard::PutNumber("Shoot Percent", shootPercent);
	SmartDashboard::PutNumber("Shoot Percent State", shootPercentState);

	if (intakeDirection) {
		SmartDashboard::PutBoolean("Intake Direction", "Forward");
	} else {
		SmartDashboard::PutBoolean("Intake Direction", "Reverse");
	}

	// Pistons
	SmartDashboard::PutBoolean("Angle", angle);
	SmartDashboard::PutBoolean("Trigger", trigger);
	SmartDashboard::PutBoolean("Intake", intakePos);

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

	if (xbox->getLeftBumperPressed()) {
		runIntake = !runIntake;
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
		}

		if (xbox->getRightTriggerPressed()) {
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

	if (xbox->getYPressed()) {
		if (shootPercentState < 3) {
			shootPercentState++;
		} else {
			shootPercentState = 0;
		}
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

void Shooter::updateMotor2() {
	//float appliedSpeed = SmartDashboard::GetNumber("ShooterSpeed", 1.0);
	if (runShoot) {
		leftSpeed = acceleration(shootPercent, leftSpeed);
		rightSpeed = acceleration(shootPercent, rightSpeed);
	} else {
		leftSpeed = 0.0;
		rightSpeed = 0.0;
	}

	if (runIntake) {
		if (intakeDirection) {
			intakeSpeed = 0.5;
		} else {
			intakeSpeed = -0.5;
		}
	} else {
		intakeSpeed = 0.0;
	}
}

float Shooter::acceleration(float newS, float oldS) {
	float accel = 0.005;

	if (fabs(newS - oldS) > accel) {
		if (oldS > newS)
			return oldS - accel;
		else
			return oldS + accel;
	}

	return newS;
}

/*void Shooter::updateMotor1() {
 double rateR = encFrontRight->GetRate();
 double rateL = encFrontLeft->GetRate();

 if (runShoot) {
 //Logic to keep the wheels within 150 of the desired RPM
 //Left side
 if (rateL < RPM) {
 if (rateL < RPM - 150)
 leftSpeed += 0.01;
 else
 leftSpeed += 0.005;

 } else if (rateL == RPM) {
 leftSpeed = 0.75;
 } else {
 if (rateL > RPM + 150)
 leftSpeed -= 0.01;
 else
 leftSpeed -= 0.005;
 }

 //Right Side
 if (rateR < RPM) {
 if (rateR < RPM - 150)
 rightSpeed += 0.01;
 else
 rightSpeed += 0.005;

 } else if (rateR == RPM) {
 rightSpeed = 0.75;
 } else {
 if (rateR > RPM + 150)
 rightSpeed -= 0.01;
 else
 rightSpeed -= 0.005;
 }
 } else {
 leftSpeed = 0.0;
 rightSpeed = 0.0;
 }
 } */
