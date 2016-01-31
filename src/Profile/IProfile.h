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

	virtual std::string getValue(std::string label);
	virtual int getInt(std::string label);
	virtual float getFloat(std::string label);
	virtual bool getBool(std::string label);

	virtual void setValue(std::string label, std::string value);
};

struct profileNode{
	std::string label;
	std::string value;
	profileNode(std::string nl ,std::string nv){
		label = nl;
		value = nv;
	}
};


#endif /* SRC_PROFILE_IPROFILE_H_ */
