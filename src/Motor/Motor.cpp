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
	frontLeft = new Jaguar(np->getInt("DRIVEFL"));
	frontRight = new Jaguar(np->getInt("DRIVEFR"));
	backLeft = new Jaguar(np->getInt("DRIVEBL"));
	backRight = new Jaguar(np->getInt("DRIVEBR"));
	frontLeft->SetInverted(np->getBool("DRIVEFL_INVERT"));
	frontRight->SetInverted(np->getBool("DRIVEFR_INVERT"));
	backLeft->SetInverted(np->getBool("DRIVEBL_INVERT"));
	backRight->SetInverted(np->getBool("DRIVEBR_INVERT"));

	//Shooter
	shootFrontLeft = new Talon(np->getInt("SHOOTFL"));
	shootFrontRight = new Talon(np->getInt("SHOOTFR"));
	shootBackLeft = new Talon(np->getInt("SHOOTBL"));
	shootBackRight = new Talon(np->getInt("SHOOTBR"));

	//Arm
	armLower = new Talon(np->getInt("ARM_LOWER"));
	armUpper = new Talon(np->getInt("ARM_UPPER"));
	encArmLower = new Encoder(np->getInt("ARM_LOWER_ENC1"),
			np->getInt("ARM_LOWER_ENC2"));
	encArmUpper = new Encoder(np->getInt("ARM_UPPER_ENC1"),
			np->getInt("ARM_UPPER_ENC2"));

	//Intake
	intake = new Talon(np->getInt("INTAKE"));

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
}

void Motor::TeleopInit() {
	//Drive
	frontLeft->Set(0);
	frontRight->Set(0);
	backLeft->Set(0);
	backRight->Set(0);

	//Shooter
	shootFrontLeft->Set(0.0);
	shootFrontRight->Set(0.0);
	shootBackLeft->Set(0.0);
	shootBackRight->Set(0.0);

	//Arm
	armLower->Set(0.0);
	armUpper->Set(0.0);
	intake->Set(0.0);
}

void Motor::TeleopPeriodic() { //Update all motors every loop
	//Drive
	frontLeft->Set(leftSpeed);
	backLeft->Set(leftSpeed);
	frontRight->Set(rightSpeed);
	backRight->Set(rightSpeed);

	//Shooter
	shootFrontLeft->Set(sLeftSpeed);
	shootFrontRight->Set(sRightSpeed);
	shootBackLeft->Set(sLeftSpeed);
	shootBackRight->Set(sRightSpeed);

	//Arm
	armLower->Set(aLowerSpeed);
	armUpper->Set(aUpperSpeed);

	//Intake
	intake->Set(intakeSpeed);

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

void Motor::setShoot(float speedL, float speedR) { //Called from the shooter class
	sLeftSpeed = speedL;
	sRightSpeed = speedR;
}

void Motor::setArm(float aLowerSPeed, float aUpperSpeed) { //Called from the arm class
	this->aLowerSpeed = aLowerSpeed;
	this->aUpperSpeed = aUpperSpeed;
}

void Motor::setIntake(float intakeSpeed) {
	this->intakeSpeed = intakeSpeed;
}
