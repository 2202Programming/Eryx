/*
 * Arm.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Beast Laptop
 */

#ifndef SRC_COMPONENTS_ARM_H_
#define SRC_COMPONENTS_ARM_H_

#include "IControl.h"
#include "Profile/IProfile.h"
#include "WPILib.h"
#include "Xbox/IXbox.h"

class Arm: public IControl {
public:
	Arm(IProfile * pro, IXbox *x);
	virtual ~Arm();

	void TeleopInit();
	void TeleopPeriodic();

private:
	IProfile *profile;
	IXbox *xbox;

	Talon *Lower;
	Talon *Upper;
	Talon *test1;
	Talon *test2;

	Encoder *encode;
	DigitalInput *limit;

};

#endif /* SRC_COMPONENTS_ARM_H_ */
