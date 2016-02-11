/*
 * NavxSensorControl.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Beasty
 */

#include <SensorControl/NavxSensorControl.h>

NavxSensorControl::NavxSensorControl(IXbox *xboxInstance, IProfile *profileInstance, IVision *visionInstance) {
	// TODO Auto-generated constructor stub
	xbox = xboxInstance;
	profile = profileInstance;
	vision = visionInstance;
	turnController = new PIDController(0.03, 0.001, 0.02, ahrs, this);
	ahrs = new AHRS(SPI::Port::kMXP);
}

NavxSensorControl::~NavxSensorControl() {
	// TODO Auto-generated destructor stub
}

MotorCommand *NavxSensorControl::UpdateMotorSpeeds(float leftMotorSpeed, float rightMotorSpeed){\
	switch (targetState)
	{
	case TargetingState::driveToAngle:
		break;
	default:
		updateMotorSpeedResponse.leftMotorSpeed = leftMotorSpeed;
		updateMotorSpeedResponse.rightMotorSpeed = rightMotorSpeed;
		break;
	}
	return &updateMotorSpeedResponse;
}

NavxSensorControl::DriveSystemState NavxSensorControl::DriveSystemControlUpdate(DriveSystemState currentState, DriveSystemState requestedState){
	// Drive system tells you what it's doing
	currentDriveState = currentState;
	// Requests a drive system state change
	return commandDriveState;
}

void NavxSensorControl::TargetingStateMachine(){
	float motorSpeed = 0;
	switch (targetState)
	{

	case TargetingState::waitForButtonPress:
		if (xbox->getLeftTriggerPressed())
		{
			commandDriveState = DriveSystemState::stopped;
			targetState = TargetingState::waitForStopped;
		}

		break;
	case TargetingState::waitForStopped:
		if (currentDriveState == DriveSystemState::stopped)
		{
			// Tell Vision to take a picture
			//vision->startAiming();
			targetState = TargetingState::waitForPicResult;
		}
		break;
	case TargetingState::waitForPicResult:
		/*visionTargetAngle = vision->getDegreesToTurn();
		turnController->SetSetpoint(visionTargetAngle);
		turnController->SetOutputRange(-1, 1);
		turnController->Enable();
		*/
		targetState = TargetingState::driveToAngle;
		updateMotorSpeedResponse.leftMotorSpeed = 0;
		updateMotorSpeedResponse.rightMotorSpeed = 0;
		break;
	case TargetingState::driveToAngle:
		// Go to that angle
		/*if (abs(turnController->GetError()) < visionAngleTolerance)
		{
			turnController->Disable();
			targetState = TargetingState::waitForButtonPress;
			commandDriveState = DriveSystemState::running;
		} else {
			motorSpeed = turnSpeed;
		}
		UpdateMotorSpeeds(-motorSpeed, motorSpeed);
		*/
		updateMotorSpeedResponse.leftMotorSpeed = 1;
		updateMotorSpeedResponse.rightMotorSpeed = 1;

		//targetState = TargetingState::waitForButtonPress;
		//commandDriveState = DriveSystemState::running;
		break;
	default:
		targetState = TargetingState::waitForButtonPress;
		break;
	}
}

void NavxSensorControl::PIDWrite(float output)
{
	turnSpeed = output;
}

void NavxSensorControl::TeleopInit(){
	turnSpeed = 0;
	targetState = TargetingState::waitForButtonPress;
	currentDriveState = DriveSystemState::running;
	commandDriveState = DriveSystemState::running;
}

void NavxSensorControl::TeleopPeriodic(){

	TargetingStateMachine();
}
