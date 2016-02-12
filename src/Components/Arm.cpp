/*
 * Arm.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Beast Laptop
 */

#include <Components/Arm.h>

Arm::Arm(IProfile * pro, IXbox *x) {
	profile = pro;
	xbox = x;

	encode = new Encoder(profile->getInt("ARME1"), profile->getInt("ARME2"));
	Upper = new Talon(2);
	Lower = new Talon(1);

	test1 = new Talon(3);
	test2 = new Talon(4);

	limit = new DigitalInput(profile->getInt("ARMT_LIMIT"));
}

Arm::~Arm() {
	// TODO Auto-generated destructor stub
}

void Arm::TeleopInit() {
	Upper->Set(0.0);
	Lower->Set(0.0);
	encode->Reset();
}

void Arm::TeleopPeriodic() {

	test1->Set(.5);
	test2->Set(.5);

	SmartDashboard::PutNumber("Distace", encode->GetDistance());
	SmartDashboard::PutNumber("Speed", encode->GetRate());

	float up, low;
	up = xbox->getAxisLeftY() * .7;
	low = xbox->getAxisRightY() * .7;

	SmartDashboard::PutNumber("Low", low);
	SmartDashboard::PutNumber("UP", up);
	bool goTo = xbox->getAHeld();

	SmartDashboard::PutBoolean("Limit", limit->Get());
	if (limit->Get()) {
		if (!goTo) {
			Upper->Set(up);
			Lower->Set(low);
		} else {
			double x = SmartDashboard::GetNumber("Location", .25);
			double y = encode->GetDistance();
			double speed = SmartDashboard::GetNumber("Speed Arm", .5);

			if (x > y) {
				Lower->Set(speed);
			} else {
				Lower->Set(-speed);
			}
		}
	}
	else{
		Upper->Set(0.0);
		Lower->Set(0.0);
	}
}
