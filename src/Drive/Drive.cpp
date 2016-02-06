/*
 * Drive.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: Beast
 */

#include "Drive/Drive.h"

Drive::Drive(IProfile *np, Motor *motor, IXbox *xbox) {
	profile = np;
	this->motor = motor;
	this->xbox = xbox;

	leftSpeed = 0.0;
	rightSpeed = 0.0;
}

Drive::~Drive() {
}

void Drive::TeleopInit() {
	motor->setDrive(0.0, 0.0);

	SmartDashboard::PutNumber("Accel", 0.1); //Curve Value

	motor->TeleopInit();
}
void Drive::TeleopPeriodic() {
	readXboxArcadeD();
	updateMotors();

	motor->TeleopPeriodic();
}
void Drive::readXboxTank() {
	leftSpeed = xbox->getAxisLeftY();
	rightSpeed = xbox->getAxisRightY();
}

void Drive::readXboxArcadeT() {
	float x = xbox->getAxisLeftX();
	float y = xbox->getAxisLeftY();

	SmartDashboard::PutNumber("X Value", x);
	SmartDashboard::PutNumber("Y Value", y);

	x *= .5;

	leftSpeed = y;
	rightSpeed = y;

	leftSpeed -= x;
	rightSpeed += x;
}

void Drive::readXboxArcadeD() {
	float x = xbox->getAxisLeftX();
	float y = xbox->getAxisLeftY();

	SmartDashboard::PutNumber("X Value", x);
	SmartDashboard::PutNumber("Y Value", y);

	if (y > 0) y *= y;
	else y *= -y;

	if (x > 0) x *= x;
	else x*= -x;

	leftSpeed = acceleration(y - x, leftSpeed);
	rightSpeed = acceleration(y + x, rightSpeed);

	SmartDashboard::PutNumber("XOut Value", rightSpeed);
	SmartDashboard::PutNumber("YOut Value", leftSpeed);
}

float Drive::acceleration(float newS, float oldS) {
	float accel = SmartDashboard::GetNumber("Accel", 0.0);

	if (fabs(newS - oldS) > accel) {
		if (oldS > newS)return oldS - accel;
		else return oldS + accel;
	}

	return newS;
}

void Drive::updateMotors() {
	motor->setDrive(leftSpeed, rightSpeed);
}

