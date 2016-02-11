/*
 * Shooter.h
 *
 *  Created on: Feb 5, 2016
 *      Author: Daniel Owen
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
	void setAngle();
	void updateMotor1();
	void updateMotor2();

	bool runShoot; //True if shooting motors should be running
	int angle;
	float leftSpeed, rightSpeed;

	IXbox *xbox;
	Motor *motor;
	Compressor *c;
	DoubleSolenoid *s1, *s2;
	Encoder *encSLF, *encSRF, *encSLB, *encSRB; //Shooter Encoders
};

#endif /* SRC_SHOOTER_SHOOTER_H_ */
