/*
 * CommandListMaker->cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: lazar
 */
#include <Autonomous/CommandListMaker.h>
#include "WPILib.h"

CommandListMaker::CommandListMaker(IProfile *p) {
	profile = p;
	storage = new std::vector<stepBase*>();

	// TODO Auto-generated constructor stub
}

CommandListMaker::~CommandListMaker()
{
	delete storage;
}

void CommandListMaker::RobotInit()
{
	autoPosition = new SendableChooser();
	autoPosition->AddDefault(low, (void*)&low);
	autoPosition->AddObject(ram, (void*)&ram);
	autoPosition->AddObject(rock, (void*)&rock);
	autoPosition->AddObject(port, (void*)&port);
	autoPosition->AddObject(chev, (void*)&chev);
	autoPosition->AddObject(sall, (void*)&sall);
	autoPosition->AddObject(deb, (void*)&deb);
	autoPosition->AddObject(moat, (void*)&moat);
	autoPosition->AddObject(draw, (void*)&draw);
	SmartDashboard::PutData("Position", autoPosition);

	autoDefence = new SendableChooser();
	autoDefence->AddDefault(pos1, (void*)&pos1);
	autoDefence->AddObject(pos2, (void*)&pos2);
	autoDefence->AddObject(pos3, (void*)&pos3);
	autoDefence->AddObject(pos4, (void*)&pos4);
	autoDefence->AddObject(pos5, (void*)&pos5);
	SmartDashboard::PutData("Defence", autoDefence);
}

void CommandListMaker::makeBasic()
{

	driveStep* step1 = new driveStep();
	step1->command = stepBase::driveStraight;
	step1->speed = 1.0;
	step1->distance = 1;
	step1->stepNum = 0;
	step1->speed = 1.0;
	storage->push_back(step1);

	turnStep* stp = new turnStep();
	stp->command = stepBase::turn;
	stp->angle= SmartDashboard::GetNumber("Auto Angle", 0);
	stp->speed = .5;
	stp->stepNum = 1;
	//storage->push_back(stp);

	stepBase *step2 = new stepBase();
	step2->command = stepBase::target;
	step2->stepNum = 2;
	//storage->push_back(step2);

	stepBase *fin =  new stepBase();
	fin->command = stepBase::shoot;
	fin->stepNum = 3;
	//storage->push_back(fin);

	stepBase *sb3 = new stepBase();
	sb3->command = stepBase::stop;
	sb3->stepNum = 4;
	storage->push_back(sb3);
}


void CommandListMaker::makeDefenceBreaker() {
	void* temp = autoPosition->GetSelected();
	std::string* dt =  static_cast<std::string*>(temp);
	std::string defence = *dt;

	temp = autoDefence->GetSelected();
	dt = static_cast<std::string*>(temp);
	std::string position = *dt;

	delete dt;
	delete temp;

	driveStep* drive = new driveStep();

	if(defence.compare(deb) == 0)	//DEBRIS
	{
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = 2.0;
		drive->speed = .75;
		storage->push_back(drive);
	}
	else if (defence.compare(ram)) //RAMPARTS
	{
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = 2.0;
		drive->speed = .75;
		storage->push_back(drive);
	}
	else if(defence.compare(rock)) //ROCK WALL
	{
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = 2.0;
		drive->speed = .75;
		storage->push_back(drive);
	}
	else if(defence.compare(low)) // LOW BAR
	{
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = 2.0;
		drive->speed = .75;
		storage->push_back(drive);
	}
	else if(defence.compare(moat) == 0) // DRAWBRIDGE
	{
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = 2.0;
		drive->speed = .75;
		storage->push_back(drive);
	}
	else //THE OTHERS
	{
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = .2;
		drive->speed = .75;
		storage->push_back(drive);
	}


	turnStep *turn = new turnStep();
	int pos = position[position.length()-1] - '0';
	switch (pos) {
	case 1:
		turn->stepNum = 1;
		turn->command = stepBase::turn;
		turn->angle = 45.0;
		turn->speed = .5;
		storage->push_back(turn);

		break; //TODO
	case 2:
		turn->stepNum = 1;
		turn->command = stepBase::turn;
		turn->angle = 45.0;
		turn->speed = .5;
		storage->push_back(turn);

		break; //TODO
	case 3:
		turn->stepNum = 1;
		turn->command = stepBase::turn;
		turn->angle = 45.0;
		turn->speed = .5;
		storage->push_back(turn);

		break; //TODO
	case 4:
		turn->stepNum = 1;
		turn->command = stepBase::turn;
		turn->angle = 45.0;
		turn->speed = .5;
		storage->push_back(turn);

		break; //TODO
	case 5:
		turn->stepNum = 1;
		turn->command = stepBase::turn;
		turn->angle = 45.0;
		turn->speed = .5;
		storage->push_back(turn);

		break; //TODO
	}

	stepBase* prepareShot = new stepBase();
	prepareShot->stepNum = 2;
	prepareShot->command = stepBase::target;
	storage->push_back(prepareShot);

	stepBase* shoot = new stepBase();
	shoot->stepNum = 3;
	shoot->command = stepBase::shoot;
	storage->push_back(shoot);

	stepBase* stop = new stepBase();
	stop->stepNum = 4;
	stop->command = stepBase::stop;
	storage->push_back(stop);
}

vector<stepBase*>* CommandListMaker::getList() {
	return storage;
}
