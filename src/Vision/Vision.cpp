/*
 * Vision.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Team Wumbo
 */
#include "NetworkTables/NetworkTable.h"
#include <AHRS.h>
#include <Vision/Vision.h>

#define JAVA_ERROR -2
#define NOT_SET -1
#define WAITING 0
#define START 1
#define PROCESSING 2
#define DONE 3

void Vision::RobotInit() {
	table = NetworkTable::GetTable("database");
	setState(WAITING);
}

void Vision::TeleopPeriodic() {
	switch (getState()) {
	case JAVA_ERROR:
		SmartDashboard::PutString("VisionStateString", "Java Error");
		break;
	case NOT_SET:
		SmartDashboard::PutString("VisionStateString", "Not Set");
		break;
	case WAITING:
		SmartDashboard::PutString("VisionStateString", "WAITING");
		break;
	case START:
		SmartDashboard::PutString("VisionStateString", "Start Vision");
		break;
	case PROCESSING:
		SmartDashboard::PutString("VisionStateString", "Processing");
		break;
	case DONE:
		SmartDashboard::PutString("VisionStateString", "Done");
		break;
	default:
		SmartDashboard::PutString("VisionStateString",
				"Something went really wrong");
		break;
	}

	visionUpdate();
}

void Vision::visionUpdate() {
	int shootingState = getState();
	if (shootingState == NOT_SET) {
		setState(WAITING);
	}
}

void Vision::startAiming() {
	int shootingState = getState();
	if (shootingState == WAITING) {
		setState(START);
	}
}

float Vision::getDegreesToTurn() {
	return table->GetNumber("degreesToTurn", 0);
}

bool Vision::getDoneAiming() {
	int shootingState = getState();
	if (shootingState == DONE) {
		setState(WAITING);
		return true;
	}
	return false;
}

void Vision::setState(int newState) {
	table->PutNumber("shootingState", newState);
}

int Vision::getState() {
	return (int) (table->GetNumber("shootingState", -1.0));
}

/*
 * shootingState possibilities:
 * -2: There was an error on the java side
 * -1: Oops...
 * 0: unassigned
 * 1: takePicture
 * 2: processingPicture
 * 3: shootingComplete
 */
