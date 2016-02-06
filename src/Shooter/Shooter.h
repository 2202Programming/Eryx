/*
 * Shooter.h
 *
 *  Created on: Feb 5, 2016
 *      Author: Beast Laptop
 */

#include "WPILib.h"
#include "IControl.h"
#include "Motor/Motor.h"
#include "Xbox/IXbox.h"

#ifndef SRC_SHOOTER_SHOOTER_H_
#define SRC_SHOOTER_SHOOTER_H_

class Shooter: public IControl {
public:
	Shooter(Motor *motor, IXbox *xbox);
	virtual ~Shooter();
	void TeleopInit();
	void TeleopPeriodic();
	void readXbox();

	bool runShoot;

	IXbox *xbox;
	Motor *motor;

};

#endif /* SRC_SHOOTER_SHOOTER_H_ */
