/*
 * CameraController.h
 *
 *  Created on: Feb 19, 2016
 *      Author: lazar
 */

#ifndef SRC_CAMERA_CAMERACONTROLLER_H_
#define SRC_CAMERA_CAMERACONTROLLER_H_

#include <IControl.h>

class LHSVision
{
public:
	LHSVision(RobotDrive*, Joystick*); //Constructor
	~LHSVision();	//Destructor
	void SendToDashboard(Image*); //Send Image to Dashboard
	void UpdateVision();	//Toggle and Display Camera
	void StopCamera(int);	//Close Specified Camera
	void StartCamera(int);	//Start Specified Camera

private:
	IMAQdxSession session;
	Image* frame;

	IMAQdxSession session2;
	Image* frame2;

	RobotDrive* mRobot;
	Joystick* mXbox;

	int send = 1;
};

#endif /* SRC_CAMERA_CAMERACONTROLLER_H_ */
