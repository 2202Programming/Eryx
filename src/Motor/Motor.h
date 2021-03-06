/*
 * Motor.h
 *
 *  Created on: Jan 27, 2016
 *      Author: Daniel Owen
 */
#pragma once

#include "Profile/IProfile.h"
#include "IControl.h"
#include "WPILib.h"
#include "Math.h"

class Motor: public IControl {
public:
	Motor(IProfile *np);
	virtual ~Motor();

	//IControl
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();

	//Methods for Components
	void setDrive(float speedL, float speedR);
	void setShoot(float speedL, float speedR);
	void setArm(float armSpeed);
	void setIntake(float intakeSpeed);

	//TODO What
	void setShoot1(bool run);
	void setShoot2(bool run);

private:
	Talon *frontLeft, *frontRight, *backLeft, *backRight;
	//Spark *frontLeft, *frontRight, *backLeft, *backRight; //Drive Motors

	//Talon *shootFrontLeft, *shootFrontRight, *shootBackLeft, *shootBackRight; //Shooter Motors
	Spark *shootLeft, *shootRight;

	Spark *armLower; //, *armUpper; // Arm Motors

	Spark *intake;

	float leftSpeed, rightSpeed; //Drive variables
	float sLeftSpeed, sRightSpeed; //Shooter variables
	float aLowerSpeed, aUpperSpeed; //Arm variables
	float intakeSpeed;
};

