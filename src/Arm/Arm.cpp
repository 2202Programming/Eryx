/*
 * Arm.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Daniel Owen
 */

#include <Arm/Arm.h>

Arm::Arm(Motor *motor, IXbox *xbox) {
	this->motor = motor;
	this->xbox = xbox;

	armSol = new DoubleSolenoid(6,7);

	//init floats
	upperSpeed = 0.0;
	lowerSpeed = 0.0;
	armPos = false;
}

Arm::~Arm() {

}

void Arm::TeleopInit() {
	//Init Motors
	motor->setArm(0.0);
	armSol->Set(DoubleSolenoid::kReverse);
}

void Arm::TeleopPeriodic() {
	readXbox();
	motor->setArm(lowerSpeed); //Set motor speeds

	if (armPos) {
		armSol->Set(DoubleSolenoid::kForward);
	} else {
		armSol->Set(DoubleSolenoid::kReverse);
	}
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

	if (xbox->getAPressed()) {
		armPos = !armPos;
	}
}

