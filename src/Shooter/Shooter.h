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

	//IControl
	void TeleopInit();
	void TeleopPeriodic();

private:
	//Input from Xbox Controller
	void readXbox();

	bool runShoot; //True if shooting motors should be running

	IXbox *xbox;
	Motor *motor;

};

#endif /* SRC_SHOOTER_SHOOTER_H_ */
