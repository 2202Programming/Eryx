/*
 * Motor.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: Beast
 */

#include <Motor/Motor.h>

#define SHOOTSPEED 1.0
#define RPM 2500

Motor::Motor(IProfile *np) {
	profile = np;
	int MOTORFL = profile->getInt("MOTORFL");
	int MOTORBL = profile->getInt("MOTORBL");
	int MOTORFR = profile->getInt("MOTORFR");
	int MOTORBR = profile->getInt("MOTORBR");

	//Drive
	frontLeft = new Talon(MOTORFL);
	frontRight = new Talon(MOTORFR);
	backLeft = new Talon(MOTORBL);
	backRight = new Talon(MOTORBR);

	//Shooter
	shootLeft = new Talon(5);
	shootRight = new Talon(6);
	shootLeft->SetInverted(true); //For test board
	encSL = new Encoder(0, 1);
	encSR = new Encoder(2, 3);
	encSL->SetReverseDirection(false); //For test board
	encSR->SetReverseDirection(true); //For test board

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
	shootLeft->Set(0.0);
	shootRight->Set(0.0);

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
	shootLeft->Set(sLeftSpeed);
	shootRight->Set(sRightSpeed);

	//Arm
	armLower->Set(aLowerSpeed);
	armUpper->Set(aUpperSpeed);

	//Date Feeds
	SmartDashboard::PutNumber("Left Speed", leftSpeed);
	SmartDashboard::PutNumber("Right Speed", rightSpeed);
	SmartDashboard::PutNumber("Left Shoot Speed", encSL->GetRate());
	SmartDashboard::PutNumber("Right Shoot Speed", encSR->GetRate());
	SmartDashboard::PutNumber("Left Motor", sRightSpeed);
	SmartDashboard::PutNumber("Right Motor", sLeftSpeed);
	SmartDashboard::PutNumber("Error",
			fabs(encSL->GetRate() - encSR->GetRate()));
}

void Motor::setDrive(float speedL, float speedR) { //Called from drive class
	leftSpeed = speedL;
	rightSpeed = -speedR; //For test bot
}

void Motor::setShoot(bool run) { //Called from the shooter class
	double rateR = encSR->GetRate();
	double rateL = encSL->GetRate();

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

void Motor::setArm(float aLowerSPeed, float aUpperSpeed) { //Called from the arm class
	this->aLowerSpeed = aLowerSpeed;
	this->aUpperSpeed = aUpperSpeed;
}

