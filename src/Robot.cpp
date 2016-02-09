#include <string>
#include "Profile/IProfile.h"
#include "Profile/SProfile.h"
#include "Xbox/IXbox.h"
#include "Xbox/MasterXboxController.h"
#include "WPILib.h"
#include "Drive/Drive.h"
#include "Shooter/Shooter.h"

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
	ISensorControl *nav;


	Robot() {
		xbox = MasterXboxController::getInstance();
		profile = new SProfile();
		master = new noList();
		m = new Motor(profile);

		master->addNode(m, "Motor");
		//master->addNode(new Drive(profile, m, xbox, nav), "Drive");
		//master->addNode(nav, "nav");
		master->addNode(new Shooter(m, xbox), "Shooter");
		master->addNode(xbox, "Xbox");
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

	void TestInit(){
		SmartDashboard::PutString("State", "Test Init");
		nLNode* test = master->head;
		while(test != NULL){
			test->value->TestInit();
			test = test->parent;
		}
	}

	void TestPeriodic() {
		SmartDashboard::PutString("State", "Test Periodic");
		lw->Run();
		nLNode* test = master->head;
		while (test != NULL){
			test->value->TestPeriodic();
			test = test->parent;
		}
	}
};

START_ROBOT_CLASS(Robot);
