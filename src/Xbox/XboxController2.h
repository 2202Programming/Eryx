#ifndef XBOX_CONTROLLER_2_H
#define XBOX_CONTROLLER_2_H

#include "IXbox.h"
/**
 * DO NOT USE THIS!!!
 * USE IXBOX.h INSTEAD!!!
 * Thanks! :)
 */
class XboxController2 : IXbox {

public:
	//cannot call update
	virtual ~XboxController2()=0;
	//virtual ~XboxController2()=0 {}

	virtual bool getXPressed()=0;/*PRESSED AND HELD ARE NOT DEPENDENT ON HOW OFTEN THEY ARE CALLED*/
	virtual bool getXHeld()=0;
	virtual bool getYPressed()=0;
	virtual bool getYHeld()=0;
	virtual bool getAPressed()=0;
	virtual bool getAHeld()=0;
	virtual bool getBPressed()=0;
	virtual bool getBHeld()=0;
	virtual bool getStartPressed()=0;
	virtual bool getStartHeld()=0;
	virtual bool getBackPressed()=0;
	virtual bool getBackHeld()=0;

	virtual bool getLeftBumperPressed()=0;
	virtual bool getLeftBumperHeld()=0;
	virtual bool getRightBumperPressed()=0;
	virtual bool getRightBumperHeld()=0;
	virtual bool getR3Pressed()=0;
	virtual bool getR3Held()=0;
	virtual bool getL3Pressed()=0;
	virtual bool getL3Held()=0;

	virtual bool getLeftTriggerPressed()=0;
	virtual bool getLeftTriggerHeld()=0;
	virtual bool getRightTriggerPressed()=0;
	virtual bool getRightTriggerHeld()=0;

	virtual float getAxisLeftX()=0;
	virtual float getAxisLeftY()=0;
	virtual float getAxisRightX()=0;
	virtual float getAxisRightY()=0;

	virtual void setRumble(bool on)=0;
};

#endif
