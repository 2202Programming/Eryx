/*
 * CommandListMaker->cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: lazar
 */
#include <Autonomous/CommandListMaker.h>
#include "WPILib.h"
#define TURNIF_NOSHOT true

//Constants to be adjusted
#define DIS_CENTR_ALIGN 181.0f + 50.0f
#define DIS_ALIGN_WALL 132.0f
#define DIS_FRONTD_BACKD 50.0f
#define DIS_LEFTPLAT_RIGHTPLAT 100.0f
#define ANG_ANGLESHOT 45.0f

CommandListMaker::CommandListMaker(IProfile *p)
{
	profile = p;
	storage = NULL;

	// TODO Auto-generated constructor stub
}

CommandListMaker::~CommandListMaker()
{
	delete storage;
}

void CommandListMaker::RobotInit()
{
#if 0
	autoPosition = new SendableChooser();
	autoPosition->AtargetTwoDefault(low, (void*) &low);
	autoPosition->AtargetTwoObject(ram, (void*) &ram);
	autoPosition->AtargetTwoObject(rock, (void*) &rock);
	autoPosition->AtargetTwoObject(port, (void*) &port);
	autoPosition->AtargetTwoObject(chev, (void*) &chev);
	autoPosition->AtargetTwoObject(sall, (void*) &sall);
	autoPosition->AtargetTwoObject(deb, (void*) &deb);
	autoPosition->AtargetTwoObject(moat, (void*) &moat);
	autoPosition->AtargetTwoObject(draw, (void*) &draw);
	//SmartDashboard::PutData("Position", autoPosition);
#endif

	stratChooser = new SendableChooser();
	stratChooser->AtargetTwoDefault(str_Approach, (void*) &str_Approach);
	stratChooser->AtargetTwoObject(str_Cross, (void*) &str_Cross);
	stratChooser->AtargetTwoObject(str_Shoot, (void*) &str_Shoot);
	SmartDashboard::PutData("Stratagy", stratChooser);

	autoDefence = new SendableChooser();
	autoDefence->AtargetTwoDefault(pos1, (void*) &pos1);
	autoDefence->AtargetTwoObject(pos2, (void*) &pos2);
	autoDefence->AtargetTwoObject(pos3, (void*) &pos3);
	autoDefence->AtargetTwoObject(pos4, (void*) &pos4);
	autoDefence->AtargetTwoObject(pos5, (void*) &pos5);
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

void CommandListMaker::makeDefenceBreaker()
{

	if (storage != NULL)
	{
		delete storage;
		storage = NULL;
	}
	storage = new std::vector<stepBase*>();

	/* Gets the current selction from the dashboard (should default to LowBar)*/
	//Selection
	void* temp = autoPosition->GetSelected();
	std::string* dt = static_cast<std::string*>(temp);
	std::string defence = *dt;

	temp = autoDefence->GetSelected();
	dt = static_cast<std::string*>(temp);
	std::string position = *dt;

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
		DriveDistance = 28;
		DriveSpeed = .75;
	}
	else if (defence.compare(ram)) //RAMPARTS
	{
		DriveDistance = 28;
		DriveSpeed = .75;
	}
	else if (defence.compare(rock)) //ROCK WALL
	{
		DriveDistance = 28;
		DriveSpeed = .75;
	}
	else if (defence.compare(low)) // LOW BAR
	{
		DriveDistance = 28;
		DriveSpeed = .75;
	}
	else if (defence.compare(moat) == 0) // Moat
	{
		DriveDistance = 28;
		DriveSpeed = .75;
	}
	else //THE OTHERS
	{

		DriveDistance = 0.5;
		DriveSpeed = 0.5;
		CanShoot = false;
	}
	//Seting the Values and Pushing the Command

	DriveDistance = 35;
	DriveSpeed = 0.75;

	driveStep* driveForward = new driveStep();
	driveForward->stepNum = GlobalStep;
	GlobalStep++;
	driveForward->command = stepBase::driveStraight;
	driveForward->distance = DriveDistance;
	driveForward->speed = DriveSpeed;
	storage->push_back(driveForward);

	stepBase* stop = new stepBase();
	stop->stepNum = GlobalStep;
	GlobalStep++;
	stop->command = stepBase::stop;
	storage->push_back(stop);
	//Turn Decision based on position

	if (CanShoot && TURNIF_NOSHOT)
	{
		//Eventual TurnStep
		turnStep *turn = new turnStep();

		//The Position it is in gotten through 'rough' means
		int pos = position[position.length() - 1] - '0';

		//Turn angle and
		double TurnAngle;
		double TurnSpeed; //TODO Remove from IControl this is't used

		//Switch Controller;
		switch (pos)
		{
		case 1:
			TurnAngle = 39.09;
			TurnSpeed = .6;
			break; //TODO
		case 2:
			TurnAngle = 27.11;
			TurnSpeed = .6;
			break; //TODO
		case 3:
			TurnAngle = 11.95;
			TurnSpeed = .6;
			break; //TODO
		case 4:
			TurnAngle = -5.06;
			TurnSpeed = .6;
			break; //TODO
		case 5:
			TurnAngle = -21.25;
			TurnSpeed = .6;
			break; //TODO
		default:
			TurnAngle = 0;
			TurnSpeed = .6;
			break;
		}

		//Sets and Push the Actual Step
		turn->stepNum = GlobalStep;
		GlobalStep++;
		turn->command = stepBase::turn;
		turn->angle = TurnAngle;
		turn->speed = TurnSpeed;
		storage->push_back(turn);
	}

	if (CanShoot)
	{
		stepBase* prepareShot = new stepBase();
		prepareShot->stepNum = GlobalStep;
		GlobalStep++;
		prepareShot->command = stepBase::target;
		storage->push_back(prepareShot);

		stepBase* shoot = new stepBase();
		shoot->stepNum = GlobalStep;
		GlobalStep++;
		shoot->command = stepBase::shoot;
		storage->push_back(shoot);

		stepBase* stop = new stepBase();
		stop->stepNum = GlobalStep;
		GlobalStep++;
		stop->command = stepBase::stop;
		storage->push_back(stop);
	}
}

void CommandListMaker::Experimental()
{
	if (storage != NULL)
	{
		delete storage;
		storage = NULL;
	}
	storage = new std::vector<stepBase*>();

	stepBase *t = new stepBase();
	t->stepNum = 0;
	t->command = stepBase::shoot;
	storage->push_back(t);


	stepBase *tt = new stepBase();
	tt->stepNum = 1;
	tt->command = stepBase::stop;
	storage->push_back(tt);

}

void CommandListMaker::makeOakWoodSpecial()
{
	if (storage != NULL)
	{
		delete storage;
		storage = NULL;
	}
	storage = new std::vector<stepBase*>();

	void* temp = autoDefence->GetSelected();
	std::string* dt = static_cast<std::string*>(temp);
	std::string position = *dt;

	temp = stratChooser->GetSelected();
	dt = static_cast<std::string*>(temp);
	std::string strat = *dt;

	Stratagy c;

	if (strat.compare(str_Approach) == 0)
	{
		c = Stratagy::Approach;
	}
	else if (strat.compare(str_Cross) == 0)
	{
		c = Stratagy::Cross;
	}
	else if (strat.compare(str_Shoot) == 0)
	{
		c = Stratagy::Shoot;
	}
	else
	{
		c = Stratagy::Approach;
	}


	int pos = position[position.length() - 1] - '0';

	Go(pos, c);
}

void CommandListMaker::Go(int x, Stratagy strat)
{
	stepBase *stp = new stepBase();

	int xx = 0;
	if (strat != Stratagy::Approach)
	{
		switch (x)
		{
		case 1:
			if ((strat == Stratagy::Cross) || (strat == Stratagy::Shoot))
			{
				driveStep *c = new driveStep();
				c->command = stepBase::experimentalDriveStraight;
				c->stepNum = xx;
				xx+=1;
				c->distance = DIS_CENTR_ALIGN;// + 40.0f;
				SmartDashboard::PutNumber("c->distance", c->distance);
				c->speed = .5;
				storage->push_back(c);
			}

			if (strat == Stratagy::Shoot)
			{
				turnStep *shootc = new turnStep();
				shootc->command = stepBase::turn;
				shootc->angle = ANG_ANGLESHOT + 15; //Angle + Adjustment
				shootc->speed = 0.5;
				shootc->stepNum = xx;
				xx+=1;
				storage->push_back(shootc);

				stepBase *c = new stepBase();
				c->command = stepBase::target;
				c->stepNum = xx;
				xx+=1;
				storage->push_back(c);

				driveStep *d = new driveStep();
				d->speed = .6;
				d->distance = 20;
				d->command = stepBase::driveStraight;
				d->stepNum = xx;
				xx+=1;
				storage->push_back(d);

				stepBase *targetTwo = new stepBase();
				targetTwo->command = stepBase::target;
				targetTwo->stepNum = xx;
				xx+=1;
				storage->push_back(targetTwo);

				stepBase *shoot = new stepBase();
				shoot->command = stepBase::shoot;
				shoot->stepNum = xx;
				xx+=1;
				storage->push_back(shoot);
			}

			stp->command = stepBase::stop;
			stp->stepNum = xx;
			xx+=1;
			storage->push_back(stp);

			break;
		case 2:
			if (strat == Stratagy::Cross)
			{
				driveStep *c = new driveStep();
				c->command = stepBase::experimentalDriveStraight;
				c->stepNum = xx;
				xx+=1;
				c->distance = DIS_CENTR_ALIGN;
				c->speed = .4;
				storage->push_back(c);
			}
			break;
		case 3:
			if (strat == Stratagy::Cross)
			{
				driveStep *c = new driveStep();
				c->command = stepBase::experimentalDriveStraight;
				c->stepNum = xx;
				xx+=1;
				c->distance = DIS_CENTR_ALIGN;
				c->speed = .6;
				storage->push_back(c);
			}

			break;
		case 4:

			if ((strat == Stratagy::Cross) || (strat == Stratagy::Shoot))
						{
							driveStep *c = new driveStep();
							c->command = stepBase::experimentalDriveStraight;
							c->stepNum = xx;
							xx+=1;
							c->distance = DIS_CENTR_ALIGN;
							c->speed = .7;
							storage->push_back(c);
						}

						if (strat == Stratagy::Shoot)
						{
							stepBase *shootc = new stepBase();
							shootc->command = stepBase::target;
							shootc->stepNum = xx;
							xx+=1;
							storage->push_back(shootc);

							stepBase *shoot = new stepBase();
							shoot->command = stepBase::shoot;
							shoot->stepNum = xx;
							xx+=1;
							//storage->push_back(shoot);
						}

						stp->command = stepBase::stop;
						stp->stepNum = xx;
						xx+=1;
						storage->push_back(stp);

			break;
		case 5:
			if (strat == Stratagy::Cross)
			{
				driveStep *c = new driveStep();
				c->command = stepBase::experimentalDriveStraight;
				c->stepNum = xx;
				xx+=1;
				c->distance = DIS_CENTR_ALIGN;
				c->speed = .6;
				storage->push_back(c);
			}
			break;
		}
	}
	else
	{
		driveStep *d = new driveStep();
		d->distance = 50;
		d->speed = .5;
		d->stepNum = xx;
		xx+=1;
		d->command = stepBase::experimentalDriveStraight;
		storage->push_back(d);

		stepBase *targetTwo = new stepBase();
		targetTwo->command = stepBase::stop;
		targetTwo->stepNum = xx;
		xx+=1;
		storage->push_back(targetTwo);
	}
}

vector<stepBase*>* CommandListMaker::getList()
{
	return storage;
}

void CommandListMaker::MakeDHarmSpecial()
{
	int i = 0;

	const double DISTANCE_FAST_ONE = 0.0;
	const double DISTANCE_SLOW_ONE = 0.0;
	const double DISTANCE_FAST_TWO = 0.0;
	const double TURNRADIUS = 90.0;
	const double DISTANCE_SLOW_TWO = 0.0;
	const double SPEED_FAST = 0.8;
	const double SPEED_SLOW = 0.4;


	//Fast Drive 1
	driveStep *fastDriveOne = new DriveStep();
	fastDriveOne->Speed = SPEED_FAST;
	fastDriveOne->distance = DISTANCE_FAST_ONE;
	fastDriveOne->stepNum = ++i;
	fastDriveOne->command = stepBase::experimentalDriveStraight;
	storage->push_back(fastDriveOned);

	//Slow Drive 
	driveStep *slowDrive = new DriveStep();
	slowDrive->Speed = SPEED_SLOW;
	slowDrive->distance = DISTANCE_SLOW_ONE;
	slowDrive->stepNum = ++i;
	slowDrive->command = stepBase::experimentalDriveStraight;
	storage->push_back(slowDrive);

	//Fast Drive Two
	driveStep *fastDriveTwo = new DriveStep();
	fastDriveTwo->Speed = SPEED_FAST;
	fastDriveTwo->distance = DISTANCE_FAST_TWO;
	fastDriveTwo->stepNum = ++i;
	fastDriveTwo->command = stepBase::experimentalDriveStraight;
	storage->push_back(fastDriveTwo);

	// Very Rough Turn to face goal
	turnStep *roughTurn = new turnStep();
	roughTurn->command = stepBase::turn;
	roughTurn->angle = TURNRADIUS; //Angle + Adjustment
	roughTurn->stepNum = ++i;
	storage->push_back(roughTurn);

	// Start Spinning up Drive Motors
	stepBase *spinUp = new stepBase();
	spinUp->command = stepBase::spinUp;
	spinUp->stepNum = ++i;
	storage->push_back(spinUp);

	// Rough Targeting
	stepBase *targetOne = new stepBase();
	targetOne->command = stepBase::target;
	targetOne->stepNum = ++i;
	storage->push_back(targetOne);

	// Drive Adjustment
	driveStep *slowDriveTwo = new driveStep();
	slowDriveTwo->speed = SPEED_SLOW;
	slowDriveTwo->distance = DISTANCE_SLOW_TWO;
	slowDriveTwo->command = stepBase::driveStraight;
	slowDriveTwo->stepNum = ++i;
	storage->push_back(slowDriveTwo);

	// Percise Targeting
	stepBase *targetTwo = new stepBase();
	targetTwo->command = stepBase::target;
	targetTwo->stepNum = ++i;
	storage->push_back(targetTwo);

	// Final Shoot
	stepBase *shoot = new stepBase();
	shoot->command = stepBase::shoot;
	shoot->stepNum = ++i;
	storage->push_back(shoot);
}