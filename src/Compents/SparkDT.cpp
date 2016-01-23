/*
 * SparkDT.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: lazar
 */
#pragma once
#include "targetGiver.h"
#include "WPILib.h"

//Channels
#define FLC_Proto 1
#define FRC_Proto 2
#define RLC_Proto 3
#define RRC_Proto 4

class SparkDT: public IControl {

	int FrontLeftChannel, FrontRightChannel, RearLeftChannel, RearRightChannel;
	Spark *FrontLeftSpark, *FrontRightSpark, *RearLeftSpark, *RearRightSpark;
	XboxController2 *xbox = MasterXboxController::getInstance();

	SparkDT(IControl::profile profile) {
		//Decides the pinouts based on which profile it is in
		if (profile == IControl::Proto) {
			FrontLeftChannel = FLC_Proto;
			FrontRightChannel = FRC_Proto;
			RearLeftChannel = RLC_Proto;
			RearRightChannel = RRC_Proto;
		} else {
			FrontLeftChannel = 0;
			FrontRightChannel = 0;
			RearLeftChannel = 0;
			RearRightChannel = 0;
		}

		FrontLeftSpark = new Spark(FrontLeftChannel);
		FrontRightSpark = new Spark(FrontRightChannel);
		RearLeftSpark = new Spark(RearLeftChannel);
		RearRightSpark = new Spark(RearRightChannel);


		//Invert the left motors
		FrontLeftSpark->SetInverted(true);
		RearLeftSpark->SetInverted(true);
	}

	void TeleopInit() {

	}

	void TelepPeriodic() {
		//Get Xbox Right x  and left x

		//Set left motor to left x

		//Set right motors to right x
	}

};

