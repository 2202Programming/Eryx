/*
 * DynamicCameraServer.cpp
 *
 *  Created on: Feb 19, 2016
 *      Author: lazar
 */

#include <Camera/DynamicCameraServer.h>

DynamicCameraServer::DynamicCameraServer(IXbox* nx) {
	// TODO Auto-generated constructor stub
	xbox = nx;
	controller = new CameraController();
}

DynamicCameraServer::~DynamicCameraServer() {
	// TODO Auto-generated destructor stub
	delete controller;
}

void DynamicCameraServer::DisabledPeriodic(){
	controller->UpdateVision(false);
}
void DynamicCameraServer::AutonomousPeriodic(){
	controller->UpdateVision(false);
}
void DynamicCameraServer::TeleopPeriodic(){
	controller->UpdateVision(xbox->getStartPressed());
}
void DynamicCameraServer::TestPeriodic(){
	controller->UpdateVision(false);
}
