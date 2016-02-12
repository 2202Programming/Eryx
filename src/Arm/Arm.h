/*
 * Arm.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Daniel Owen
 */

#include "WPILib.h"
#include "IControl.h"
#include "Motor/Motor.h"
#include "Xbox/IXbox.h"

#ifndef SRC_ARM_ARM_H_
#define SRC_ARM_ARM_H_

class Arm: public IControl {
public:
	Arm(Motor *motor, IXbox *xbox);
	virtual ~Arm();

	//IControl
	void TeleopInit();
	void TeleopPeriodic();

private:
	//Gets inputs from the xbox Controller
	void readXbox();

	Motor *motor;
	IXbox *xbox;

	float lowerSpeed, upperSpeed;
};

#endif /* SRC_ARM_ARM_H_ */

