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

	frontLeft = new Jaguar(MOTORFL);
	frontRight = new Jaguar(MOTORFR);
	backLeft = new Jaguar(MOTORBL);
	backRight = new Jaguar(MOTORBR);

	shootLeft = new Talon(5);
	shootRight = new Talon(6);

	encSR = new Encoder(0, 1);
	encSL = new Encoder(2, 3);

	rightSpeed = 0.0;
	leftSpeed = 0.0;
	sRightSpeed = 0.0;
	sLeftSpeed = 0.0;
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

	shootLeft->Set(sLeftSpeed);
	shootRight->Set(sRightSpeed);
}

void Motor::setDrive(float speedL, float speedR) {
	leftSpeed = speedL;
	rightSpeed = -speedR;
}

void Motor::setShoot(bool run) {
	if (run) {
		double rateR = encSR->GetRate();
		double rateL = encSL->GetRate();

		if (rateL > RPM) {
			sLeftSpeed = 1.0;
		} else {
			sLeftSpeed = 0.0;
		}

		if (rateR > RPM) {
			sRightSpeed = 1.0;
		} else {
			sRightSpeed = 0.0;
		}
	} else {
		sRightSpeed = 0.0;
		sLeftSpeed = 0.0;
	}
}

