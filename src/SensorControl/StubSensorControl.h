/*
 * StubSensorControl.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Beasty
 */

#ifndef SRC_SENSORCONTROL_STUBSENSORCONTROL_H_
#define SRC_SENSORCONTROL_STUBSENSORCONTROL_H_
#include "ISensorControl.h"

class StubSensorControl: public ISensorControl {
public:
	StubSensorControl();
	virtual ~StubSensorControl();
};

#endif /* SRC_SENSORCONTROL_STUBSENSORCONTROL_H_ */
