/*
 * Drive.h
 *
 *  Created on: Jan 27, 2016
 *      Author: Beast
 */

#include "WPILib.h"
#include "IControl.h"
#include "IDrive.h"
#include "Profile/IProfile.h"
#include "Motor/Motor.h"
#include "Xbox/MasterXboxController.h"

#ifndef SRC_DRIVE_H_
#define SRC_DRIVE_H_

class Drive: public IDrive, public IControl {
public:
	Drive(IProfile *np);
	virtual ~Drive();

	void TeleopInit();
	void TeleopPeriodic();

	void readXboxTank();
	void readXboxArcadeT();
	void readXboxArcadeD();
	void updateMotors();

	float acceleration(float newS, float oldS);

	IProfile *profile;

	Motor *motor;
	MasterXboxController *xbox;

	double leftSpeed;
	double rightSpeed;
};

#endif /* SRC_DRIVE_H_ */
