#include "targetGiver.h"

class Robot: public IterativeRobot {
public:
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
	LineReader* lineReader;
	stepBase* currentStep;

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
			lineReader=new LineReader();

			master->addNode(sensorControl, "Sensor Control");
			master->addNode(vision, "Vision");
			master->addNode(drive, "Drive");
			master->addNode(shooter, "Shooter");
			master->addNode(arm, "ARM");
			master->addNode(rc, "relay");
			master->addNode(lineReader, "LineReader");//added by David, might have messed stuff up

			//MUST BE CALLED LAST
			master->addNode(m, "Motor");

		}


		//CameraServer::GetInstance()->StartAutomaticCapture("cam0");
	}

private:
	LiveWindow *lw;

	void RobotInit() {



		lw = LiveWindow::GetInstance();
		SmartDashboard::PutString("State", "Robot Init");
		SmartDashboard::PutNumber("Auto Angle", 0.0);
		clMaker->RobotInit();
		//CameraServer::GetInstance()->StartAutomaticCapture("cam1");

		//added by David


		nLNode* test = master->head;
		while (test != NULL) {
			test->value->RobotInit();
			test = test->parent;
		}

	}

	void AutonomousInit() {
		SmartDashboard::PutString("State", "Autonomous Init");

		clMaker->makeDefenceBreaker();
		currentStep = clMaker->getFirstStep();

		nLNode* test = master->head;
		while (test != NULL) {
			test->value->AutonomousInit();
			test = test->parent;
		}
	}

	void AutonomousPeriodic() {
		SmartDashboard::PutString("State", "Autonomous Periodic");

		//If the robot is oryx and the step is not null
		if (robot.compare("ORYX") == 0 && currentStep != NULL) {

			if (sensorControl->AutonomousPeriodic(currentStep)) {

				currentStep = clMaker->getNextStep();

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
