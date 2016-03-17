/*
 * CommandListMaker->cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: lazar
 */
#include <Autonomous/CommandListMaker.h>
#include "WPILib.h"
#define TURNIF_NOSHOT true

CommandListMaker::CommandListMaker(IProfile *p) {
	profile = p;
	storage = new std::vector<stepBase*>();

	// TODO Auto-generated constructor stub
}

CommandListMaker::~CommandListMaker() {
	delete storage;
}

void CommandListMaker::RobotInit() {
	autoPosition = new SendableChooser();
	autoPosition->AddDefault(low, (void*) &low);
	autoPosition->AddObject(ram, (void*) &ram);
	autoPosition->AddObject(rock, (void*) &rock);
	autoPosition->AddObject(port, (void*) &port);
	autoPosition->AddObject(chev, (void*) &chev);
	autoPosition->AddObject(sall, (void*) &sall);
	autoPosition->AddObject(deb, (void*) &deb);
	autoPosition->AddObject(moat, (void*) &moat);
	autoPosition->AddObject(draw, (void*) &draw);
	SmartDashboard::PutData("Position", autoPosition);

	autoDefence = new SendableChooser();
	autoDefence->AddDefault(pos1, (void*) &pos1);
	autoDefence->AddObject(pos2, (void*) &pos2);
	autoDefence->AddObject(pos3, (void*) &pos3);
	autoDefence->AddObject(pos4, (void*) &pos4);
	autoDefence->AddObject(pos5, (void*) &pos5);
	SmartDashboard::PutData("Defence", autoDefence);
}

void CommandListMaker::makeBasic() {

	driveStep* step1 = new driveStep();
	step1->command = stepBase::driveStraight;
	step1->speed = 1.0;
	step1->distance = 1;
	step1->stepNum = 0;
	step1->speed = 1.0;
	storage->push_back(step1);

	turnStep* stp = new turnStep();
	stp->command = stepBase::turn;
	stp->angle = SmartDashboard::GetNumber("Auto Angle", 0);
	stp->speed = .5;
	stp->stepNum = 1;
	//storage->push_back(stp);

	stepBase *step2 = new stepBase();
	step2->command = stepBase::target;
	step2->stepNum = 2;
	//storage->push_back(step2);

	stepBase *fin = new stepBase();
	fin->command = stepBase::shoot;
	fin->stepNum = 3;
	//storage->push_back(fin);

	stepBase *sb3 = new stepBase();
	sb3->command = stepBase::stop;
	sb3->stepNum = 4;
	storage->push_back(sb3);
}

void CommandListMaker::makeDefenceBreaker() {

	/* Gets the current selction from the dashboard (should default to LowBar)*/
	//Selection
	void* temp = autoPosition->GetSelected();
	std::string* dt = static_cast<std::string*>(temp);
	std::string defence = *dt;

	temp = autoDefence->GetSelected();
	dt = static_cast<std::string*>(temp);
	std::string position = *dt;

	delete dt;

	//Bool Determing if Shooting is possible on the current defence
	bool CanShoot = false;

	//Step Number Needs to be tracked
	int GlobalStep = 0;

	//Fist Drive Step Distance and Speed
	double DriveDistance;
	double DriveSpeed;

	//The Step We Are Going to Pass
	driveStep* drive = new driveStep();

	//Which Defence we are going over determines the speed and distance they will go
	//But ignores the type and number
	if (defence.compare(deb) == 0)	//DEBRIS
			{
		DriveDistance = 2.0;
		DriveSpeed = .75;
	} else if (defence.compare(ram)) //RAMPARTS
			{
		DriveDistance = 2.0;
		DriveSpeed = .75;
	} else if (defence.compare(rock)) //ROCK WALL
			{
		DriveDistance = 2.0;
		DriveSpeed = .75;
	} else if (defence.compare(low)) // LOW BAR
			{
		DriveDistance = 2.0;
		DriveSpeed = .75;
	} else if (defence.compare(moat) == 0) // Moat
			{
		DriveDistance = 2.0;
		DriveSpeed = .75;
	} else //THE OTHERS
	{
		DriveDistance = 0;
		DriveSpeed = 0;
		CanShoot = false;
	}

	//Seting the Values and Pushing the Command
	drive->stepNum = GlobalStep;
	GlobalStep++;
	drive->command = stepBase::driveStraight;
	drive->distance = DriveDistance;
	drive->speed = DriveSpeed;
	storage->push_back(drive);

	//Turn Decision based on position
	if (CanShoot && TURNIF_NOSHOT) {
		//Eventual TurnStep
		turnStep *turn = new turnStep();

		//The Position it is in gotten through 'rough' means
		int pos = position[position.length() - 1] - '0';

		//Turn angle and
		double TurnAngle;
		double TurnSpeed; //TODO Remove from IControl this is't used

		//Switch Controller;
		switch (pos) {
		case 1:
			TurnAngle = 45.0;
			TurnSpeed = .6;
			break; //TODO
		case 2:
			TurnAngle = 45.0;
			TurnSpeed = .6;
			break; //TODO
		case 3:
			TurnAngle = 45.0;
			TurnSpeed = .6;
			break; //TODO
		case 4:
			TurnAngle = 45.0;
			TurnSpeed = .6;
			break; //TODO
		case 5:
			TurnAngle = 45.0;
			TurnSpeed = .6;
			break; //TODO
		default:
			TurnAngle = 0;
			TurnSpeed = .6;
			break;
		}

		//Sets and Push the Actual Step
		turn->stepNum = GlobalStep; GlobalStep ++;
		turn->command = stepBase::turn;
		turn->angle = TurnAngle;
		turn->speed = TurnSpeed;
		storage->push_back(turn);
	}

	if (CanShoot) {
		stepBase* prepareShot = new stepBase();
		prepareShot->stepNum = GlobalStep; GlobalStep ++;
		prepareShot->command = stepBase::target;
		storage->push_back(prepareShot);

		stepBase* shoot = new stepBase();
		shoot->stepNum = GlobalStep; GlobalStep ++;
		shoot->command = stepBase::shoot;
		storage->push_back(shoot);

		stepBase* stop = new stepBase();
		stop->stepNum = GlobalStep; GlobalStep ++;
		stop->command = stepBase::stop;
		storage->push_back(stop);
	}
}
vector<stepBase*>* CommandListMaker::getList() {
	return storage;
}
