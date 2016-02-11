/*
 * Motor.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: Daniel Owen
 */

#include <Motor/Motor.h>

#define SHOOTSPEED 1.0
#define RPM 2500

Motor::Motor(IProfile *np) {
	profile = np;

	//Drive
	frontLeft = new Talon(1);
	frontRight = new Talon(2);
	backLeft = new Talon(3);
	backRight = new Talon(4);

	//Shooter
	shootLeftF = new Talon(5);
	shootRightF = new Talon(6);
	shootLeftB = new Talon(7);
	shootRightB = new Talon(8);
	shootLeftF->SetInverted(true); //For test board
	shootLeftB->SetInverted(true); //For test board
	encSLF = new Encoder(0, 1);
	encSRF = new Encoder(2, 3);
	encSLB = new Encoder(4, 5);
	encSRB = new Encoder(6, 7);
	encSLF->SetReverseDirection(false); //For test board
	encSRF->SetReverseDirection(true); //For test board
	encSLB->SetReverseDirection(false); //For test board
	encSRB->SetReverseDirection(true); //For test board

	//Arm
	armLower = new Talon(7);
	armUpper = new Talon(8);
	encALower = new Encoder(4, 5);
	encAUpper = new Encoder(6, 7);

	//Init Floats
	leftSpeed = 0.0;
	rightSpeed = 0.0;
	sLeftSpeed = 0.0;
	sRightSpeed = 0.0;
	aLowerSpeed = 0.0;
	aUpperSpeed = 0.0;
}

Motor::~Motor() {
}

void Motor::TeleopInit() {
	//Drive
	frontLeft->Set(0);
	frontRight->Set(0);
	backLeft->Set(0);
	backRight->Set(0);

	//Shooter
	shootLeftF->Set(0.0);
	shootRightF->Set(0.0);
	shootLeftB->Set(0.0);
	shootRightB->Set(0.0);

	//Arm
	armLower->Set(0.0);
	armUpper->Set(0.0);
}

void Motor::TeleopPeriodic() { //Update all motors every loop
	//Drive
	frontLeft->Set(leftSpeed);
	backLeft->Set(leftSpeed);
	frontRight->Set(rightSpeed);
	backRight->Set(rightSpeed);

	//Shooter
	shootLeftF->Set(sLeftSpeed);
	shootRightF->Set(sRightSpeed);
	shootLeftB->Set(sLeftSpeed);
	shootRightB->Set(sRightSpeed);

	//Arm
	armLower->Set(aLowerSpeed);
	armUpper->Set(aUpperSpeed);

	//Date Feeds
	SmartDashboard::PutNumber("Left Speed", leftSpeed);
	SmartDashboard::PutNumber("Right Speed", rightSpeed);
	SmartDashboard::PutNumber("Left Shoot Speed", encSLF->GetRate());
	SmartDashboard::PutNumber("Right Shoot Speed", encSRF->GetRate());
	SmartDashboard::PutNumber("Left Shoot Speed", encSLB->GetRate());
	SmartDashboard::PutNumber("Right Shoot Speed", encSRB->GetRate());
	SmartDashboard::PutNumber("Left Motor", sRightSpeed);
	SmartDashboard::PutNumber("Right Motor", sLeftSpeed);
}

void Motor::setDrive(float speedL, float speedR) { //Called from drive class
	leftSpeed = speedL;
	rightSpeed = -speedR; //For test bot
}

void Motor::setShoot1(bool run) { //Called from the shooter class
	double rateR = encSRF->GetRate();
	double rateL = encSLF->GetRate();

	//Logic to keep the wheels within 150 of the desired RPM
	//Left side
	if (rateL < RPM) {
		if (rateL < RPM - 150)
			sLeftSpeed += 0.01;
		else
			sLeftSpeed += 0.005;

	} else if (rateL == RPM) {
		sLeftSpeed = 0.75;
	} else {
		if (rateL > RPM + 150)
			sLeftSpeed -= 0.01;
		else
			sLeftSpeed -= 0.005;
	}

	//Right Side
	if (rateR < RPM) {
		if (rateR < RPM - 150)
			sRightSpeed += 0.01;
		else
			sRightSpeed += 0.005;

	} else if (rateR == RPM) {
		sRightSpeed = 0.75;
	} else {
		if (rateR > RPM + 150)
			sRightSpeed -= 0.01;
		else
			sRightSpeed -= 0.005;
	}
}

void Motor::setShoot2(bool run) {
	sLeftSpeed = 0.75;
	sRightSpeed = 0.75;
}

void Motor::setArm(float aLowerSPeed, float aUpperSpeed) { //Called from the arm class
	this->aLowerSpeed = aLowerSpeed;
	this->aUpperSpeed = aUpperSpeed;
}

