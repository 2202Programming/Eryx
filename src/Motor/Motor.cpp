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
	/*profile = np;
	 int MOTORFL = profile->getInt("MOTORFL");
	 int MOTORBL = profile->getInt("MOTORBL");
	 int MOTORFR = profile->getInt("MOTORFR");
	 int MOTORBR = profile->getInt("MOTORBR");

	 frontLeft = new Jaguar(MOTORFL);
	 frontRight = new Jaguar(MOTORFR);
	 backLeft = new Jaguar(MOTORBL);
	 backRight = new Jaguar(MOTORBR);*/

	shootLeft = new Talon(5);
	shootRight = new Talon(6);
	shootLeft->SetInverted(true);

	encSL = new Encoder(0, 1);
	encSR = new Encoder(2, 3);
	encSR->SetReverseDirection(true);
	encSL->SetReverseDirection(false);

	rightSpeed = 0.0;
	leftSpeed = 0.0;
	sRightSpeed = 0.0;
	sLeftSpeed = 0.0;
}

Motor::~Motor() {
}

void Motor::TeleopInit() {
	/*frontLeft->Set(0);
	 frontRight->Set(0);
	 backLeft->Set(0);
	 backRight->Set(0); */
}

void Motor::TeleopPeriodic() {
	SmartDashboard::PutNumber("Left Speed", leftSpeed);
	SmartDashboard::PutNumber("Right Speed", rightSpeed);

	/*frontLeft->Set(leftSpeed);
	 backLeft->Set(leftSpeed);
	 frontRight->Set(rightSpeed);
	 backRight->Set(rightSpeed);*/

	shootLeft->Set(sLeftSpeed);
	shootRight->Set(sRightSpeed);

	SmartDashboard::PutNumber("Left Speed", encSL->GetRate());
	SmartDashboard::PutNumber("Right Speed", encSR->GetRate());
	SmartDashboard::PutNumber("Left Motor", sRightSpeed);
	SmartDashboard::PutNumber("Right Motor", sLeftSpeed);
	SmartDashboard::PutNumber("Error", fabs(encSL->GetRate()- encSR->GetRate()));
}

void Motor::setDrive(float speedL, float speedR) {
	leftSpeed = speedL;
	rightSpeed = -speedR;
}

void Motor::setShoot(bool run) {
	double rateR = encSR->GetRate();
	double rateL = encSL->GetRate();

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

