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
	frontLeft = new Talon(3); //3 for tim - 1 for 2016
	frontRight = new Talon(1); //1 for tim - 2 for 2016
	backLeft = new Talon(4); //4 for tim - 3 for 2016
	backRight = new Talon(2); //2 for tim - 4 for 2016
	frontLeft->SetInverted(true); //true for tim - false for 2016
	backLeft->SetInverted(true); //true for tim - false for 2016

	//Shooter
	shootLeftF = new Talon(5);
	shootRightF = new Talon(6);
	shootLeftB = new Talon(7);
	shootRightB = new Talon(8);
	shootLeftF->SetInverted(true); //For test board
	shootLeftB->SetInverted(true); //For test board

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
	SmartDashboard::PutNumber("Left Motor", sRightSpeed);
	SmartDashboard::PutNumber("Right Motor", sLeftSpeed);
}

void Motor::setDrive(float speedL, float speedR) { //Called from drive class
	leftSpeed = speedL;
	rightSpeed = speedR; //For test bot
}

void Motor::setShoot1(bool run) { //Called from the shooter class

}

void Motor::setShoot2(bool run) {

}

void Motor::setArm(float aLowerSPeed, float aUpperSpeed) { //Called from the arm class
	this->aLowerSpeed = aLowerSpeed;
	this->aUpperSpeed = aUpperSpeed;
}

void Motor::setShoot(float speedL, float speedR){

}

