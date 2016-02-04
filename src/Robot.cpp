#include "targetGiver.h"

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
		IControl* xbox;
		xbox = MasterXboxController::getInstance();
		head = new nLNode(xbox, "xbox");
		length = 1;
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

	IControl::profile CompareID(std::string id) {

		IControl::profile ret;

		if (id.compare("Tim") == 1) {
			ret = IControl::profile::Tim;
		}

		else if (id.compare("Hoen") == 1) {
			ret = IControl::profile::Hoen;
		}

		else if (id.compare("Monty20")) {
			ret = IControl::Monty20;
		}

		else if (id.compare("Proto")) {
			ret = IControl::Proto;
		}

		else if (id.compare("bot2016")) {
			ret = IControl::bot2016;
		} else {
			ret = IControl::nothing;
		}

		return ret;
	}

	noList* master;
	IControl::profile profile;

	Robot() {
		master = new noList();
		//profile = CompareID(SmartDashboard::GetString("Identity"));

		if(profile = IControl::Proto){
		}

	}

private:
	LiveWindow *lw;

	void RobotInit() {
		lw = LiveWindow::GetInstance();
		SmartDashboard::PutString("State", "Robot Init");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->RobotInit(IControl::profile(profile));
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
		IXbox* xbox=MasterXboxController::getInstance();
		SmartDashboard::PutNumber("IsAHeld", xbox->getAHeld());
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
