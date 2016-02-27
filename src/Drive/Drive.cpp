/*
 * Drive.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: Daniel Owen
 */

#include "Drive/Drive.h"

Drive::Drive(Motor *motor, IXbox *xbox, ISensorControl *nav) {
	this->motor = motor;
	this->xbox = xbox;
	this->nav = nav;

	navSpeed = NULL;

	//init floats, state, and userControl
	leftSpeed = 0.0;
	rightSpeed = 0.0;
	state = nav->running;
	requestedState = nav->running;
	userControl = false;

	left = new Encoder(2, 3);
	right = new Encoder(4, 5);
	left2 = new Encoder(6, 7);
	right2 = new Encoder(0, 1);
}

Drive::~Drive() {
	motor = NULL;
	xbox = NULL;
	nav = NULL;
	navSpeed = NULL;
	delete navSpeed;
	left = NULL;
	delete left;
	left2 = NULL;
	delete left2;
	right = NULL;
	delete right;
	right2 = NULL;
	delete right2;
}

void Drive::AutonomousInit() {
	requestedState = nav->stopped;
	state = nav->stopped;
}

void Drive::AutonomousPeriodic() {
	navSpeed = nav->UpdateMotorSpeeds(0.0, 0.0);
	updateMotors();
}

void Drive::TeleopInit() {
	motor->setDrive(0.0, 0.0);

	SmartDashboard::PutNumber("Accel", 0.1); //Acceleration curve Value 0.1 - 0.05 is good

	userControl = true; //Start with user control
	state = nav->running;
	requestedState = nav->running;
}

void Drive::TeleopPeriodic() {
	requestedState = nav->DriveSystemControlUpdate(state, nav->running); //Nav returns state to go to
	readXboxArcadeD();
	navSpeed = nav->UpdateMotorSpeeds(leftSpeed, rightSpeed); //nav returns speed it wants (corrected or wehen nav is controlling)
	updateMotors();

	SmartDashboard::PutNumber("Left Raw", left->Get());
	SmartDashboard::PutNumber("Right RAW", right->Get());
	SmartDashboard::PutNumber("Left2 Raw", left2->Get());
	SmartDashboard::PutNumber("Right2 RAW", right2->Get());
}

void Drive::readXboxTank() { //Tank drive - 2 sticks
	leftSpeed = xbox->getAxisLeftY();
	rightSpeed = xbox->getAxisRightY();
}

void Drive::readXboxArcadeT() { // Doesn't work with NAV right now
	float x, y;

	x = xbox->getAxisLeftX();
	y = xbox->getAxisLeftY();

	//SmartDashboard::PutNumber("X Value", x);
	//SmartDashboard::PutNumber("Y Value", y);

	x *= .5;

	leftSpeed = y;
	rightSpeed = y;

	leftSpeed -= x;
	rightSpeed += x;
}

void Drive::readXboxArcadeD() {
	float x, y;

	if (requestedState == nav->running) { //When the state is running xbox controls other wise start to stop
		x = xbox->getAxisLeftX();
		y = xbox->getAxisLeftY();
		userControl = true;
	} else {
		x = 0.0;
		y = 0.0;
	}
	//SmartDashboard::PutNumber("X Value", x);
	//SmartDashboard::PutNumber("Y Value", y);

	//x*x + y*y is >= 1
	if (y > 0)
		y *= y;
	else
		y *= -y;

	if (x > 0)
		x *= x;
	else
		x *= -x;

	// For Nav states
	if (requestedState == nav->stopped) {
		if (!(fabs(leftSpeed) <= 0.05 && fabs(rightSpeed) <= 0.05)
				&& userControl) {
			state = nav->stopping;
		} else {
			state = nav->stopped;
			userControl = false;
		}
	} else
		state = nav->running;

	if (state == nav->running || state == nav->stopping) { //If running or stopping update speeds here
		leftSpeed = acceleration(y + x, leftSpeed);
		rightSpeed = acceleration(y - x, rightSpeed);
	}

	//SmartDashboard::PutNumber("RightOut Value", rightSpeed);
	//SmartDashboard::PutNumber("LeftOut Value", leftSpeed);
}
//Compare requested speed with last speed, if difference greater than accel value only change by accel value
float Drive::acceleration(float newS, float oldS) {
	float accel = SmartDashboard::GetNumber("Accel", 0.0);

	if (fabs(newS - oldS) > accel) {
		if (oldS > newS)
			return oldS - accel;
		else
			return oldS + accel;
	}

	return newS;
}

void Drive::updateMotors() {
	if (requestedState == nav->stopped && state == nav->stopped) { //Update speeds here if nav is controlling
		leftSpeed = navSpeed->leftMotorSpeed;
		rightSpeed = navSpeed->rightMotorSpeed;
		SmartDashboard::PutBoolean("Nav", true);
	}

	//Update motors
	motor->setDrive(leftSpeed, rightSpeed);
}

