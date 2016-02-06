/*
 * ISensorControl.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Beasty
 */

#ifndef SRC_SENSORCONTROL_ISENSORCONTROL_H_
#define SRC_SENSORCONTROL_ISENSORCONTROL_H_

#include <IControl.h>

class MotorCommand {
public:
	int leftMotorSpeed;
	int rightMotorSpeed;
};

class ISensorControl: public IControl {
public:
	ISensorControl(){}
	virtual ~ISensorControl(){}
	enum DriveSystemState{
			running,
			stopping,
			stopped
		};
	MotorCommand updateMotorSpeedResponse;
	//Currently does absolutely nothing other than set DriveSystemState to running.
	virtual DriveSystemState DriveSystemControlUpdate(DriveSystemState currentState, DriveSystemState requestedState){
		return DriveSystemState::running;
	}
	virtual MotorCommand *UpdateMotorSpeeds(int leftMotorSpeed, int rightMotorSpeed){

		updateMotorSpeedResponse.leftMotorSpeed = leftMotorSpeed;
		updateMotorSpeedResponse.rightMotorSpeed = rightMotorSpeed;

		return &updateMotorSpeedResponse;
	}
};

#endif /* SRC_SENSORCONTROL_ISENSORCONTROL_H_ */
