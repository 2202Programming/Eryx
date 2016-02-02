/*
 * SProfile.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: lazar
 */

#include <Profile/SProfile.h>

SProfile::SProfile() {
	master = new profileNode("MOTORFL", "1", master);
	master = new profileNode("MOTORBL", "2", master);
	master = new profileNode("MOTORFR", "3", master);
	master = new profileNode("MOTORBR", "4", master);

}

SProfile::~SProfile() {
	profileNode *temp = master;
	profileNode *test;
	while(temp != NULL){
		test = temp;
		temp = temp->parent;
		delete test;
	}
	delete temp;
}

std::string SProfile::getValue(std::string label){
	profileNode *temp = master;
	while(temp != NULL){
		if(temp->label.compare(label) == 0){
			return temp->value;
		}
		temp = temp->parent;
	}
	return "null";
}
int SProfile::getInt(std::string label){
	return std::stoi(getValue(label));
}

float SProfile::getFloat(std::string label){
	return std::stof(getValue(label));
}

bool SProfile::getBool(std::string label){
	return getValue(label).at(0) == '1';
}

bool SProfile::setValue(std::string label, std::string value){
	bool alreadyExists = true;
	if(getValue(label).compare("null") == 0){
		alreadyExists = false;

	}
	return alreadyExists;
}
