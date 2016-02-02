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

	float leftSpeed;
	float rightSpeed;

	IProfile *profile;

protected:
	Jaguar *frontLeft;
	Jaguar *frontRight;
	Jaguar *backLeft;
	Jaguar *backRight;


};

