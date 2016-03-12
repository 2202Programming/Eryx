#ifndef VISION_H
#define VISION_H
#include <Vision/IVision.h>

class Vision: public IVision {
public:
	void RobotInit();
	void TeleopPeriodic();
	void AutonomousPeriodic();
	std::shared_ptr<NetworkTable> table;

	void startAiming();

	//This will return true exactly one time. The vision state machine will then be ready to aim again.
	bool getDoneAiming();
	bool getCrashed();
	float getDegreesToTurn();


private:
	void visionUpdate();
	void setState(int newState);
	int getState();
};

#endif
