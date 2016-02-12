/*
 * SimpleDrive.h
 *
 *  Created on: Feb 12, 2016
 *      Author: lazar
 */

#ifndef SRC_DRIVE_SIMPLEDRIVE_H_
#define SRC_DRIVE_SIMPLEDRIVE_H_

#include "IControl.h"
#include "Profile/IProfile.h"
#include "Xbox/IXbox.h"
#include "WPILib.h"


class SimpleDrive:  public IControl {
public:
	SimpleDrive(IProfile *p, IXbox *x);
	virtual ~SimpleDrive();

	void TeleopInit();
	void TeleopPeriodic();

private:
	IProfile *profile;
	IXbox *xbox;

	Spark *FLM, *FRM, *RLM, *RRM;

};

#endif /* SRC_DRIVE_SIMPLEDRIVE_H_ */
