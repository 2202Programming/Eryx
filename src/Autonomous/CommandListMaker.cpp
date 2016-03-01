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

namespace AutoConstants{
	const std::string pos1 = "Position One";
	const std::string pos2 = "Position Two";
	const std::string pos3 = "Position Three";
	const std::string pos4 = "Position Four";
	const std::string pos5 = "Position Five";

	const std::string ram = "Ramparts";
	const std::string low = "Low Bar";
	const std::string rock = "Rock Wall";
	const std::string port = "Portculis";
	const std::string chev = "Cheval de Frise";
	const std::string sall = "Sally Port";
	const std::string deb = "Rough Terrain";
	const std::string moat = "Moat";
	const std::string draw = "Drawbridge";


}

CommandListMaker::CommandListMaker(IProfile *p) {
	profile = p;
	storage = new std::vector<stepBase*>();

	/*
	autoPosition = new SendableChooser();
	autoPosition->AddDefault(AutoConstants::pos1, (void*)1);
	autoPosition->AddObject(AutoConstants::pos2, (void*)2);
	autoPosition->AddObject(AutoConstants::pos3, (void*)3);
	autoPosition->AddObject(AutoConstants::pos4, (void*)4);
	autoPosition->AddObject(AutoConstants::pos5, (void*)5);

	autoDefence = new SendableChooser();
	autoDefence->AddDefault(AutoConstants::rock,(void*)ROCKWALL);
	autoDefence->AddObject(AutoConstants::low, (void*)LOWBAR);
	autoDefence->AddObject(AutoConstants::ram, (void*)RAMPARTS);
	autoDefence->AddObject(AutoConstants::port, (void*)PORTI);
	autoDefence->AddObject(AutoConstants::chev, (void*)CHEVAL);
	autoDefence->AddObject(AutoConstants::sall, (void*)SALLY);
	autoDefence->AddObject(AutoConstants::deb, (void*)DEBRIS);
	autoDefence->AddObject(AutoConstants::moat, (void*)MOAT);
	autoDefence->AddObject(AutoConstants::draw, (void*)DRAW);

	SmartDashboard::PutData("Auto Defence", autoDefence);
	SmartDashboard::PutData("Auto Position", autoPosition);
	*/
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
	step1->speed = 1.0;
	storage->push_back(step1);

	stepBase *fin =  new stepBase();
	fin->command = stepBase::stop;
	fin->stepNum = 1;
	storage->push_back(fin);
}


void CommandListMaker::makeDefenceBreaker() {
	int def = (int)autoDefence->GetSelected();
	int pos = (int)autoPosition->GetSelected();

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
