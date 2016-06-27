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

	enum Stratagy
	{
		Approach,
		Cross,
		Shoot,
	};

	CommandListMaker(IProfile *p);
	virtual ~CommandListMaker();

	void RobotInit();

	void makeBasic();
	void makeDefenceBreaker();
	void Experimental();
	void makeOakWoodSpecial();

	void Go(int x, Stratagy strat);

	vector<stepBase*>* getList();

	stepBase* getNextStep()
	{
		if (storage == NULL) return (stepBase*)NULL;
		if (currentStep < 0) return (stepBase*)NULL;
		if (currentStep >= (signed)storage->size()) return (stepBase*)NULL;
		int temp = currentStep;
		currentStep += 1;
		return storage->at(temp);
	}

	stepBase* getFirstStep()
	{
		currentStep = 0;
		return getNextStep();
	}


	int currentStep = 0;


private:
	const std::string ram = "Ramparts";
	const std::string low = "Low Bar";
	const std::string rock = "Rock Wall";
	const std::string port = "Portculis";
	const std::string chev = "Cheval de Frise";
	const std::string sall = "Sally Port";
	const std::string deb = "Rough Terrain";
	const std::string moat = "Moat";
	const std::string draw = "Drawbridge";

	const std::string pos1 = "Position 1";
	const std::string pos2 = "Position 2";
	const std::string pos3 = "Position 3";
	const std::string pos4 = "Position 4";
	const std::string pos5 = "Position 5";

	const std::string str_Approach = "Approach";
	const std::string  str_Cross = "Cross";
	const std::string str_Shoot = "Shoot";

	SendableChooser *autoPosition;
	SendableChooser *autoDefence;
	SendableChooser *stratChooser;



	vector<stepBase*>* storage;
	IProfile *profile;
};

#endif /* SRC_AUTONOMOUS_COMMANDLISTMAKER_H_ */
