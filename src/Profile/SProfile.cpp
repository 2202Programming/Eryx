/*
 * SProfile.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: lazar
 */

#include <Profile/SProfile.h>

SProfile::SProfile() {
	labels = new std::vector<std::string>();
	values = new std::vector<std::string>();
	setValue("MOTORFL", "1");
	setValue("MOTORFR", "2");
	setValue("MOTORBL", "3");
	setValue("MOTORBR", "4");
}

SProfile::~SProfile() {

}

std::string SProfile::getValue(std::string label){
	int x = 0;
	for (int i = 0; i < labels->size(); i++)
	{
		if (labels->at(i).compare(label) == 0)
		{
			x = i;
		}
	}

	return values->at(x);
}
int SProfile::getInt(std::string label){
	std::string x = getValue(label);
	if(x.compare("")==0){
		return -999;
	}
	return std::stoi(getValue(label));
}

float SProfile::getFloat(std::string label){
	return std::stof(getValue(label));
}

bool SProfile::getBool(std::string label){
	return getValue(label).at(0) == '1';
}

bool SProfile::setValue(std::string label, std::string value){
	labels->push_back(label);
	values->push_back(value);
	return true;
}
