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
#include "Profile/IProfile.h"

#ifndef SRC_SHOOTER_SHOOTER_H_
#define SRC_SHOOTER_SHOOTER_H_

class Shooter: public IControl {
public:
	Shooter(Motor *motor, IXbox *xbox, IProfile *p);
	virtual ~Shooter();

	//IControl
	void TeleopInit();
	void TeleopPeriodic();

private:
	//Input from Xbox Controller
	void readXbox();
	void setPnumatics();
	void updateMotor1(); // w/ encoders
	void updateMotor2(); // w/o encoders

	bool runShoot; //True if shooting motors should be running
	bool runIntake;
	bool runTrigger;
	bool angle;
	float leftSpeed, rightSpeed;

	IXbox *xbox;
	Motor *motor;
	Compressor *c;
	DoubleSolenoid *s1;
	DoubleSolenoid *trigger;
	Encoder *encFrontLeft, *encFrontRight, *encBackLeft, *encBackRight; //Shooter Encoders
};

#endif /* SRC_SHOOTER_SHOOTER_H_ */
