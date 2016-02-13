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
#include <AHRS.h>
#include <Vision/IVision.h>

#include <SensorControl/ISensorControl.h>

class NavxSensorControl: public ISensorControl, public PIDOutput {
public:
	NavxSensorControl(IXbox *xbox, IProfile *profileInstance, IVision *visionInstance);
	virtual ~NavxSensorControl();

	IXbox *xbox;
	IProfile *profile;
	AHRS *ahrs;                         // navX-MXP
	PIDController *turnController;      // PID Controller
	IVision *vision;

	enum TargetingState{
		waitForButtonPress,
		waitForStopped,
		waitForPicResult,
		driveToAngle,
	};

	MotorCommand *UpdateMotorSpeeds(float leftMotorSpeed, float rightMotorSpeed);
	DriveSystemState DriveSystemControlUpdate(DriveSystemState currentState, DriveSystemState requestedState);

	void TeleopInit();
	void TeleopPeriodic();
	void AutonomousInit();
	bool AutonomousPeriodic(stepBase *step);
	void InitDriveStraight(driveStep *step);
	bool ExecDriveStraight(driveStep *step);
	void InitTurn(turnStep *step);
	bool ExecTurn(turnStep *step);


protected:
	TargetingState targetState;
	DriveSystemState currentDriveState, commandDriveState;
	double visionTargetAngle;
	double visionAngleTolerance;
	float turnSpeed;
	int currentStep;
	bool inAutonomous;

	void PIDWrite(float output);
	void TargetingStateMachine();
	void InitializeVisionAlignment(double commandedAngle);
	bool ExecuteVisionAlignment();

};

#endif /* SRC_SENSORCONTROL_NAVXSENSORCONTROL_H_ */
