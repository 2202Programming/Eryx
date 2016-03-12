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

	//Drive
	frontLeft = new Spark(2);
	frontRight = new Spark(4);
	backLeft = new Spark(1);
	backRight = new Spark(3);

	//Shooter
	shootLeft = new Spark(6);
	shootRight = new Spark(7);

	//Arm
	armLower = new Spark(8);

	//Intake
	intake = new Spark(5);

	//Init Floats
	leftSpeed = 0.0;
	rightSpeed = 0.0;
	sLeftSpeed = 0.0;
	sRightSpeed = 0.0;
	aLowerSpeed = 0.0;
	aUpperSpeed = 0.0;
	intakeSpeed = 0.0;
}

Motor::~Motor() {
	frontLeft = NULL;
	delete frontLeft;
	frontRight = NULL;
	delete frontRight;
	backLeft = NULL;
	delete backLeft;
	backRight = NULL;
	delete backRight;
	shootLeft = NULL;
	delete shootLeft;
	shootRight = NULL;
	delete shootRight;
	armLower = NULL;
	delete armLower;
	intake = NULL;
	delete intake;

}

void Motor::AutonomousInit() {
	frontLeft->Set(0);
	frontRight->Set(0);
	backLeft->Set(0);
	backRight->Set(0);

	//Shooter
	shootLeft->Set(0.0);
	shootRight->Set(0.0);

	//Arm
	armLower->Set(0.0);
	//armUpper->Set(0.0);
	intake->Set(0.0);
}

void Motor::AutonomousPeriodic() {
	//Drive
	frontLeft->Set(-leftSpeed);
	backLeft->Set(-leftSpeed);
	frontRight->Set(rightSpeed);
	backRight->Set(rightSpeed);

	//Shooter
	shootLeft->Set(sLeftSpeed);
	shootRight->Set(sRightSpeed);

	//Arm
	armLower->Set(aLowerSpeed);

	//Intake
	intake->Set(intakeSpeed);
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
	intake->Set(0.0);
}

void Motor::TeleopPeriodic() { //Update all motors every loop
	//Drive
	frontLeft->Set(-leftSpeed);
	backLeft->Set(-leftSpeed);
	frontRight->Set(rightSpeed);
	backRight->Set(rightSpeed);

	//Shooter
	shootLeft->Set(sLeftSpeed);
	shootRight->Set(sRightSpeed);

	//Arm
	armLower->Set(aLowerSpeed);

	//Intake
	intake->Set(intakeSpeed);
}

void Motor::setDrive(float speedL, float speedR) { //Called from drive class
	leftSpeed = speedL;
	rightSpeed = speedR; //For test bot
}

void Motor::setShoot(float speedL, float speedR) { //Called from the shooter class
	sLeftSpeed = speedL;
	sRightSpeed = speedR;

	if (sLeftSpeed > 0.6) {
		sLeftSpeed = 0.6;
	}

	if (sRightSpeed > 0.6) {
		sRightSpeed = 0.6;
	}

}

void Motor::setArm(float armSpeed) { //Called from the arm class
	this->aLowerSpeed = armSpeed;
}

void Motor::setIntake(float intakeSpeed) {
	this->intakeSpeed = intakeSpeed;
}
