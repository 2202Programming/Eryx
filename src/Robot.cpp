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

#define debug 1

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
	Motor *m;
	IXbox *xbox;
	IProfile* profile;
	ISensorControl* sensorControl;
	IVision* vision;
	Drive *drive;
	std::vector<stepBase> *auton;
	std::string robot;


	Robot() {

		xbox = MasterXboxController::getInstance();
		profile = new SProfile();
		master = new noList();
		profile = new SProfile();

		robot = profile->getValue("ROBOT");

		master->addNode(xbox, "Xbox");

		if (robot.compare("PROTO") == 0) {

			master->addNode(new SimpleDrive(profile, xbox), "drive");

		} else if (robot.compare("TIM") == 0) {

			master->addNode(new SimpleDrive(profile, xbox), "drive");
			master->addNode(new TimShooter(profile, xbox), "shooter");

		} else if (robot.compare("ORYX") == 0) {

			vision = new Vision();
			m = new Motor(profile);
			sensorControl = new NavxSensorControl(xbox, profile, vision);
			drive = new Drive(profile, m, xbox, sensorControl);

			master->addNode(sensorControl, "Sensor Control");
			master->addNode(vision, "Vision");
			master->addNode(drive, "Drive");
			master->addNode(new Arm(m, xbox), "ARM");

			//MUST BE CALLED LAST
			master->addNode(m, "Motor");
		}

		std::string autonID = profile->getValue("AUTOLIST");

		auton = new std::vector<stepBase>();

		if(autonID.compare("BASIC")==0){
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
		}
	}

private:
	LiveWindow *lw;

	void RobotInit() {
		lw = LiveWindow::GetInstance();
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
		if(robot.compare("ORYX")==0)
		{
		stepBase *command = &auton->at(x);
		if(command != NULL){
			bool result = sensorControl->AutonomousPeriodic(command);
			if(result){
				x += 1;
				command = &auton->at(x);
			}
		}
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
