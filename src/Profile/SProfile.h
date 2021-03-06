/*
* SProfile.h
*
*  Created on: Jan 30, 2016
*      Author: lazar
*/

#ifndef SRC_PROFILE_SPROFILE_H_
#define SRC_PROFILE_SPROFILE_H_

#include "Profile/IProfile.h"
#include <string>
#include <map>


class SProfile : public IProfile {
public:

	
	std::map<std::string, std::string> *storage;
	SProfile();
	~SProfile();

	std::string getValue(std::string label);

	bool setValue(std::string label, std::string value);

};

#endif /* SRC_PROFILE_SPROFILE_H_ */
