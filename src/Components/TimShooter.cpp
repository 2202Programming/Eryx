/*
 * TimShooter.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: lazar
 */

#include <Components/TimShooter.h>

TimShooter::TimShooter(IProfile *pro, IXbox *x) {
	// TODO Auto-generated constructor stub
	profile = pro;
	xbox = x;

	c = new Compressor();

	Spin1 = new Jaguar(profile->getInt("SPIN1"));
	Spin2 = new Jaguar(profile->getInt("SPIN2"));

	updown = new Victor(profile->getInt("UPDOWN"));
	UpMax = new DigitalInput(profile->getInt("UPMAX"));
	DownMax = new DigitalInput(profile->getInt("DOWNMAX"));

	safe = new Solenoid(2);
	fire = new Solenoid(3);
}

TimShooter::~TimShooter() {
	// TODO Auto-generated destructor stub
}

void TimShooter::TeleopInit(){
	c->SetClosedLoopControl(true);
	fire->Set(true);
	safe->Set(false);
	setMotors(0.0);
}

void TimShooter::TeleopPeriodic(){

	c->SetClosedLoopControl(true);

	if(xbox->getRightBumperPressed() && !(state == 4.0)){
		state++;
	}

	if(xbox->getLeftBumperPressed() && !(state == 0.0)){
		state --;
	}
	setMotors(.25*state);

	bool go = xbox->getRightTriggerHeld();
	SmartDashboard::PutBoolean("GO", go);
	if(go){
		fire->Set(false);
		safe->Set(true);
	}
	else {
		fire->Set(true);
		safe->Set(false);
	}

	bool updo = xbox->getAHeld();
	SmartDashboard::PutBoolean("UPDOWN", updo);
	if(updo){
		updown->Set(.1);
	}
	else updown->Set(0.0);

}

void TimShooter::DisabledInit(){

	c->SetClosedLoopControl(false);

}

void TimShooter::setMotors(float value){
	Spin1->Set(value);
	Spin2->Set(value);
}
