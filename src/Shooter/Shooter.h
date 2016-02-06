/*
 * Shooter.h
 *
 *  Created on: Feb 5, 2016
 *      Author: Beast Laptop
 */

#include "WPILib.h"
#include "IControl.h"
#include "Motor/Motor.h"
#include "Xbox/MasterXboxController.h"

#ifndef SRC_SHOOTER_SHOOTER_H_
#define SRC_SHOOTER_SHOOTER_H_

class Shooter: public IControl {
public:
	Shooter(Motor *motor, MasterXboxController *xbox);
	virtual ~Shooter();
	void TeleopInit();
	void TeleopPeriod();
	void readXbox();

	bool runShoot;

	MasterXboxController *xbox;
	Motor *motor;

};

#endif /* SRC_SHOOTER_SHOOTER_H_ */
