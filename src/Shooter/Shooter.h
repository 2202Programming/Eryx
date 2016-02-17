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
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();

private:
	//Input from Xbox Controller
	void readXbox();
	void setPnumatics();
	void updateMotor1(); // w/ encoders
	void updateMotor2(); // w/o encoders
	void shoot();
	bool hasShot();

	bool runShoot; //True if shooting motors should be running
	bool runIntake;
	bool runTrigger;
	bool angle;
	bool intakePos;
	float leftSpeed, rightSpeed;
	bool shot;

	IXbox *xbox;
	Motor *motor;
	Compressor *c;
	DoubleSolenoid *angleSol;
	Solenoid *trigger;
	DoubleSolenoid *intakeSol;
	Encoder *encFrontLeft, *encFrontRight, *encBackLeft, *encBackRight; //Shooter Encoders
};

#endif /* SRC_SHOOTER_SHOOTER_H_ */
