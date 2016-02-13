/*
 * NavxSensorControl.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Beasty
 */

#include <SensorControl/NavxSensorControl.h>

NavxSensorControl::NavxSensorControl(IXbox *xboxInstance,
		IProfile *profileInstance, IVision *visionInstance) {
	// TODO Auto-generated constructor stub
	xbox = xboxInstance;
	profile = profileInstance;
	vision = visionInstance;
	ahrs = new AHRS(SPI::Port::kMXP);
	turnController = new PIDController(0.001, 0.0005, 0.00, ahrs, this);
}

NavxSensorControl::~NavxSensorControl() {
	// TODO Auto-generated destructor stub
}

MotorCommand *NavxSensorControl::UpdateMotorSpeeds(float leftMotorSpeed,
		float rightMotorSpeed) {
	if (!inAutonomous) {

		switch (targetState) {
		case TargetingState::driveToAngle:
			break;
		default:
			updateMotorSpeedResponse.leftMotorSpeed = leftMotorSpeed;
			updateMotorSpeedResponse.rightMotorSpeed = rightMotorSpeed;
			break;
		}
	}
	return &updateMotorSpeedResponse;
}

NavxSensorControl::DriveSystemState NavxSensorControl::DriveSystemControlUpdate(
		DriveSystemState currentState, DriveSystemState requestedState) {
	// Drive system tells you what it's doing
	currentDriveState = currentState;
	// Requests a drive system state change
	return commandDriveState;
}

void NavxSensorControl::TargetingStateMachine() {
	float motorSpeed = 0;
	switch (targetState) {
	case TargetingState::waitForButtonPress:
		if (xbox->getLeftTriggerPressed()) {
			commandDriveState = DriveSystemState::stopped;
			targetState = TargetingState::waitForStopped;
		}

		break;
	case TargetingState::waitForStopped:
		if (currentDriveState == DriveSystemState::stopped) {
			// Tell Vision to take a picture
			//vision->startAiming();
			targetState = TargetingState::waitForPicResult;
		}
		break;
	case TargetingState::waitForPicResult:
		//if (vision->getDoneAiming()) {
		if (true) {
			//visionTargetAngle = vision->getDegreesToTurn();
			visionTargetAngle = 42;
			turnController->SetSetpoint(10);
			turnController->SetOutputRange(-1, 1);
			turnController->Enable();
			targetState = TargetingState::driveToAngle;
			updateMotorSpeedResponse.leftMotorSpeed = 0;
			updateMotorSpeedResponse.rightMotorSpeed = 0;
		}
		break;
	case TargetingState::driveToAngle:
		// Go to that angle
		if (abs(turnController->GetError()) < 30) {
			turnController->Disable();
			targetState = TargetingState::waitForButtonPress;
			commandDriveState = DriveSystemState::running;
			//motorSpeed = 0;
		} else {
			motorSpeed = turnSpeed;
		}
		SmartDashboard::PutNumber("NavX Motor Speed", motorSpeed);
		/*if (abs(motorSpeed) > 0.3)
		 {
		 if (motorSpeed > 0)
		 {
		 motorSpeed = 0.3;
		 }
		 else
		 {
		 motorSpeed = -0.3;
		 }
		 }*/

		updateMotorSpeedResponse.leftMotorSpeed = -motorSpeed;
		updateMotorSpeedResponse.rightMotorSpeed = motorSpeed;

		//updateMotorSpeedResponse.leftMotorSpeed = 1;
		//updateMotorSpeedResponse.rightMotorSpeed = 1;
		//targetState = TargetingState::waitForButtonPress;
		//commandDriveState = DriveSystemState::running;
		break;
	default:
		targetState = TargetingState::waitForButtonPress;
		break;
	}
}

void NavxSensorControl::PIDWrite(float output) {
	turnSpeed = output;
}

void NavxSensorControl::TeleopInit() {
	turnSpeed = 0;
	targetState = TargetingState::waitForButtonPress;
	currentDriveState = DriveSystemState::running;
	commandDriveState = DriveSystemState::running;
}

void NavxSensorControl::TeleopPeriodic() {
	inAutonomous = false;
	TargetingStateMachine();

	SmartDashboard::PutNumber("Yaw", ahrs->GetYaw());
	SmartDashboard::PutNumber("Roll", ahrs->GetRoll());
	SmartDashboard::PutNumber("Pitch", ahrs->GetRoll());
}

void NavxSensorControl::AutonomousInit() {
	currentStep = -1;
	inAutonomous = true;
}

/*
 * Initialize parameters for a straight drive
 */

void NavxSensorControl::InitDriveStraight(driveStep *step) {
	SmartDashboard::PutNumber("Displacement", step->distance);
}

/*
 * Execute one driveStraight step
 * return true if target reached
 */
bool NavxSensorControl::ExecDriveStraight(driveStep *step) {
	SmartDashboard::PutNumber("Displacement", ahrs->GetDisplacementX());

	if (ahrs->GetDisplacementX() < step->distance) {
		// Check these motor speed values
		updateMotorSpeedResponse.leftMotorSpeed = step->speed;
		updateMotorSpeedResponse.rightMotorSpeed = step->speed;
		return false;
	} else {
		// Set speeds to zero
		updateMotorSpeedResponse.leftMotorSpeed = 0;
		updateMotorSpeedResponse.rightMotorSpeed = 0;
	}
	return true;
}

void NavxSensorControl::InitTurn(turnStep *step) {

}

/*
 * Execute one turn step
 * return true if target reached
 */

bool NavxSensorControl::ExecTurn(turnStep *step) {
	return true;
}

bool NavxSensorControl::AutonomousPeriodic(stepBase *step) {
	updateMotorSpeedResponse.leftMotorSpeed = 0;
	updateMotorSpeedResponse.rightMotorSpeed = 0;

	switch (step->command) {
	case step->driveStraight:
		if (currentStep != step->stepNum) {
			currentStep = step->stepNum;
			InitDriveStraight((driveStep *) step);
		}
		return ExecDriveStraight((driveStep *) step);
		break;
	case step->turn:
		if (currentStep != step->stepNum) {
			currentStep = step->stepNum;
			InitTurn((turnStep *) step);
		}
		return ExecTurn((turnStep *) step);
		break;

	case step->stop:
		// Stop all autonomous execution
		return false;

	default:
		// We don't support this command; skip
		return true;
	}
	// If we get here, we're lost and we give up
	return false;
}
