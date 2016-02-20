/*
 * CameraController.h
 *
 *  Created on: Feb 19, 2016
 *      Author: lazar
 */

#ifndef SRC_CAMERA_CAMERACONTROLLER_H_
#define SRC_CAMERA_CAMERACONTROLLER_H_
#include "WPILib.h"
#include <IControl.h>
#include "Xbox/IXbox.h"


class CameraController
{
public:
	CameraController(); //Constructor
	~CameraController();	//Destructor

	void SendToDashboard(Image*); //Send Image to Dashboard
	void UpdateVision(bool x);	//Toggle and Display Camera
	void StopCamera(int);	//Close Specified Camera
	void StartCamera(int);	//Start Specified Camera

private:
	IMAQdxSession session;
	Image* frame;

	IMAQdxSession session2;
	Image* frame2;

	int send = 1;
};

#endif /* SRC_CAMERA_CAMERACONTROLLER_H_ */
