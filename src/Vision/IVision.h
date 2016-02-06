/*
 * IVision.h
 *
 *  Created on: Feb 5, 2016
 *      Author: beast
 */

#ifndef SRC_VISION_IVISION_H_
#define SRC_VISION_IVISION_H_

class IVision:public IControl {

public:
	/*
	 * Triggers the aiming process on the Drivers Station
	 * Call this method and then wait until getDoneAiming() returns true
	 */
	virtual void startAiming();

	/*
	 * Returns true if the robot is done aiming, and false if it is not
	 */
	virtual bool getDoneAiming();

	/*
	 * Returns the number of degrees to the right that the robot should turn (relative to what it is currently facing)
	 * If the robot is to turn left, the number of degrees will be negative. This assumes that getDoneAiming() has
	 * already returned true;
	 */
	virtual float getDegreesToTurn();
};

#endif /* SRC_VISION_IVISION_H_ */
