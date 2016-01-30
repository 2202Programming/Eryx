/*
 * IProfile.h
 *
 *  Created on: Jan 30, 2016
 *      Author: lazar
 */

#ifndef SRC_INTEGRATION_IPROFILE_H_
#define SRC_INTEGRATION_IPROFILE_H_
#include "targetGiver.h"

class IProfile{
public:
	IProfile();
	virtual ~IProfile();

	virtual std::string getValue(std::string value);
	virtual int getInt(std::string value);
	virtual float getFloat(std::string value);
	virtual bool getBool(std::string value);

};

#endif /* SRC_INTEGRATION_IPROFILE_H_ */
