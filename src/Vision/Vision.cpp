/*
 * Vision.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Team Wumbo
 */
#include "NetworkTables/NetworkTable.h"
#include <AHRS.h>
#include <Vision/Vision.h>

void Vision::RobotInit() {
	table=NetworkTable::GetTable("database");
}

void Vision::TeleopPeriodic() {
	visionUpdate();
}

void Vision::visionUpdate() {
	int shootingState=table->GetNumber("shootingState", -1);
	if (shootingState==3) {
		table->PutNumber("shootingState", 0);
	}
	else if (shootingState==-1) {
		table->PutNumber("shootingState", 0);
	}
}

void Vision::startAiming() {
	int shootingState=table->GetNumber("shootingState", -1);
	if (shootingState==0) {
		table->PutNumber("shootingState", 1);
	}
}

float Vision::getDegreesToTurn() {
	return table->GetNumber("degreesToTurn", 0);
}

bool Vision::getDoneAiming() {
	int shootingState=table->GetNumber("shootingState", -1);
	return shootingState==3;
}

/*
 * shootingState possibilities:
 * -1: Oops...
 * 0: unassigned
 * 1: takePicture
 * 2: processingPicture
 * 3: shootingComplete
 */
