/*
* SProfile.cpp
*
*  Created on: Jan 30, 2016
*      Author: lazar
*/

#include "Profile/SProfile.h"

SProfile::SProfile() 
{
	storage = new std::map<std::string, std::string>();

/*
	master = new profileNode("MOTORFL", "1", master);
	master = new profileNode("MOTORBL", "2", master);
	master = new profileNode("MOTORFR", "3", master);
	master = new profileNode("MOTORBR", "4", master);
	master = new profileNode("SET", "SET", master);
	master = new profileNode("TRUE", "SET", master);
	master = new profileNode("FLOAT", "42.0", master);
	master = new profileNode("ROBOT", "ARM", master);
	master = new profileNode("SPIN1", "5", master);
	master = new profileNode("SPIN2", "6", master);
	master = new profileNode("SAFE", "3", master);
	master = new profileNode("FIRE", "4", master);
	master = new profileNode("UPDOWN", "7", master);
	master = new profileNode("UPMAX", "7", master);
	master = new profileNode("DOWNMAX", "6", master);
	master = new profileNode("ARME1", "2", master);
	master = new profileNode("ARME2", "3", master);
	master = new profileNode("ARMT_UPPER", "2", master);
	master = new profileNode("ARMT_LOWER", "1", master);
	master = new profileNode("ARMT_LIMIT", "0", master);
*/
	setValue("MOTORFL", "1");
	setValue("MOTORBL", "2");
	setValue("MOTORFR", "3");
	setValue("MOTORBR", "4");
	setValue("SET", "SET");
	setValue("TRUE", "TRUE");
	setValue("FLOAT", "42.0");
	setValue("ROBOT", "ARM");
	setValue("SPIN1", "5");
	setValue("SPIN2", "6");
	setValue("SAFE", "3");
	setValue("FIRE", "4");
	setValue("UPDOWN", "7");
	setValue("UPMAX", "6");
	setValue("DOWNMAX","6");
	setValue("ARME1", "2");
	setValue("ARMT_UPPER", "2");
	setValue("ARMT_LOWER", "1");
	setValue("ARMT_LIMIT", "0");
}

SProfile::~SProfile() 
{
	
	delete storage;
	
}

std::string SProfile::getValue(std::string label)
{

	return storage->find(label)->second;
}
 
bool SProfile::setValue(std::string label, std::string value) 
{
	storage->insert(std::pair<std::string, std::string>(label, value));

	return true;
}
