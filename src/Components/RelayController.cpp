/*
 * RelayController.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: lazar
 */

#include <Components/RelayController.h>

namespace RelayIO {
const int RELAY_RED = 1;
const int RELAY_BLUE = 0;
}

RelayController::RelayController() {
	// TODO Auto-generated constructor stub
	Red = new Relay(RelayIO::RELAY_RED);
	Blue = new Relay(RelayIO::RELAY_BLUE);
}

RelayController::~RelayController() {
	// TODO Auto-generated destructor stub
	delete Red;
	delete Blue;
}

void RelayController::ToggleColor() {
	switch (currnet) {
	case RelayColor::neither:
		break; //TODO
	case RelayColor::blue:
		break; //TODO
	case RelayColor::red:
		break; // TODO
	}
}

void RelayController::setColor(RelayColor color) {
	currnet = color;
	switch (color) {
	case RelayColor::neither:
		break; //TODO
	case RelayColor::blue:
		Red->Set(Relay::kOn);
		Blue->Set(Relay::kOff);
		break;
	case RelayColor::red:
		Red->Set(Relay::kOff);
		Blue->Set(Relay::kOn);
		break;
	}
}

void RelayController::relayBlink(int speed) {

}

void RelayController::burnUp() {

}

void RelayController::stopBlink() {

}

void RelayController::TeleopInit()
{
	SmartDashboard::PutNumber("LED", 0);
	setColor(RelayColor::blue);
}

void RelayController::TeleopPeriodic()
{
	int x = SmartDashboard::GetNumber("LED", 0);
	RelayColor test;

	if(x == 0)test = RelayColor::blue;
	else if(x == 1)test = RelayColor::red;

	if (currnet != test)
	{
		setColor(test);
	}
}

/*
 * 	void ToggleColor();	//Swithchs the current color if it is set to neither it does nothing
 void setColor(RelayColor, bool); 	//Sets the selected color to the value
 void relayBlink(int); //Blinks the leds at a certain speed the int describle the number of cycles before it switchs

 void burnUp(); //Speed ups the frequency for 2s // Extra Credit
 void stopBlink(); //Stops Blinking
 *
 */
