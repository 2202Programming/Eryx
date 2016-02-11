/*
* IProfile.h
*
*  Created on: Jan 30, 2016
*      Author: lazar
*/

#ifndef SRC_PROFILE_IPROFILE_H_
#define SRC_PROFILE_IPROFILE_H_

#include <string>

class IProfile {

public:
	IProfile();
	virtual ~IProfile();

	virtual std::string getValue(std::string label) { return "null"; }

	virtual bool setValue(std::string label, std::string value) { return false; }

	virtual int getInt(std::string label) {
		std::string value = getValue(label);
		try
		{
			return std::stoi(getValue(label));
		}
		catch (...)
		{
			return -999;
		}
	}

	virtual float getFloat(std::string label) {
		std::string value = getValue(label);
		try
		{
			return std::stof(getValue(label));
		}
		catch (...)
		{
			return -999.0f;
		}
	}

	virtual bool getBool(std::string label) {
		std::string value = getValue(label);
		if (value == "ON") return true;
		if (value == "TRUE") return true;
		if (value == "SET") return true;
		if (value == "1") return true;
		return false;
	}

};

class profileNode {
public:
	std::string label;
	std::string value;
	profileNode *parent;
	profileNode(std::string nl, std::string nv) {
		label = nl;
		value = nv;
		parent = NULL;
	}
	profileNode(std::string nl, std::string nv, profileNode *nn) : profileNode(nl, nv)
	{
		parent = nn;
	}
};


#endif /* SRC_PROFILE_IPROFILE_H_ */
