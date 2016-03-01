/*
 * CustomUSBCamera.h
 *
 *  Created on: Feb 22, 2016
 *      Author: lazar
 */

#ifndef SRC_CAMERA_CUSTOMUSBCAMERA_H_
#define SRC_CAMERA_CUSTOMUSBCAMERA_H_

#include "IControl.h"
#include "WPILib.h"


class CustomUSBCamera: public IControl {
public:
	CustomUSBCamera();
	virtual ~CustomUSBCamera();

	void setCameraName(std::string);
	void startAutoCapture();
	void stopAutoCapture();

	void setExposure(unsigned int);
	unsigned int getExposure();

	void DisabledPeriodic();
	void AutonomousPeriodic();
	void TeleopPeriodic();


private:
	void run();
	void remake();
	std::shared_ptr<USBCamera> Pointy;
	USBCamera *Cam;
};

#endif /* SRC_CAMERA_CUSTOMUSBCAMERA_H_ */
