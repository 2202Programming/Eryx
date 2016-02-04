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

	virtual std::string getValue(std::string label){return "null";}
	virtual int getInt(std::string label){return -999;}
	virtual float getFloat(std::string label){return -999.9;}
	virtual bool getBool(std::string label){return false;}

	virtual bool setValue(std::string label, std::string value){return false;}
};

class profileNode{
public:
	std::string label;
	std::string value;
	profileNode *parent;
	profileNode(std::string nl ,std::string nv){
		label = nl;
		value = nv;
		parent = NULL;
	}
	profileNode(std::string nl, std::string nv, profileNode *nn){
		profileNode(nl, nv);
		parent = nn;
	}
};


#endif /* SRC_PROFILE_IPROFILE_H_ */
