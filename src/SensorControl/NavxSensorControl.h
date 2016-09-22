/*
 * NavxSensorControl.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Beasty
 */

#ifndef SRC_SENSORCONTROL_NAVXSENSORCONTROL_H_
#define SRC_SENSORCONTROL_NAVXSENSORCONTROL_H_

#define DEBUG false;

#include <WPILib.h>
#include <math.h>
#include <list>
#include <AHRS.h>

#include "Xbox/IXbox.h"
#include "Profile/IProfile.h"
#include "Vision/IVision.h"
#include "Shooter/Shooter.h"
#include "SensorControl/Artificial.cpp"
#include "SensorControl/ISensorControl.h"

class NavxSensorControl: public ISensorControl, public PIDOutput {
public:
	NavxSensorControl(IXbox *xbox, IProfile *profileInstance, IVision *visionInstance, Shooter *shooterInstance);
	virtual ~NavxSensorControl();

	//Values for Targeting State machine
	enum TargetingState{
		waitForButtonPress,
		waitForStopped,
		waitForPicResult,
		driveToAngle,
		driveToDistance,
	};

	//Values for The DriveStraight Auto Step
	enum AutoStratagy{
		null,
		timer,
		distance,
		encoder,
		hardTimer,
	};

	//Which Stratagy the system is currently using
	AutoStratagy strat = encoder;

	MotorCommand *UpdateMotorSpeeds(float leftMotorSpeed, float rightMotorSpeed);
	DriveSystemState DriveSystemControlUpdate(DriveSystemState currentState, DriveSystemState requestedState);

	//ICONTROL METHODS
	void RobotInit();
	void TeleopInit();
	void TeleopPeriodic();
	void AutonomousInit();
	bool AutonomousPeriodic(stepBase *step);

private:


		Shooter *shooter;									//Main Shooting Mechanism
		IXbox *xbox;										  //Xbox Controller
		IProfile *profile;								//Profile System
		AHRS *ahrs;                       // navX-MXP
		PIDController *turnController;    // PID Controller
		IVision *vision;									//Vision Class

		void InitEncoders();

protected:

	float SavedYaw;

	float nkp, nkd, nki;

	ArtificialOutput* AO;									//Artifical PID Output for auto drive staight
	ArtificialSource* AS;									//Artifical PID Input for auto Drive Straight
	PIDController* DriveingController;		//PID Controller for auto Drive Straight

	std::list<double>* VoltageList;				//Stores the Last x Voltages to normalize the value
	double minVoltage = 8.0f;							//Store the Lowest Normal Voltage

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
	Timer *t = NULL;
	Timer *autoT = NULL;
	Timer *dxdt = NULL;

	double motorConstant = 1.5;
	double DriveStraitTime;

	void PIDWrite(float output);
	void TargetingStateMachine();
	void InitializeVisionAlignment(double commandedAngle);
	bool ExecuteVisionAlignment();
	int getTime();
};

#endif /* SRC_SENSORCONTROL_NAVXSENSORCONTROL_H_ */
