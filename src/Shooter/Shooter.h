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
	void readXboxState();
	void readXboxComp(); // Lukas and Aaron layout
	void setPnumatics();
	void updateMotor1(); // w/ encoders
	void updateMotor2(); // w/o encoders
	void shoot();
	bool hasShot();
	float acceleration(float newS, float oldS);

	bool runShoot; //True if shooting motors should be running
	bool runIntake;
	bool intakeDirection;
	bool runTrigger;
	bool angle;
	bool intakePos;
	float leftSpeed, rightSpeed;
	int shootPercentState; // 0 is 1.0, 1 is 0.5, 2 is 0.2
	float shootPercent;
	float intakeSpeed;
	bool shot;
	bool time;

	enum shootState {
		ready,
		windup,
		goShoot,
		winddown
	};
	shootState sState;

	IXbox *xbox;
	Motor *motor;
	Compressor *c;
	Timer *t;
	DoubleSolenoid *angleSol;
	DoubleSolenoid *trigger;
	DoubleSolenoid *intakeSol;
	Encoder *encFrontLeft, *encFrontRight, *encBackLeft, *encBackRight; //Shooter Encoders
};

#endif /* SRC_SHOOTER_SHOOTER_H_ */
