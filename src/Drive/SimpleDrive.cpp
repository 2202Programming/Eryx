/*
 * SimpleDrive.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: lazar
 */

#include <Drive/SimpleDrive.h>

SimpleDrive::SimpleDrive(IProfile *p, IXbox *x) {
	// TODO Auto-generated constructor stub
	profile = p;
	xbox = x;

	//	Spark *FLM, *FRM, *RLM, *RRM;

	FLM = new Spark(profile->getInt("MOTORFL"));
	FRM = new Spark(profile->getInt("MOTORFR"));
	RLM = new Spark(profile->getInt("MOTORBL"));
	RRM = new Spark(profile->getInt("MOTORBR"));

	RLM->SetInverted(true);
	FLM->SetInverted(true);
}

SimpleDrive::~SimpleDrive() {
	// TODO Auto-generated destructor stub
}

void SimpleDrive::TeleopInit(){
	leftSpeed = 0.0;
	rightSpeed = 0.0;
}

void SimpleDrive::TeleopPeriodic(){
	double x = xbox->getAxisLeftX();
	double y = xbox->getAxisLeftY();

	x = x * profile->getFloat("TURNSPEED");
	leftSpeed = y;
	rightSpeed = y;

	leftSpeed += x;
	rightSpeed -= x;

	FLM->Set(leftSpeed);
	FRM->Set(rightSpeed);
	RLM->Set(leftSpeed);
	RRM->Set(rightSpeed);
}
