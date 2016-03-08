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
#include "WPILib.h"

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

	bool DEBUG = false;

	enum TargetingState{
		waitForButtonPress,
		waitForStopped,
		waitForPicResult,
		driveToAngle,
	};

	enum AutoStratagy{
		null,
		timer,
		distance,
		encoder,
		hardTimer,
	};


	AutoStratagy strat = encoder;

	MotorCommand *UpdateMotorSpeeds(float leftMotorSpeed, float rightMotorSpeed);
	DriveSystemState DriveSystemControlUpdate(DriveSystemState currentState, DriveSystemState requestedState);

	void RobotInit();
	void TeleopInit();
	void TeleopPeriodic();
	void AutonomousInit();
	bool AutonomousPeriodic(stepBase *step);
	void InitDriveStraight(driveStep *step);
	bool ExecDriveStraight(driveStep *step);
	void InitTurn(turnStep *step);
	bool ExecTurn(turnStep *step);


protected:
	Encoder *left;
	Encoder *right;
	Encoder *left2;
	Encoder *right2;

	TargetingState targetState;
	DriveSystemState currentDriveState, commandDriveState;
	double visionTargetAngle;
	double visionAngleTolerance;
	float turnSpeed;
	int currentStep;

	bool comp = true;
	bool inAutonomous;
	bool time;
	bool autoTime;

	float angleTime;
	int timesCalled = 0;
	Timer *t;

	double motorConstant = 1.5;
	double DriveStraitTime;

	void InitAutoTarget();
	bool AutoTarget();

	bool GetDriveStraightContinue(float value);

	void PIDWrite(float output);
	void TargetingStateMachine();
	void InitializeVisionAlignment(double commandedAngle);
	bool ExecuteVisionAlignment();
	int getTime();
};

#endif /* SRC_SENSORCONTROL_NAVXSENSORCONTROL_H_ */
