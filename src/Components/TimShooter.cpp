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

	c = new Compressor();
	Spin1 = new Jaguar(profile->getInt("SPIN1"));
	Spin2 = new Jaguar(profile->getInt("SPIN2"));

	safe = new Solenoid(profile->getInt("SAFE"));
	fire = new Solenoid(profile->getInt("FIRE"));
}

TimShooter::~TimShooter() {
	// TODO Auto-generated destructor stub
}

void TimShooter::TeleopInit(){
	c->SetClosedLoopControl(true);
	setSolenoid(false);
	setMotors(0.0);
}

void TimShooter::TeleopPeriodic(){
	c->SetClosedLoopControl(true);
	if(xbox->getRightBumperPressed() && !(state == 4)){
		state++;
	}

	if(xbox->getLeftBumperPressed() && !(state == 0)){
		state --;
	}
	setMotors(state * .25);

	if(xbox->getRightTriggerHeld())
		setSolenoid(true);
	else setSolenoid(false);
}

void TimShooter::DisabledInit(){
	c->SetClosedLoopControl(false);
}

void TimShooter::toggleSolenoid(){
	safe->Set(!safe->Get());
	fire->Set(!fire->Get());
}

void TimShooter::setSolenoid(bool trigger){
	safe->Set(!trigger);
	fire->Set(trigger);
}

void TimShooter::setMotors(float value){
	Spin1->Set(value);
	Spin2->Set(value);
}
