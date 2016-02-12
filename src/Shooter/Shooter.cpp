/*
 * Shooter.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Daniel Owen
 */

#include <Shooter/Shooter.h>

#define RPM 2500

Shooter::Shooter(Motor *motor, IXbox *xbox) {
	this->xbox = xbox;
	this->motor = motor;
	c = new Compressor();
	s1 = new DoubleSolenoid(0, 1);
	s2 = new DoubleSolenoid(2, 3);
	runShoot = false;
	angle = 0;
	leftSpeed = 0.0;
	rightSpeed = 0.0;

	encSLF = new Encoder(0, 1);
	encSRF = new Encoder(2, 3);
	encSLB = new Encoder(4, 5);
	encSRB = new Encoder(6, 7);
	encSLF->SetReverseDirection(false); //For test board
	encSRF->SetReverseDirection(true); //For test board
	encSLB->SetReverseDirection(false); //For test board
	encSRB->SetReverseDirection(true); //For test board
}

Shooter::~Shooter() {
}

void Shooter::TeleopInit() {
	//Shooter starts stopped
	motor->setShoot(0.0, 0.0);
	c->Start();
	s1->Set(s1->kForward);
	s2->Set(s2->kForward);
}

void Shooter::TeleopPeriodic() {
	readXbox();
	motor->setShoot2(runShoot);
	updateMotor2();
	setAngle();
	motor->setShoot(leftSpeed, rightSpeed);

	SmartDashboard::PutNumber("Left Shoot Speed", encSLF->GetRate());
	SmartDashboard::PutNumber("Right Shoot Speed", encSRF->GetRate());
	SmartDashboard::PutNumber("Left Shoot Speed", encSLB->GetRate());
	SmartDashboard::PutNumber("Right Shoot Speed", encSRB->GetRate());
}

void Shooter::readXbox() {
	//Toggle - not hold
	if (xbox->getRightTriggerHeld()) { //Turn shooter on
		runShoot = true;
	} else { //Turn shooter off
		runShoot = false;
	}

	if (xbox->getRightBumperHeld() && angle <= 3) {
		angle++;
	} else if (xbox->getLeftBumperHeld() && angle >= 0) {
		angle--;
	}
}

void Shooter::setAngle() {
	switch (angle) {
	case 0: // Down
		s1->Set(s1->kForward);
		s2->Set(s2->kForward);
		break;
	case 1: // angle 1
		s1->Set(s1->kReverse);
		s2->Set(s2->kForward);
		break;
	case 2: //angle 2
		s1->Set(s1->kForward);
		s2->Set(s2->kReverse);
		break;
	case 3: //angle 3
		s1->Set(s1->kReverse);
		s2->Set(s2->kReverse);
		break;

	}
}

void Shooter::updateMotor1() {
	double rateR = encSRF->GetRate();
	double rateL = encSLF->GetRate();

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
}

void Shooter::updateMotor2() {
	leftSpeed = 0.75;
	rightSpeed = 0.75;
}
