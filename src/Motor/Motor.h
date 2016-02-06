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


class Motor {
public:
	Motor(IProfile *np);
	virtual ~Motor();
	void TeleopInit();
	void TeleopPeriodic();
	void setDrive(float speedL, float speedR);
	void setShoot(bool run);

	float leftSpeed;
	float rightSpeed;
	float sRightSpeed;
	float sLeftSpeed;

	IProfile *profile;

protected:
	Jaguar *frontLeft;
	Jaguar *frontRight;
	Jaguar *backLeft;
	Jaguar *backRight;

	Talon *shootLeft;
	Talon *shootRight;

	Encoder *encSR;
	Encoder *encSL;
};

