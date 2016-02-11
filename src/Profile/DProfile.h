
#pragma once

#include "Profile/IProfile.h"
#include <iostream>
#include <fstream>
#include <string>

class DProfile :
	public IProfile
{
public:
	DProfile();
	~DProfile();

	std::string getValue(std::string label);
	bool setValue(std::string label, std::string value);

private:
	profileNode *master = NULL;

	void findIndex();
	void generateIndex();

private:

};

