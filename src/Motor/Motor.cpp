/*
 * Motor.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: Beast
 */

#include <Motor/Motor.h>

Motor::Motor(IProfile *np) {
	profile = np;
	int MOTORFL = profile->getInt("MOTORFL");
	int MOTORBL = profile->getInt("MOTORBL");
	int MOTORFR = profile->getInt("MOTORFR");
	int MOTORBR = profile->getInt("MOTORBR");

	frontLeft = new Jaguar(MOTORFL);
	frontRight = new Jaguar(MOTORFR);
	backLeft = new Jaguar(MOTORBL);
	backRight = new Jaguar(MOTORBR);

	rightSpeed = 0.0;
	leftSpeed = 0.0;
}

Motor::~Motor() {
}

void Motor::TeleopInit() {
	frontLeft->Set(0);
	frontRight->Set(0);
	backLeft->Set(0);
	backRight->Set(0);
}

void Motor::TeleopPeriodic() {
	SmartDashboard::PutNumber("Left Speed", leftSpeed);
	SmartDashboard::PutNumber("Right Speed", rightSpeed);

	frontLeft->Set(leftSpeed);
	backLeft->Set(leftSpeed);
	frontRight->Set(rightSpeed);
	backRight->Set(rightSpeed);
}

void Motor::setDrive(float speedL, float speedR) {
	leftSpeed = speedL;
	rightSpeed = -speedR;
}

