/*
 * LineReader.h
 *
 *  Created on: Mar 21, 2016
 *      Author: Beast
 */

#include <IControl.h>
#include <WPILib.h>

#ifndef SRC_LINEREADER_LINEREADER_H_
#define SRC_LINEREADER_LINEREADER_H_
class LineReader : public IControl {
public:
	LineReader();
	virtual ~LineReader();
	void TeleopPeriodic();
private:
	DigitalInput* navx14;
};

#endif
