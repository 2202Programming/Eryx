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
#define FLC_Proto
#define FRC_Proto
#define RLC_Proto
#define RRC_Proto



class SparkDT : public IControl{

	int FrontLeftChannel, FrontRightChannel, RearLeftChannel, RearRightChannel;
	Spark *FrontLeftSpark, *FrontRightSpark, RearLeftSpark, RearRightSpark;
	XboxController2 *xbox = MasterXboxController::getInstance();

	SparkDT(IControl::profile profile){
		//Decides the pinouts based on which profile it is in

		//Invert the left motors
	}

	void TeleopInit(){

	}

	void TelepPeriodic(){
		//Get Xbox Right x  and left x

		//Set left motor to left x

		//Set right motors to right x
	}

};

