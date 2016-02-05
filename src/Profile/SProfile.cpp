/*
 * SProfile.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: lazar
 */

#include "SProfile.h"

SProfile::SProfile() {
	master = new profileNode("MOTORFL", "1", master);
	master = new profileNode("MOTORBL", "2", master);
	master = new profileNode("MOTORFR", "3", master);
	master = new profileNode("MOTORBR", "4", master);
	master = new profileNode("SET", "SET", master);
	master = new profileNode("TRUE", "SET", master);
	master = new profileNode("FLOAT", "42.0", master);
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
	return "";
}

bool SProfile::setValue(std::string label, std::string value){
	bool alreadyExists = true;
	if(getValue(label).compare("null") == 0){
		alreadyExists = false;

	}
	return alreadyExists;
}
