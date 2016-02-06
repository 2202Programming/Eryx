/*
 * NavxSensorControl.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Beasty
 */

#include <SensorControl/NavxSensorControl.h>

NavxSensorControl::NavxSensorControl(IXbox *xboxInstance, IProfile *profileInstance) {
	// TODO Auto-generated constructor stub
	xbox = xboxInstance;
	profile = profileInstance;
}

NavxSensorControl::~NavxSensorControl() {
	// TODO Auto-generated destructor stub
}

MotorCommand *NavxSensorControl::UpdateMotorSpeeds(int leftMotorSpeed, int rightMotorSpeed){
	updateMotorSpeedResponse.leftMotorSpeed = leftMotorSpeed;
	updateMotorSpeedResponse.rightMotorSpeed = rightMotorSpeed;
	return &updateMotorSpeedResponse;
}

NavxSensorControl::DriveSystemState NavxSensorControl::DriveSystemControlUpdate(DriveSystemState currentState, DriveSystemState requestedState){
	return DriveSystemState::running;
}

void NavxSensorControl::TeleopPeriodic(){

}
