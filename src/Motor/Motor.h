/*
 * Motor.h
 *
 *  Created on: Jan 27, 2016
 *      Author: Beast
 */
#pragma once

#include "Profile/IProfile.h"
#include "IControl.h"
#include "WPILib.h"


class Motor: public IControl {
public:
	Motor(IProfile *np);
	virtual ~Motor();

	//IControl
	void TeleopInit();
	void TeleopPeriodic();

	//Methods for Components
	void setDrive(float speedL, float speedR);
	void setShoot(bool run);
	void setArm(float aLowerSpeed, float aUpperSpeed);

private:
	IProfile *profile; //Robot profile for ports

	Talon *frontLeft, *frontRight, *backLeft, *backRight; //Drive Motors

	Talon *shootLeft, *shootRight; //Shooter Motors
	Encoder *encSR, *encSL; //Shooter Encoders

	Talon *armLower, *armUpper; //Arm Motors
	Encoder *encALower, *encAUpper; //Arm Encoders

	float leftSpeed, rightSpeed; //Drive variables
	float sLeftSpeed, sRightSpeed; //Shooter variables
	float aLowerSpeed, aUpperSpeed; //Arm variables
};

