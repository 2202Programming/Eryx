/*
 * NavxSensorControl.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Beasty
 */

#include <SensorControl/NavxSensorControl.h>
#include <math.h>
#define STABILIZE true

#define kP 0.006
#define kI 0.002
#define kD 0.0

#define TunePID false

NavxSensorControl::NavxSensorControl(IXbox *xboxInstance,
		IProfile *profileInstance, IVision *visionInstance, Shooter *shhh) {
	// TODO Auto-generated constructor stub
	shootie = shhh;
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

	if (DEBUG) {
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
		if ((xbox->getLeftTriggerPressed() && !comp)
				|| (xbox->getLeftBumperPressed() && comp)) {
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
		if (xbox->getStartPressed()) {
			turnController->Disable();
			targetState = TargetingState::waitForButtonPress;
			commandDriveState = DriveSystemState::running;
			delete t;
			t = NULL;
		}
		if (vision->getDoneAiming()) {

			visionTargetAngle = vision->getDegreesToTurn();

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
		if (fabs(turnController->GetError()) < 1) 						//If the Error of the Turncontroller is below a certain value the timer starts to stop it
		{																//This only works if it is less then 1 for a whole second
			if (t == NULL) 												//If the timer doest exist yet we create a new one and start
			{
				t = new Timer();
				t->Start();												//TODO Figure out a way to start the timer if it already exists for some reason
			}
			else
			{
				if (t->Get() > 1) 										//If one second has passed then you are the correct angle
				{
					time = true;										//How you tell the system to move on
				}
			}
		}
		else 															//If the error is not less then 1 destroy the timer and restart it
		{
			delete t;
			t = NULL;
		}
		if (xbox->getStartPressed() || time) 							//Checks at the correct angle or abort
		{
			turnController->Disable();									//Turns off the PID controller
			targetState = TargetingState::waitForButtonPress;			//
			commandDriveState = DriveSystemState::running;
			delete t;
			t = NULL;
			//motorSpeed = 0;
		}
		else
		{
			motorSpeed = turnSpeed;
		}

		SmartDashboard::PutNumber("NavX Motor Speed", motorSpeed);		//SmartDashboard applied motor speed

		//Updateing the Motor Speed Values
		updateMotorSpeedResponse.leftMotorSpeed = -motorSpeed;
		updateMotorSpeedResponse.rightMotorSpeed = motorSpeed;
		break;
	default:
		targetState = TargetingState::waitForButtonPress;
		break;
	}
}

void NavxSensorControl::PIDWrite(float output) {
	bool positive = output >= 0;
	output = sqrt(fabs(output));//negative numbers don't have a real square root
	if (!positive)
		output *= -1;
	turnSpeed = output;
}

void NavxSensorControl::RobotInit() {


	SmartDashboard::PutNumber("kP", kP);
	SmartDashboard::PutNumber("kI", kI);
	SmartDashboard::PutNumber("kD", kD);
}
void NavxSensorControl::TeleopInit() {
	ahrs->ZeroYaw();
	turnSpeed = 0;
	targetState = TargetingState::waitForButtonPress;
	currentDriveState = DriveSystemState::running;
	commandDriveState = DriveSystemState::running;
	t = NULL;

	turnController->SetPID(0.040, 0.0025, 0.0);
	left->Reset();
	right->Reset();
	left2->Reset();
	right2->Reset();
}

void NavxSensorControl::TeleopPeriodic() {
	inAutonomous = false;
	TargetingStateMachine();
	SmartDashboard::PutNumber("Yaw", ahrs->GetYaw());

}

void NavxSensorControl::AutonomousInit() {
	right->Reset();
	currentStep = -1;
	inAutonomous = true;

	ahrs->ZeroYaw();
	turnController->SetPID(0.055, 0.0, 0.0);
}

/*
 * Initialize parameters for a straight drive
 */

void NavxSensorControl::InitDriveStraight(driveStep *step) {
	delete t;
	t = NULL;
	t = new Timer();

	t->Stop();
	t->Reset();
	t->Start();
	DriveStraitTime = (step->distance / (step->speed * motorConstant));

	right->SetDistancePerPulse(0.63);
}

double NavxSensorControl::GetEncoderCount(float value) {
	return value * 107.1429;
}


/*
 * Execute one driveStraight step
 * return true if target reached
 */

bool NavxSensorControl::GetDriveStraightContinue(float value) {
	switch (strat) {
	case null:
		return false;
	case timer:
		return t->Get() < DriveStraitTime; //TODO
	case distance:
		return ahrs->GetDisplacementX() < value;
	case encoder:
		return right->Get() <  1000; //GetEncoderCount(value);
	case hardTimer:

		SmartDashboard::PutNumber("Timer", t->Get());
		return t->Get() < 2;
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

	SmartDashboard::PutNumber("Distance", right->GetDistance());
	SmartDashboard::PutNumber("Raw", right->Get());

	if (GetDriveStraightContinue(step->distance)) {
		// Check these motor speed values
		updateMotorSpeedResponse.leftMotorSpeed = step->speed;
		updateMotorSpeedResponse.rightMotorSpeed = step->speed;

		if (STABILIZE) {
			if (ahrs->GetRawAccelY() > 0) {
				updateMotorSpeedResponse.leftMotorSpeed -= .05;
				updateMotorSpeedResponse.rightMotorSpeed += .05;
			} else if (ahrs->GetRawAccelY() < 0) {
				updateMotorSpeedResponse.leftMotorSpeed += .05;
				updateMotorSpeedResponse.rightMotorSpeed -= .05;
			}
		}
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

bool NavxSensorControl::AutonomousPeriodic(stepBase *step) {
	updateMotorSpeedResponse.leftMotorSpeed = 0;
	updateMotorSpeedResponse.rightMotorSpeed = 0;

	SmartDashboard::PutNumber("Yaw", ahrs->GetYaw());
	SmartDashboard::PutNumber("Left Drive", left->Get());
	SmartDashboard::PutNumber("Right Drive", right->Get());
	SmartDashboard::PutNumber("Left Drive 2", left2->Get());
	SmartDashboard::PutNumber("Right Drive 2", right2->Get());

	switch (step->command)
	{
	case step->driveStraight:
		InitDriveStraight((driveStep *) step);

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
		if (t != NULL)
			delete t;
		t = NULL;
		updateMotorSpeedResponse.leftMotorSpeed = 0;
		updateMotorSpeedResponse.rightMotorSpeed = 0;
		return false;
	case step->target:
		if (t != NULL)
			delete t;
		t = NULL;

		if (currentStep != step->stepNum) {
			currentStep = step->stepNum;
			InitAutoTarget();
		}
		return AutoTarget();
		break;
	case step->shoot:
		if (currentStep != step->stepNum) {
			currentStep = step->stepNum;
			InitAutoShoot();
		}
		return ExecAutoShoot();
		break;
	case step->experimentalDriveStraight:
		if(currentStep != step->stepNum)
		{
			currentStep = step->stepNum;
			InitExpDriveStraight();
		}
		return ExecExpDriveStraight((driveStep*)step);
		break;
	case step->driveThroughDefence:
		if(currentStep != step->stepNum)
		{
			currentStep = step->stepNum;
			InitDriveThroughDefence();
		}
		return ExecDriveThroughDefence();
		break;
	case step->driveTillHitsWall:
		if(currentStep != step->stepNum)
		{
			currentStep = step->stepNum;
			InitDriveTillHitsWall();
		}
		return ExecDriveTillHitsWall();
		break;
	case step->BeastModeDanceAttack:
		if(currentStep != step->stepNum)
		{
			currentStep = step->stepNum;
			InitBeastModeDanceAttack();
		}
		ExecBeastModeDanceAttack();
		break;
	default:
		return true;		// We don't support this command; skip
	}
	return false;	// If we get here, we're lost and we give up
}

void NavxSensorControl::InitAutoTarget() {
	ahrs->ZeroYaw();
	vision->startAiming();
	targetState = TargetingState::waitForPicResult;
}

bool NavxSensorControl::AutoTarget() {
	TargetingStateMachine();
	return time;
}

void NavxSensorControl::InitTurn(turnStep *step) {
	ahrs->ZeroYaw();
	turnController->Reset();
	turnController->SetSetpoint(step->angle);
	autoTime = false;
	turnController->Enable();
	targetState = TargetingState::driveToAngle;
	updateMotorSpeedResponse.leftMotorSpeed = 0;
	updateMotorSpeedResponse.rightMotorSpeed = 0;
}

bool NavxSensorControl::ExecTurn(turnStep *step) {
	float motorSpeed;
	SmartDashboard::PutString("AUTO STATE", "Exec Turn");
	if (fabs(turnController->GetError()) < 1) {
		if (t == NULL) {
			t = new Timer();
			t->Start();
		} else {
			if (t->Get() > 5) {
				time = autoTime;
			}
		}
	} else {
		delete t;
		t = NULL;
	}

	if (xbox->getStartPressed() || autoTime) {
		turnController->Disable();
		commandDriveState = DriveSystemState::running;
		delete t;
		t = NULL;
	} else {
		motorSpeed = turnSpeed;
	}

	updateMotorSpeedResponse.leftMotorSpeed = -motorSpeed;
	updateMotorSpeedResponse.rightMotorSpeed = motorSpeed;
	return autoTime;
}

void NavxSensorControl::InitAutoShoot()
{

}

bool NavxSensorControl::ExecAutoShoot()
{
	return shootie->shoot();
}


//Drive Straight with navx stabilization
void NavxSensorControl::InitExpDriveStraight()
{
	ahrs->ZeroYaw();

	SmartDashboard::PutString("AUTO STATE", "Init Exp Drive Straight");
	left->Reset();
	right->Reset();
	right2->Reset();
	left2->Reset();

	AO = new ArtificialOutput();
	AS = new ArtificialSource();

	if(TunePID)
	{
	nkp  = SmartDashboard::GetNumber("kP", kP);
	nki  = SmartDashboard::GetNumber("kI", kI);
	nkd  = SmartDashboard::GetNumber("kD", kD);
	}
	else
	{
	nkp = kP;
	nki = kI;
	nkd = kD;
	}

	if(DriveingController != NULL)
	{
		delete DriveingController;
		DriveingController = NULL;
	}
	DriveingController = new PIDController(nkp, nki, nkd, AS, AO);
	DriveingController->SetOutputRange(-.25,.25);
	DriveingController->Enable();
}
bool NavxSensorControl::ExecExpDriveStraight(driveStep* ds)
{
	SmartDashboard::PutString("AUTO STATE", "Exec Exp Drive Straight");
	float leftSet, rightSet;					//Left and right Set Values
	leftSet = ds->speed;
	rightSet = ds->speed;

	AS->SetDiffence(GetPIDError());				//Set the PID Error of the artifical PID
	float adjustment = AO->OutputValue;			//Get the Result of the PID

	leftSet = leftSet - adjustment/2;				//Adjust Left Based on PID
	rightSet = rightSet + adjustment/2;			//Adjust Right based on PID

	SmartDashboard::PutNumber("Drive Adjustment", adjustment);
	SmartDashboard::PutNumber("LeftSpeed", leftSet);
	SmartDashboard::PutNumber("RightSpeed", rightSet);
	SmartDashboard::PutNumber("CurrentYaw", ahrs->GetYaw());

	if(GetDriveStraightContinue(ds->distance))	//If it is less then whatever distance strat we are using
	{

		updateMotorSpeedResponse.leftMotorSpeed = leftSet;
		updateMotorSpeedResponse.rightMotorSpeed = rightSet;

		return false;
	}

	//Should Only Get Here if it at the final and correct distance
	SmartDashboard::PutString("AUTO STATE", "Init Exp Drive Straight End");
	delete AO;
	delete AS;
	delete DriveingController;
	return true;
}
float NavxSensorControl::GetPIDError()							//Support Return the offset from the correct path
{
	/*
	float leftAvg = (left->Get() + left2->Get())/2;
	float rightAvg = (right->Get() + right2->Get())/2;
	return leftAvg - rightAvg;
	*/

	return ahrs->GetYaw();
}


//Drive Throught Defence With Navx Heading to detect when the Pitch return to zero
void NavxSensorControl::InitDriveThroughDefence()
{
	SmartDashboard::PutString("AUTO STATE", "Init DriveThroughDefence");
}
bool NavxSensorControl::ExecDriveThroughDefence()
{
	SmartDashboard::PutString("AUTO STATE", "Exec DriveThroughDefence");


	SmartDashboard::PutString("AUTO STATE", "Exec DriveThroughDefence End");
	return true;
}
float NavxSensorControl::getPitch()
{
	return 0.0f;
}

//DriveUntil it hits the wall
void NavxSensorControl::InitDriveTillHitsWall()
{
	SmartDashboard::PutString("AUTO STATE", "Init DriveTillHitsWall");
	VoltageList = new std::list<double>();
}
bool NavxSensorControl::ExecDriveTillHitsWall()
{

	double motorSpeed = 0.5;
	updateMotorSpeedResponse.leftMotorSpeed = motorSpeed;
	updateMotorSpeedResponse.rightMotorSpeed = motorSpeed;

	SmartDashboard::PutString("AUTO STATE", "Exec DriveThroughDefence");
	VoltageList->push_front(DriverStation::GetInstance().GetBatteryVoltage());
	if(VoltageList->size() > 10)
	{
		VoltageList->pop_back();
	}
	double sum = 0;
	for(std::list<double>::iterator iter = VoltageList->begin(); iter != VoltageList->end(); iter++)
	{
		sum = sum + *iter;
	}
	sum = sum/10;
	if(sum > minVoltage)
	{
		return false;
	}
	else
	{
	SmartDashboard::PutString("AUTO STATE", "Exec DriveThroughDefence End");
	return true;
	}
}

//DANCE MODE DANCE DANCE DANCE DANCE DANCE DANCE DANCE DANCE DANCE DANCE DANCE DANCE
void NavxSensorControl::InitBeastModeDanceAttack()
{

}
bool NavxSensorControl::ExecBeastModeDanceAttack()
{
	float motorSpeed = 1.0f;
	updateMotorSpeedResponse.leftMotorSpeed = -motorSpeed;
	updateMotorSpeedResponse.rightMotorSpeed = motorSpeed;
	return false;
}
