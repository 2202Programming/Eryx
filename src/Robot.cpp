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
#include "Autonomous/CommandListMaker.h"
#include "noList.cpp"

#define debug 1

class Robot: public IterativeRobot {
public:

	noList* master;
	IProfile* profile;
	std::vector<stepBase*> *auton;
	Motor *m;
	IXbox *xbox;
	ISensorControl* sensorControl;
	IVision* vision;
	Drive *drive;
	Arm *arm;
	CommandListMaker *clMaker;

	std::string robot;

	Robot() {
		master = new noList();
		profile = new DProfile();
		xbox = MasterXboxController::getInstance();
		clMaker = new CommandListMaker(profile);

		robot = profile->getValue("ROBOT");
		robot = "ORYX";

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
			drive = new Drive(m, xbox, sensorControl);
			arm = new Arm(m, xbox);

			master->addNode(sensorControl, "Sensor Control");
			master->addNode(vision, "Vision");
			master->addNode(drive, "Drive");
			//master->addNode(arm, "ARM");

			//MUST BE CALLED LAST
			master->addNode(m, "Motor");
		}

		std::string autonID = profile->getValue("AUTOLIST");
		autonID = "BASIC";
		if (autonID.compare("BASIC") == 0) {
			clMaker->makeBasic();
		} else if (autonID.compare("ADVANCED") == 0) {
		//	clMaker->makeDefenceBreaker();
		}
		auton = clMaker->getList();
	}

private:
	LiveWindow *lw;

	void RobotInit() {
		lw = LiveWindow::GetInstance();
		//SmartDashboard::PutString("Profile",robot);
		SmartDashboard::PutString("MOTORFL", profile->getValue("MOTORFL"));
		SmartDashboard::PutString("State", "Robot Init");
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
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
			stepBase *command = auton->at(x);
			if (sensorControl->AutonomousPeriodic(command) && command != NULL) {
				x += 1;
				command = auton->at(x);
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
