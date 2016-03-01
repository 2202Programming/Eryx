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
	turnController = new PIDController(0.01, 0.000, 0.00, ahrs, this);
	turnController->SetInputRange(-180.0, 180.0);
	turnController->SetOutputRange(-1, 1);
	turnController->SetContinuous(true);
	time = false;
	angleTime = 0.0;
	t = NULL;

	left = new Encoder(2, 3);
	right = new Encoder(4, 5);
	left2 = new Encoder(6, 7);
	right2 = new Encoder(0, 1);

	left->SetReverseDirection(true);
	left2->SetReverseDirection(true);
	right->SetReverseDirection(false);
	right2->SetReverseDirection(false);
}

NavxSensorControl::~NavxSensorControl() {
	// TODO Auto-generated destructor stub
	delete ahrs;
	delete turnController;
	delete vision;

	delete left, right, left2, right2;
	delete t;
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

	if(DEBUG){
	SmartDashboard::PutNumber("Update Motor Left",
			updateMotorSpeedResponse.leftMotorSpeed);
	SmartDashboard::PutNumber("Update Motor right",
			updateMotorSpeedResponse.rightMotorSpeed);
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
			vision->startAiming();
			targetState = TargetingState::waitForPicResult;
		}
		break;
	case TargetingState::waitForPicResult:
		if (vision->getDoneAiming()) {
			//if (true) {
			visionTargetAngle = vision->getDegreesToTurn();
			//visionTargetAngle = 42;
			ahrs->ZeroYaw();
			turnController->Reset();
			turnController->SetSetpoint(visionTargetAngle);
			time = false;
			turnController->Enable();
			targetState = TargetingState::driveToAngle;
			updateMotorSpeedResponse.leftMotorSpeed = 0;
			updateMotorSpeedResponse.rightMotorSpeed = 0;
		}
		break;
	case TargetingState::driveToAngle:
		if (fabs(turnController->GetError()) < 3) {
			if (t == NULL) {
				t = new Timer();
				t->Start();
			} else {
				if (t->Get() > 1) {
					time = true;
				}
			}
		} else {
			delete t;
			t = NULL;
		}
		if (xbox->getStartPressed() || time) {
			turnController->Disable();
			targetState = TargetingState::waitForButtonPress;
			commandDriveState = DriveSystemState::running;
			delete t;
			t = NULL;
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
	ahrs->ZeroYaw();
	turnSpeed = 0;
	targetState = TargetingState::waitForButtonPress;
	currentDriveState = DriveSystemState::running;
	commandDriveState = DriveSystemState::running;
	t = NULL;
	turnController->SetPID(0.055, 0.0004, 0.0);
	left->Reset();
	right->Reset();
	left2->Reset();
	right2->Reset();
}

void NavxSensorControl::TeleopPeriodic() {
	inAutonomous = false;
	TargetingStateMachine();

	SmartDashboard::PutNumber("Yaw", ahrs->GetYaw());
	//SmartDashboard::PutNumber("Roll", ahrs->GetRoll());
	//SmartDashboard::PutNumber("Pitch", ahrs->GetPitch());

	SmartDashboard::PutNumber("Left Drive", left->Get());
	SmartDashboard::PutNumber("Right Drive", right->Get());
	SmartDashboard::PutNumber("Left Drive 2", left2->Get());
	SmartDashboard::PutNumber("Right Drive 2", right2->Get());
}

void NavxSensorControl::AutonomousInit() {
	currentStep = -1;
	inAutonomous = true;
}

/*
 * Initialize parameters for a straight drive
 */

void NavxSensorControl::InitDriveStraight(driveStep *step) {
	t = new Timer();

		t->Stop();
		t->Reset();
		t->Start();
		DriveStraitTime = (step->distance / (step->speed * motorConstant));

}

/*
 * Execute one driveStraight step
 * return true if target reached
 */

bool NavxSensorControl::GetDriveStraightContinue(float value){
	switch(strat){
	case null:
		return false;
	case timer:
		return t->Get() < DriveStraitTime; //TODO
	case distance:
		return ahrs->GetDisplacementX() < value;
	case encoder:
		return right2->GetDistance() < 2000 || right->GetDistance() < 2000 || left->GetDistance() < 2000 || left2->GetDistance() < 2000;
	case hardTimer:
		SmartDashboard::PutNumber("Timer", t->Get());
		return t->Get() < 1;
	default:
		return false;
	}

}

bool NavxSensorControl::ExecDriveStraight(driveStep *step) {

	if (DEBUG) {
		SmartDashboard::PutNumber("Displacement Y", ahrs->GetDisplacementY());
		SmartDashboard::PutNumber("Displacement X", ahrs->GetDisplacementX());
		SmartDashboard::PutNumber("Displacement Z", ahrs->GetDisplacementZ());
		SmartDashboard::PutString("AUTO STATE", "Exec Drive Straight");
		SmartDashboard::PutNumber("Time Called Auto", timesCalled);
		SmartDashboard::PutNumber("Step Speed", step->speed);
		timesCalled += 1;
	}

	if (GetDriveStraightContinue(step->distance)) {
		// Check these motor speed values
		updateMotorSpeedResponse.leftMotorSpeed = step->speed;
		updateMotorSpeedResponse.rightMotorSpeed = step->speed;
		return false;
	} else {
		// Set speeds to zero
		updateMotorSpeedResponse.leftMotorSpeed = 0;
		updateMotorSpeedResponse.rightMotorSpeed = 0;
	}
	delete t;
	t = NULL;
	SmartDashboard::PutString("AUTO STATE", "Exec Drive Straight END");
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

	SmartDashboard::PutNumber("Left Drive", left->Get());
	SmartDashboard::PutNumber("Right Drive", right->Get());
	SmartDashboard::PutNumber("Left Drive 2", left2->Get());
	SmartDashboard::PutNumber("Right Drive 2", right2->Get());

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
		if(t != NULL) delete t;
		t = NULL;
		updateMotorSpeedResponse.leftMotorSpeed = 0;
		updateMotorSpeedResponse.rightMotorSpeed = 0;
		return false;
	case step->target:
		if(t != NULL)delete t;
		t = NULL;

		if(currentStep != step->stepNum){
			currentStep = step->stepNum;

		}
		break;
	case step->shoot:
		break;
	default:
		// We don't support this command; skip
		return true;
	}
	// If we get here, we're lost and we give up
	return false;
}
