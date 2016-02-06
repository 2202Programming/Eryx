/*
 * Shooter.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Beast Laptop
 */

#include <Shooter/Shooter.h>

Shooter::Shooter(Motor *motor, IXbox *xbox) {
		this->xbox = xbox;
		this->motor = motor;
		runShoot = false;
}

Shooter::~Shooter() {
}

void Shooter::TeleopInit() {
	motor->setShoot(false);
}

void Shooter::TeleopPeriodic() {
	readXbox();
	motor->setShoot(runShoot);

}

void Shooter::readXbox() {
	if (xbox->getXHeld()) {
		runShoot = true;
	} else if (xbox->getBHeld()) {
		runShoot = false;
	}
}
