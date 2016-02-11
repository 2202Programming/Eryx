/*
 * Drive.h
 *
 *  Created on: Jan 27, 2016
 *      Author: Daniel Owen
 */

#include "WPILib.h"
#include "IControl.h"
#include "IDrive.h"
#include "Profile/IProfile.h"
#include "Motor/Motor.h"
#include "Xbox/IXbox.h"
#include "SensorControl/ISensorControl.h"
#include "Math.h"

#ifndef SRC_DRIVE_H_
#define SRC_DRIVE_H_

class Drive: public IDrive, public IControl {
public:
	Drive(IProfile *np, Motor *motor, IXbox *xbox, ISensorControl *nav);
	virtual ~Drive();

	//IControl
	void TeleopInit();
	void TeleopPeriodic();

private:
	//Different Control Methods - pick one and call it in TeleopPeriodic
	void readXboxTank();
	void readXboxArcadeT();
	void readXboxArcadeD();
	void updateMotors();

	//Acceleration for the drives
	float acceleration(float newS, float oldS);

	IProfile *profile;

	Motor *motor;
	IXbox *xbox;
	ISensorControl *nav;
	MotorCommand *navSpeed;

	ISensorControl::DriveSystemState state; //Current state
	ISensorControl::DriveSystemState requestedState; //State nav wants us to go to

	float leftSpeed, rightSpeed;

	bool userControl; //True if using xbox or decelerating, false if under nav control
};

#endif /* SRC_DRIVE_H_ */
