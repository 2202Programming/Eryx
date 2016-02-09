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
	//Shooter starts stopped
	motor->setShoot(false);
}

void Shooter::TeleopPeriodic() {
	readXbox();
	motor->setShoot(runShoot);

}

void Shooter::readXbox() {
	//Toggle - not hold
	if (xbox->getLeftBumperPressed()) { //Turn shooter on
		runShoot = true;
	} else if (xbox->getRightBumperPressed()) { //Turn shooter off
		runShoot = false;
	}
}
