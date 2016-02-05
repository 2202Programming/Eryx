/*
 * DProfile.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: lazar
 */

#include <Profile/DProfile.h>

DProfile::DProfile() {
	remakeIndex();
}

DProfile::~DProfile() {
	generateIndex();
	delete master;
}

std::string DProfile::getValue(std::string label){
	profileNode *temp = master;
	while(temp !=NULL){
		if(temp->label.compare(label) == 1){
			return temp->value;
		}
	}
	return "null";
}

int DProfile::getInt(std::string label){
	return std::stoi(getValue(label));
}

float DProfile::getFloat(std::string label){
	return std::stof(getValue(label));
}

bool DProfile::getBool(std::string label){
	return getValue(label).at(0) == '1';
}

bool DProfile::setValue(std::string label, std::string value){
	bool alreadyExists = true;
	if(getValue(label).compare("null") == 0){
		alreadyExists = false;

	}
	return alreadyExists;
}

void DProfile::remakeIndex(){
	//TODO
}

void DProfile::generateIndex(){
	//TODO
}

