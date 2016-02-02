/* A new version of XboxController that workes on an update system, to be called by a separate thread.
 This will attempt to avoid errors in calling certain methods multiple times and getting varying answers.
 */

#include <Xbox/MasterXboxController.h>
#include "WPILib.h"
#include <cmath>

#define BUTTON_A 1
#define BUTTON_B 2
#define BUTTON_X 3
#define BUTTON_Y 4
#define BUTTON_LB 5
#define BUTTON_RB 6
#define BUTTON_BACK 7
#define BUTTON_START 8
#define BUTTON_L3 9 // Press down the left joystick for L3.
#define BUTTON_R3 10 // Press down the right joystick for R3.

#define AXIS_RIGHT_X 4//-----------------------------------------Probably broken!!!!!!!!!!!!!!!!!!!!!!!!!!!! switch left with right!!!!!!!!!!!!!!!!!!!!!!!!
#define AXIS_RIGHT_Y 5//-----------------------------------------Probably broken!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define AXIS_LEFT_X 0
#define AXIS_LEFT_Y 1
#define AXIS_TRIGGER_LEFT 2// 2==left, 3==right TODO-------------------------------------------
#define AXIS_TRIGGER_RIGHT 3
#define JOG_DEBOUNCE 10

#define REAL_TIME_BETWEEN_UPDATES 0.005

#define DEBOUNCE_COUNT_LIMIT 15

static MasterXboxController *newXbox= NULL;
static MasterXboxController *newXbox2= NULL;

MasterXboxController::MasterXboxController(int port) :
		OldXboxController(port), lstick(port), rstick(port) {
	rstick.SetAxisChannel(Joystick::kXAxis, 4);
	rstick.SetAxisChannel(Joystick::kYAxis, 5);

	timer=new Timer();
	timer->Start();
	lostTimeBank=0.0;
	lastTime=timer->Get();

	//set all buttons to false
	xLast=false;
	xNow=false;
	yLast=false;
	yNow=false;
	aLast=false;
	aNow=false;
	bLast=false;
	bNow=false;
	startLast=false;
	startNow=false;
	backLast=false;
	backNow=false;
	leftBumperLast=false;
	leftBumperNow=false;
	rightBumperLast=false;
	rightBumperNow=false;
	l3Last=false;
	l3Now=false;
	r3Last=false;
	r3Now=false;
	leftTriggerLast=false;
	leftTriggerNow=false;
	rightTriggerLast=false;
	rightTriggerNow=false;

	//set counters to 0
	xDebounceCounter=0;
	yDebounceCounter=0;
	aDebounceCounter=0;
	bDebounceCounter=0;
	startDebounceCounter=0;
	backDebounceCounter=0;
	leftBumperDebounceCounter=0;
	rightBumperDebounceCounter=0;
	l3DebounceCounter=0;
	r3DebounceCounter=0;
	leftTriggerDebounceCounter=0;
	rightTriggerDebounceCounter=0;
}

MasterXboxController *MasterXboxController::getInstance(int port) {
	if (port==0) {
		if (newXbox==NULL) newXbox=new MasterXboxController(0); //this is the first time getInstance is called
		return newXbox;
	}
	else {
		if (newXbox2==NULL)newXbox2=new MasterXboxController(port); //this is the first time getInstance is called for this port
		return newXbox2;
	}
}

void MasterXboxController::update() {
	//<<<<<<< HEAD
	xLast=xNow;
	yLast=yNow;
	aLast=aNow;
	bLast=bNow;
	startLast=startNow;
	backLast=backNow;
	leftBumperLast=leftBumperNow;
	rightBumperLast=rightBumperNow;
	l3Last=l3Now;
	r3Last=r3Now;
	leftTriggerLast=leftTriggerNow;
	rightTriggerLast=rightTriggerNow;

	accountForLostTime(); //Not implemented yet

	xNow=isButtonHeld(xDebounceCounter, rstick.GetRawButton(BUTTON_X));
	yNow=isButtonHeld(yDebounceCounter, rstick.GetRawButton(BUTTON_Y));
	aNow=isButtonHeld(aDebounceCounter, rstick.GetRawButton(BUTTON_A));
	bNow=isButtonHeld(bDebounceCounter, rstick.GetRawButton(BUTTON_B));
	startNow=isButtonHeld(startDebounceCounter, rstick.GetRawButton(BUTTON_START));
	backNow=isButtonHeld(backDebounceCounter, rstick.GetRawButton(BUTTON_BACK));
	leftBumperNow=isButtonHeld(leftBumperDebounceCounter, rstick.GetRawButton(BUTTON_LB));
	rightBumperNow=isButtonHeld(rightBumperDebounceCounter, rstick.GetRawButton(BUTTON_RB));
	l3Now=isButtonHeld(l3DebounceCounter, rstick.GetRawButton(BUTTON_L3));
	r3Now=isButtonHeld(r3DebounceCounter, rstick.GetRawButton(BUTTON_R3));
	leftTriggerNow=isButtonHeld(leftTriggerDebounceCounter, getAxisTriggerLeft()>0.8);
	rightTriggerNow=isButtonHeld(rightTriggerDebounceCounter, getAxisTriggerRight()>0.8);
}

void MasterXboxController::accountForLostTime() { //TODO make this method update all counters
	double currentTime=timer->Get();
	lostTimeBank+=currentTime-lastTime-REAL_TIME_BETWEEN_UPDATES;

	while (lostTimeBank>=REAL_TIME_BETWEEN_UPDATES) {
		updateAllCounters();
		lostTimeBank-= REAL_TIME_BETWEEN_UPDATES;
	}

	lastTime=currentTime;
}

void MasterXboxController::updateAllCounters() {
	xDebounceCounter++;
	yDebounceCounter++;
	aDebounceCounter++;
	bDebounceCounter++;
	startDebounceCounter++;
	backDebounceCounter++;
	leftBumperDebounceCounter++;
	rightBumperDebounceCounter++;
	l3DebounceCounter++;
	r3DebounceCounter++;
	leftTriggerDebounceCounter++;
	rightTriggerDebounceCounter++;
}

float MasterXboxController::getAxisRightX() {
	return (-1.0)*rstick.GetRawAxis(AXIS_RIGHT_X);
}

float MasterXboxController::getAxisRightY() {
	return (-1.0)*rstick.GetRawAxis(AXIS_RIGHT_Y);
}

float MasterXboxController::getAxisLeftX() {
	return (-1.0)*lstick.GetRawAxis(AXIS_LEFT_X);
}

float MasterXboxController::getAxisLeftY() {
	return (-1.0)*lstick.GetRawAxis(AXIS_LEFT_Y);
}

bool MasterXboxController::getXPressed() {
	return (!xLast)&&(xNow);
}

bool MasterXboxController::getYPressed() {
	return (!yLast)&&(yNow);
}

bool MasterXboxController::getAPressed() {
	return (!aLast)&&(aNow);
}

bool MasterXboxController::getBPressed() {
	return (!bLast)&&(bNow);
}

bool MasterXboxController::getStartPressed() {
	return (!startLast)&&(startNow);
}

bool MasterXboxController::getBackPressed() {
	return (!backLast)&(backNow);
}

bool MasterXboxController::getLeftBumperPressed() {
	return (!leftBumperLast)&&(leftBumperNow);
}

bool MasterXboxController::getRightBumperPressed() {
	return (!rightBumperLast)&&(rightBumperNow);
}

bool MasterXboxController::getL3Pressed() {
	return (!l3Last)&&(l3Now);
}

bool MasterXboxController::getR3Pressed() {
	return (!r3Last)&&(r3Now);
}

bool MasterXboxController::getLeftTriggerPressed() {
	return (!leftTriggerLast)&&(leftTriggerNow);
}

bool MasterXboxController::getRightTriggerPressed() {
	return (!rightTriggerLast)&&(rightTriggerNow);
}

bool MasterXboxController::getXHeld() {
	return xLast&&xNow;
}

bool MasterXboxController::getYHeld() {
	return yLast&&yNow;
}

bool MasterXboxController::getAHeld() {
	return aLast&&aNow;
}

bool MasterXboxController::getBHeld() {
	return bLast&&bNow;
}

bool MasterXboxController::getStartHeld() {
	return startLast&&startNow;
}

bool MasterXboxController::getBackHeld() {
	return backLast&&backNow;
}

bool MasterXboxController::getLeftBumperHeld() {
	return leftBumperLast&&leftBumperNow;
}

bool MasterXboxController::getRightBumperHeld() {
	return rightBumperLast&&rightBumperNow;
}

bool MasterXboxController::getL3Held() {
	return l3Last&&l3Now;
}

bool MasterXboxController::getR3Held() {
	return r3Last&&r3Now;
}

bool MasterXboxController::getLeftTriggerHeld() {
	return leftTriggerLast&&leftTriggerNow;
}

bool MasterXboxController::getRightTriggerHeld() {
	return rightTriggerLast&&rightTriggerNow;
}

float MasterXboxController::getAxisTriggerRight() {
	return rstick.GetRawAxis(AXIS_TRIGGER_RIGHT);
}

float MasterXboxController::getAxisTriggerLeft() {
	return rstick.GetRawAxis(AXIS_TRIGGER_LEFT);
}

bool MasterXboxController::isButtonHeld(int &debounceCounter, bool rawValue) {
	if (rawValue) {
		debounceCounter++;
		if (debounceCounter>DEBOUNCE_COUNT_LIMIT) return true;
	}
	else { //we are still debouncing...
		debounceCounter=0;
	}
	return false;
}

