#include <string>
#include "Profile/IProfile.h"
#include "Profile/SProfile.h"
#include "Xbox/IXbox.h"
#include "Xbox/MasterXboxController.h"
#include "WPILib.h"
#include "Drive/Drive.h"
#include "Components/TimShooter.h"
#include "Shooter/Shooter.h"
#include "Vision/IVision.h"
#include "SensorControl/ISensorControl.h"
#include "Vision/Vision.h"
#include "SensorControl/NavxSensorControl.h"
#include "Motor/Motor.h"
#include "Drive/SimpleDrive.h"
#include "Arm/Arm.h"
#include "Profile/DProfile.h"

#define debug 1
#define RAMPARTS 0
#define LOWBAR 1
#define ROCKWALL 2
#define DEBRIS 3
#define MOAT 4
#define DRAW 5
#define CHEVAL 6
#define SALLY 7
#define PORTI 8

struct nLNode {
	IControl* value;
	std::string id;
	nLNode* parent;

	nLNode(IControl* val, std::string nid) {
		value = val;
		id = nid;
		parent = NULL;
	}
};

struct noList {
	nLNode* head;
	int length = 0;

	noList() {
		head = NULL;
	}
	nLNode* getComponent(std::string id) {
		nLNode* test = head;
		while (test != NULL) {
			std::string tid = test->id;
			if (id.compare(id) == 0) {
				return test;
			} else {
				test = test->parent;
			}
		}
		if (debug) {
			printf("noList: No Element Found in the Array");
		}
		return NULL;
	}

	void addNode(IControl* obj, std::string nid) {
		nLNode* object = new nLNode(obj, nid);
		object->parent = head;
		head = object;
	}
};

class Robot: public IterativeRobot {
public:

	noList* master;
	IProfile* profile;
	std::vector<stepBase> *auton;
	Motor *m;
	IXbox *xbox;
	ISensorControl* sensorControl;
	IVision* vision;
	Drive *drive;
	Arm *arm;

	std::string robot;

	Robot() {
		master = new noList();
		profile = new DProfile();

		xbox = MasterXboxController::getInstance();

		robot = profile->getValue("ROBOT");

		master->addNode(xbox, "Xbox");
		/*
		 if (robot.compare("PROTO") == 0) {

		 master->addNode(new SimpleDrive(profile, xbox), "drive");

		 } else if (robot.compare("TIM") == 0) {

		 master->addNode(new SimpleDrive(profile, xbox), "drive");
		 master->addNode(new TimShooter(profile, xbox), "shooter");

		 }// else if (robot.compare("ORYX") == 0) {
		 */
		vision = new Vision();
		m = new Motor(profile);
		sensorControl = new NavxSensorControl(xbox, profile, vision);
		drive = new Drive(m, xbox, sensorControl);
		arm = new Arm(m, xbox);

		master->addNode(sensorControl, "Sensor Control");
		master->addNode(vision, "Vision");
		master->addNode(drive, "Drive");
		//master->addNode(arm, "ARM");

		//MUST BE CALLED LAST
		master->addNode(m, "Motor");

		std::string autonID = profile->getValue("AUTOLIST");

		auton = new std::vector<stepBase>();

		if (autonID.compare("BASIC") == 0) {
			driveStep step1 = driveStep();
			step1.command = stepBase::driveStraight;
			step1.distance = 5;
			step1.stepNum = 0;
			step1.speed = .5;
			auton->push_back(step1);

			stepBase fin = stepBase();
			fin.command = stepBase::stop;
			fin.stepNum = 1;
			auton->push_back(fin);
		} else if (autonID.compare("ADVANCED") == 0) {
			int def = profile->getInt("AUTO_DEF");
			int pos = profile->getInt("AUTO_POS");
			bool basic = true;

			driveStep drive = driveStep();
			switch (def) {
			case DEBRIS:
				drive.stepNum = 0;
				drive.command = stepBase::driveStraight;
				drive.distance = 2.0;
				drive.speed = .75;
				auton->push_back(drive);
				break; //TODO
			case RAMPARTS:
				drive.stepNum = 0;
				drive.command = stepBase::driveStraight;
				drive.distance = 2.0;
				drive.speed = .75;
				auton->push_back(drive);
				break; //TODO
			case LOWBAR:
				drive.stepNum = 0;
				drive.command = stepBase::driveStraight;
				drive.distance = 2.0;
				drive.speed = .75;
				auton->push_back(drive);
				break; //TODO
			case MOAT:
				drive.stepNum = 0;
				drive.command = stepBase::driveStraight;
				drive.distance = 2.0;
				drive.speed = .75;
				auton->push_back(drive);
				break; //TODO
			case ROCKWALL:
				drive.stepNum = 0;
				drive.command = stepBase::driveStraight;
				drive.distance = 2.0;
				drive.speed = .75;
				auton->push_back(drive);
				break; //TODO
			case PORTI:
				drive.stepNum = 0;
				drive.command = stepBase::driveStraight;
				drive.distance = 2.0;
				drive.speed = .75;
				auton->push_back(drive);
				break; //TODO
			}

			turnStep turn = turnStep();

			switch (pos) {
			case 1:
				turn.stepNum = 1;
				turn.command = stepBase::turn;
				turn.angle = 45.0;
				turn.speed = .5;
				auton->push_back(turn);

				break; //TODO
			case 2:
				turn.stepNum = 1;
				turn.command = stepBase::turn;
				turn.angle = 45.0;
				turn.speed = .5;
				auton->push_back(turn);
				break; //TODO
			case 3:
				turn.stepNum = 1;
				turn.command = stepBase::turn;
				turn.angle = 45.0;
				turn.speed = .5;
				auton->push_back(turn);
				break; //TODO
			case 4:
				turn.stepNum = 1;
				turn.command = stepBase::turn;
				turn.angle = 45.0;
				turn.speed = .5;
				auton->push_back(turn);
				break; //TODO
			case 5:
				turn.stepNum = 1;
				turn.command = stepBase::turn;
				turn.angle = 45.0;
				turn.speed = .5;
				auton->push_back(turn);
				break; //TODO
			}

			stepBase prepareShot = stepBase();
			prepareShot.stepNum = 2;
			prepareShot.command = stepBase::target;
			auton->push_back(prepareShot);

			stepBase shoot = stepBase();
			shoot.stepNum = 3;
			shoot.command = stepBase::shoot;
			auton->push_back(shoot);

			stepBase stop = stepBase();
			stop.stepNum = 4;
			stop.command = stepBase::stop;
			auton->push_back(stop);
		}
	}

private:
	LiveWindow *lw;

	void RobotInit() {
		lw = LiveWindow::GetInstance();
		//SmartDashboard::PutString("Profile",robot);
		SmartDashboard::PutString("MOTORFL", profile->getValue("MOTORFL"));
		SmartDashboard::PutString("State", "Robot Init");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->RobotInit();
			test = test->parent;
		}

	}

	void AutonomousInit() {
		SmartDashboard::PutString("State", "Autonomous Init");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->AutonomousInit();
			test = test->parent;
		}
	}

	void AutonomousPeriodic() {
		SmartDashboard::PutString("State", "Autonomous Periodic");
		//No list here beacause auto was always a bit more complicated

		int x = 0;
		if (robot.compare("ORYX") == 0) {
			stepBase *command = &auton->at(x);
			if (command != NULL) {
				bool result = sensorControl->AutonomousPeriodic(command);
				if (result) {
					x += 1;
					command = &auton->at(x);
				}
			}
		}
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->AutonomousPeriodic();
			test = test->parent;
		}

	}

	void TeleopInit() {
		SmartDashboard::PutString("State", "Teleop Init");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->TeleopInit();
			test = test->parent;
		}
	}

	void TeleopPeriodic() {
		SmartDashboard::PutString("State", "Teleop Periodic");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->TeleopPeriodic();
			test = test->parent;
		}
	}

	void TestInit() {
		SmartDashboard::PutString("State", "Test Init");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->TestInit();
			test = test->parent;
		}
	}

	void TestPeriodic() {
		SmartDashboard::PutString("State", "Test Periodic");
		lw->Run();
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->TestPeriodic();
			test = test->parent;
		}
	}
};

START_ROBOT_CLASS(Robot);
