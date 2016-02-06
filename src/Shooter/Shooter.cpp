/*
 * Shooter.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Beast Laptop
 */

#include <Shooter/Shooter.h>

Shooter::Shooter(MasterXboxController *xbox, Motor *motor) {
		this->xbox = xbox;
		this->motor = motor;
		runShoot = false;
}

Shooter::~Shooter() {
}

void Shooter::TeleopInit() {
	motor->setShoot(false);
}

void Shooter::TeleopPeriod() {
	readXbox();
	motor->setShoot(runShoot);

}

void Shooter::readXbox() {
	if (xbox->isXHeld()) {
		runShoot = true;
	} else if (xbox->isBHeld()) {
		runShoot = false;
	}
}
