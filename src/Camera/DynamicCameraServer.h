/*
 * DynamicCameraServer.h
 *
 *  Created on: Feb 19, 2016
 *      Author: lazar
 */

#ifndef SRC_CAMERA_DYNAMICCAMERASERVER_H_
#define SRC_CAMERA_DYNAMICCAMERASERVER_H_

#include "Camera/CameraController.h"
#include "IControl.h"
#include "Xbox/IXbox.h"

class DynamicCameraServer : public IControl {
public:
	DynamicCameraServer(IXbox*);
	virtual ~DynamicCameraServer();

	 void DisabledPeriodic();
	 void AutonomousPeriodic();
	 void TeleopPeriodic();
	 void TestPeriodic();

private:
	 CameraController* controller;
	 IXbox* xbox;
};

#endif /* SRC_CAMERA_DYNAMICCAMERASERVER_H_ */
