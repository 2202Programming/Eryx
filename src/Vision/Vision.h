#ifndef VISION_H
#define VISION_H

class Vision: public IVision {
public:
	void RobotInit();
	void TeleopPeriodic();
	std::shared_ptr<NetworkTable> table;

	void startAiming();
	bool getDoneAiming();
	float getDegreesToTurn();


private:
	void visionUpdate();
};

#endif
