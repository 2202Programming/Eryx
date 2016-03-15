/*
 * CommandListMaker.h
 *
 *  Created on: Feb 16, 2016
 *      Author: lazar
 */

#ifndef SRC_AUTONOMOUS_COMMANDLISTMAKER_H_
#define SRC_AUTONOMOUS_COMMANDLISTMAKER_H_

#include "WPILib.h"
#include "Profile/IProfile.h"
#include "IControl.h"
#include <vector>

using namespace std;
class CommandListMaker {
public:
	CommandListMaker(IProfile *p);
	virtual ~CommandListMaker();

	void RobotInit();

	void makeBasic();
	void makeDefenceBreaker();

	vector<stepBase*>* getList();

	SendableChooser *autoPosition;
	SendableChooser *autoDefence;

private:



	vector<stepBase*>* storage;
	IProfile *profile;
};

#endif /* SRC_AUTONOMOUS_COMMANDLISTMAKER_H_ */
