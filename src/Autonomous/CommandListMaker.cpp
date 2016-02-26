/*
 * CommandListMaker->cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: lazar
 */
#define RAMPARTS 0
#define LOWBAR 1
#define ROCKWALL 2
#define DEBRIS 3
#define MOAT 4
#define DRAW 5
#define CHEVAL 6
#define SALLY 7
#define PORTI 8

#include <Autonomous/CommandListMaker.h>
#include "WPILib.h"

CommandListMaker::CommandListMaker(IProfile *p) {
	profile = p;
	storage = new std::vector<stepBase*>();
	// TODO Auto-generated constructor stub

}

CommandListMaker::~CommandListMaker() {
	delete storage;
	// TODO Auto-generated destructor stub
}

void CommandListMaker::makeBasic() {
	driveStep* step1 = new driveStep();
	step1->command = stepBase::driveStraight;
	step1->distance = 1;
	step1->stepNum = 0;
	step1->speed = 0.6;
	storage->push_back(step1);

	stepBase *fin =  new stepBase();
	fin->command = stepBase::stop;
	fin->stepNum = 1;
	storage->push_back(fin);
}


void CommandListMaker::makeDefenceBreaker() {
	int def = SmartDashboard::GetNumber("AUTO DEFENCE", 0);
	int pos = SmartDashboard::GetNumber("AUTO POSITION", 0);
	bool basic = true;

	driveStep* drive = new driveStep();
	switch (def) {
	case DEBRIS:
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = 2.0;
		drive->speed = .75;
		storage->push_back(drive);
		break; //TODO
	case RAMPARTS:
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = 2.0;
		drive->speed = .75;
		storage->push_back(drive);
		break; //TODO
	case LOWBAR:
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = 2.0;
		drive->speed = .75;
		storage->push_back(drive);
		break; //TODO
	case MOAT:
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = 2.0;
		drive->speed = .75;
		storage->push_back(drive);
		break; //TODO
	case ROCKWALL:
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = 2.0;
		drive->speed = .75;
		storage->push_back(drive);
		break; //TODO
	case PORTI:
		drive->stepNum = 0;
		drive->command = stepBase::driveStraight;
		drive->distance = 2.0;
		drive->speed = .75;
		storage->push_back(drive);
		break; //TODO
	}

	turnStep *turn = new turnStep();

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
