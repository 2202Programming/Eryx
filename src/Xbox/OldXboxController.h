/*
 * XboxController.h
 *
 *  Created on: Jan 7, 2015
 *      Author: Beasty
 */

#ifndef OLD_XBOX_CONTROLLER_H
#define OLD_XBOX_CONTROLLER_H


/* This is the Header File for Xbox Controller*/

#define DEBOUNCER 15

#include "WPILib.h"


class OldXboxController  {
public:
	~OldXboxController() {}
	bool isLeftJogPressed();
	bool isRightJogPressed();
	bool isUpJogPressed();
	bool isDownJogPressed();
	bool isAPressed();
	bool isBPressed();
	bool isXPressed();
	bool isYPressed();
	bool isLBumperPressed();
	bool isRBumperPressed();
	bool isBackPressed();
	bool isStartPressed();
	bool isL3Pressed();
	bool isR3Pressed();
	bool isAHeld();
	bool isBHeld();
	bool isXHeld();
	bool isYHeld();
	bool isLBumperHeld();
	bool isRBumperHeld();
	bool isBackHeld();
	bool isStartHeld();
	bool isL3Held();
	bool isR3Held();
	bool isRightTriggerHeld();
	bool isRightTriggerPressed();
	bool isLeftTriggerHeld();
	float getAxisRightX();
	float getAxisRightY();
	float getAxisLeftX();
	float getAxisLeftY();
	float getAxisTrigger();
	Joystick* getLeftStick();
	Joystick* getRightStick();
	bool JogEnabled();
	bool isEndGame();
protected:
	OldXboxController(int stick);
private:
	Joystick lstick;
	Joystick rstick;
	int a;
	int b;
	int x;
	int y;
	int lb;
	int rb;
	int back;
	int start;
	int l3;
	int r3;
	int leftJog;
	int upJog;
	int rightJog;
	int downJog;
	int rightTrigger;
	int leftTrigger;
	int endGame;

	bool isButtonPressed(int &counter, bool rawValue, int debounceCount);
	bool isButtonPressed(int &counter, bool rawValue);
	bool isButtonHeld(int &counter, bool rawValue);
	bool isButtonHeld(int &counter, bool rawValue, int debounceCount);
};



#endif /* SRC_XBOXCONTROLLER_H_ */
