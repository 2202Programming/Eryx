/*
 * NavxSensorControl.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Beasty
 */

#ifndef SRC_SENSORCONTROL_NAVXSENSORCONTROL_H_
#define SRC_SENSORCONTROL_NAVXSENSORCONTROL_H_
#include <Xbox/IXbox.h>
#include <Profile/IProfile.h>

#include <SensorControl/ISensorControl.h>

class NavxSensorControl: public ISensorControl {
public:
	NavxSensorControl(IXbox *xbox, IProfile *profileInstance);
	virtual ~NavxSensorControl();

	IXbox *xbox;
	IProfile *profile;

	MotorCommand *UpdateMotorSpeeds(int leftMotorSpeed, int rightMotorSpeed);
	DriveSystemState DriveSystemControlUpdate(DriveSystemState currentState, DriveSystemState requestedState);

	void TeleopPeriodic();
};

#endif /* SRC_SENSORCONTROL_NAVXSENSORCONTROL_H_ */
