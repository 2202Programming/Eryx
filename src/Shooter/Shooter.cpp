/*
 * Shooter.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Daniel Owen
 */

#include <Shooter/Shooter.h>

#define RPM 2500

Shooter::Shooter(Motor *motor, IXbox *xbox, IProfile *p) {
	this->xbox = xbox;
	this->motor = motor;
	c = new Compressor();
	s1 = new DoubleSolenoid(p->getInt("SHOOTER_SOL1_1"),
			p->getInt("SHOOTER_SOL1_2"));
	trigger = new DoubleSolenoid(p->getInt("SHOOTER_SOL2_1"),
			p->getInt("SHOOTER_SOL2_2"));
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
	encBackRight->SetReverseDirection(p->getBool("SHOOTERBR_ENC1_INVERT")); //For test board

	runShoot = false;
	runIntake = false;
	runTrigger = false;
	angle = false;
	shot = false;
	leftSpeed = 0.0;
	rightSpeed = 0.0;

}

Shooter::~Shooter() {
}

void Shooter::AutonomousInit() {
	angle = true;
}

void Shooter::AutonomousPeriodic() {
	updateMotor2();
	setPnumatics();
	motor->setShoot(leftSpeed, rightSpeed);

	if (encFrontLeft->GetRate() > RPM) {
		runTrigger = true;
		shot = true;
	}
}

void Shooter::shoot() {
	runShoot = true;
}

bool Shooter::hasShot() {
	if (shot == true) {
		shot = false;
		return true;
	}

	return false;
}

void Shooter::TeleopInit() {
	//Shooter starts stopped
	motor->setShoot(0.0, 0.0);
	runShoot = false;
	c->Start();
	s1->Set(s1->kReverse);
	angle = false;
	trigger->Set(trigger->kForward);
	runTrigger = false;
}

void Shooter::TeleopPeriodic() {
	readXbox();
	updateMotor2();
	setPnumatics();

	motor->setShoot(leftSpeed, rightSpeed);

	if (runIntake) {
		motor->setIntake(1.0);
	} else {
		motor->setIntake(0.0);
	}

	SmartDashboard::PutNumber("Left Shoot Speed", encFrontLeft->GetRate());
	SmartDashboard::PutNumber("Right Shoot Speed", encFrontRight->GetRate());
	SmartDashboard::PutNumber("Left Shoot Speed", encBackLeft->GetRate());
	SmartDashboard::PutNumber("Right Shoot Speed", encBackRight->GetRate());
}

void Shooter::readXbox() {
	//Toggle - not hold
	if (xbox->getR3Pressed()) { //Turn shooter on/off
		runShoot = !runShoot;
	}

	if (xbox->getRightTriggerPressed()) { //Toggle trigger
		runTrigger = !runTrigger;
	}

	if (xbox->getRightBumperHeld()) { //Up
		angle = true;
	} else if (xbox->getLeftBumperHeld()) { //Down
		angle = false;
	}

	if (xbox->getBackHeld()) {
		runIntake = true;
	} else {
		runIntake = false;
	}
}

void Shooter::setPnumatics() {

	if (angle) {
		s1->Set(s1->kForward); //Up
	} else {
		s1->Set(s1->kReverse); //Down
	}

	if (runTrigger) {
		trigger->Set(trigger->kForward);
	} else {
		trigger->Set(trigger->kReverse);
	}
}

void Shooter::updateMotor1() {
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
}

void Shooter::updateMotor2() {
	if (runShoot) {
		leftSpeed = 1.0;
		rightSpeed = 1.0;
	} else {
		leftSpeed = 0.0;
		rightSpeed = 0.0;
	}
}
