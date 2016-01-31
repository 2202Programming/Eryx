/*
 * DProfile.h
 *
 *  Created on: Jan 30, 2016
 *      Author: lazar
 */

#ifndef SRC_PROFILE_DPROFILE_H_
#define SRC_PROFILE_DPROFILE_H_

#include <Profile/IProfile.h>

class DProfile: virtual public IProfile {
public:
	DProfile();
	virtual ~DProfile();

	std::string getValue(std::string label);
	int getInt(std::string label);
	float getFloat(std::string label);
	bool getBool(std::string label);

	void setValue(std::string label, std::string value);
};

#endif /* SRC_PROFILE_DPROFILE_H_ */
