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
	*/

	setValue("MOTORFL", "1");
	setValue("MOTORBL", "2");
	setValue("MOTORFR", "3");
	setValue("MOTORBR", "4");
	setValue("SET", "SET");
	setValue("TRUE", "TRUE");
	setValue("FLOAT2", "42.0");
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
