/*
 * CustomUSBCamera.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: lazar
 */

#include <Camera/CustomUSBCamera.h>

namespace CamerIO{
	std::string camera = "cam0";
	const bool debug = true;
}


CustomUSBCamera::CustomUSBCamera() {
	// TODO Auto-generated constructor stub
	remake();
}

CustomUSBCamera::~CustomUSBCamera() {
	// TODO Auto-generated destructor stub
	delete Cam;
	Cam = 0;
}

void CustomUSBCamera::remake()
{
	Cam = new USBCamera(CamerIO::camera,false);
	Pointy = std::shared_ptr<USBCamera>(Cam);
	CameraServer::GetInstance()->StartAutomaticCapture(Pointy);
}

void CustomUSBCamera::setCameraName(std::string nn){
	CamerIO::camera = nn;
}

void CustomUSBCamera::setExposure(unsigned int nx)
{
	Cam->SetBrightness(nx);
	remake();
}

unsigned int CustomUSBCamera::getExposure()
{
	return Cam->GetBrightness();
}

void CustomUSBCamera::run()
{
	if(CamerIO::debug)
	{
		SmartDashboard::PutNumber("Camera Brightness", getExposure());
		SmartDashboard::PutString("Camera Name", CamerIO::camera);
	}

	setExposure(SmartDashboard::GetNumber("Brightness", 50));
}

void CustomUSBCamera::DisabledPeriodic()
{
	run();
}

void CustomUSBCamera::AutonomousPeriodic()
{
	run();
}

void CustomUSBCamera::TeleopPeriodic()
{
	run();
}
