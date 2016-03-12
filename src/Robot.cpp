#include "targetGiver.h"

class Robot: public IterativeRobot {
public:
	unsigned int x = 0;
	IList* master;
	IProfile* profile;
	std::vector<stepBase*> *auton;
	Motor *m;
	IXbox *xbox;
	ISensorControl* sensorControl;
	IVision* vision;
	Drive *drive;
	Arm *arm;
	CommandListMaker *clMaker;
	RelayController* rc;

	bool DEBUG = false;

	Shooter *shooter;

	std::string robot;

	Robot() {
		master = new IList();
		profile = new DProfile();
		xbox = MasterXboxController::getInstance();
		clMaker = new CommandListMaker(profile);

		robot = profile->getValue("ROBOT");
		robot = "ORYX";

		master->addNode(xbox, "Xbox");

		if (robot.compare("PROTO") == 0) {

			//master->addNode(camera, "camera");

		} else if (robot.compare("TIM") == 0) {

			master->addNode(new SimpleDrive(profile, xbox), "drive");
			master->addNode(new TimShooter(profile, xbox), "shooter");

		} else if (robot.compare("ORYX") == 0) {

			vision = new Vision();
			m = new Motor(profile);
			arm = new Arm(m, xbox);
			shooter = new Shooter(m, xbox, profile);
			sensorControl = new NavxSensorControl(xbox, profile, vision, shooter);
			drive = new Drive(m, xbox, sensorControl);
			rc = new RelayController();

			master->addNode(sensorControl, "Sensor Control");
			master->addNode(vision, "Vision");
			master->addNode(drive, "Drive");
			master->addNode(shooter, "Shooter");
			master->addNode(arm, "ARM");
			master->addNode(rc, "relay");

			//MUST BE CALLED LAST
			master->addNode(m, "Motor");

		}

		clMaker->makeBasic();
		auton = clMaker->getList();
		//CameraServer::GetInstance()->StartAutomaticCapture("cam0");
	}

private:
	LiveWindow *lw;

	void RobotInit() {
		lw = LiveWindow::GetInstance();
		SmartDashboard::PutString("State", "Robot Init");
		//CameraServer::GetInstance()->StartAutomaticCapture("cam1");

		//added by David


		nLNode* test = master->head;
		while (test != NULL) {
			test->value->RobotInit();
			test = test->parent;
		}

	}

	void AutonomousInit() {
		x = 0;
		SmartDashboard::PutString("State", "Autonomous Init");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->AutonomousInit();
			test = test->parent;
		}
	}

	void AutonomousPeriodic() {
		SmartDashboard::PutString("State", "Autonomous Periodic");
		//No list here because auto was always a bit more complicated

		SmartDashboard::PutNumber("AUTO COMMAND", x);
		SmartDashboard::PutNumber("Auton Size", auton->size());
		if (robot.compare("ORYX") == 0 && x < auton->size()) {
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


		// Turn???
		//NavxSensorControl::AutonomousPeriodic(turn);

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

		//Added by David
		//

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

	void DisabledInit() {
		SmartDashboard::PutString("State", "Disabled Init");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->DisabledInit();
			test = test->parent;
		}
	}

	void DisabledPeriodic() {
		SmartDashboard::PutString("State", "Disabled Periodic");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->DisabledPeriodic();
			test = test->parent;
		}
	}
};

START_ROBOT_CLASS(Robot);
