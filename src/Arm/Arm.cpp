/*
 * Arm.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Beast
 */

#include <Arm/Arm.h>

Arm::Arm(Motor *motor, IXbox *xbox) {
	this->motor = motor;
	this->xbox = xbox;

	//init floats
	upperSpeed = 0.0;
	lowerSpeed = 0.0;
}

Arm::~Arm() {
}

void Arm::TeleopInit() {
	//Init Motors
	motor->setArm(0.0, 0.0);
}

void Arm::TeleopPeriodic() {
	readXbox();
	motor->setArm(lowerSpeed, upperSpeed); //Set motor speeds
}

void Arm::readXbox() {
	//Lower arm
	if (xbox->getXHeld()) {
		lowerSpeed = 1.0; //Move Back
	} else if (xbox->getBHeld()) {
		lowerSpeed = -1.0; //Move forward
	} else {
		lowerSpeed = 0.0;
	}

	//Upper arm
	if (xbox->getAHeld()) {
		upperSpeed = 1.0; //Move Back
	} else if (xbox->getYHeld()) {
		upperSpeed = -1.0; //Move forward
	} else {
		upperSpeed = 0.0;
	}
}
