/*
 * TimShooter.h
 *
 *  Created on: Feb 6, 2016
 *      Author: lazar
 */

#ifndef SRC_COMPONENTS_TIMSHOOTER_H_
#define SRC_COMPONENTS_TIMSHOOTER_H_

#include "WPILib.h"
#include "IControl.h"
#include "Profile/IProfile.h"
#include "Xbox/IXbox.h"

class TimShooter: public IControl {
public:
	TimShooter(IProfile *pro, IXbox *x);
	virtual ~TimShooter();

	void TeleopInit();
	void TeleopPeriodic();
	void DisabledInit();

private:


	void setMotors(float value);


	double state = 0.0;

	IProfile *profile;
	IXbox *xbox;

	Compressor *c;

	Jaguar *Spin1;
	Jaguar *Spin2;
	Victor *updown;

	Solenoid *safe;
	Solenoid *fire;
};

#endif /* SRC_COMPONENTS_TIMSHOOTER_H_ */
