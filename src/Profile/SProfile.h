/*
 * SProfile.h
 *
 *  Created on: Jan 30, 2016
 *      Author: lazar
 */

#ifndef SRC_PROFILE_SPROFILE_H_
#define SRC_PROFILE_SPROFILE_H_

#include <Profile/IProfile.h>
#include <string>

class SProfile: public IProfile {
public:
	SProfile();
	~SProfile();

	std::string getValue(std::string label);
	int getInt(std::string label);
	float getFloat(std::string label);
	bool getBool(std::string label);

	void setValue(std::string label, std::string value);
};

#endif /* SRC_PROFILE_SPROFILE_H_ */
