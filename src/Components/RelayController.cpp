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
	Red = new Relay(RelayIO::RELAY_RED, Relay::kForwardOnly);
	Blue = new Relay(RelayIO::RELAY_BLUE, Relay::kForwardOnly);
}

RelayController::~RelayController() {
	// TODO Auto-generated destructor stub
	delete Red;
	delete Blue;
}


void RelayController::TeleopInit()
{
	DriverStation::Alliance alligent = DriverStation::GetInstance().GetAlliance();
	switch(alligent){
	case DriverStation::kBlue:
		Red->Set(Relay::kOff);
		Blue->Set(Relay::kOn);
		break;
	case DriverStation::kRed:
		Red->Set(Relay::kOn);
		Blue->Set(Relay::kOff);
		break;
	case DriverStation::kInvalid:
		Red->Set(Relay::kOff);
		Blue->Set(Relay::kOn);
		break;
	}
}

void RelayController::AutonomousInit()
{
	DriverStation::Alliance alligent = DriverStation::GetInstance().GetAlliance();
	switch(alligent){
	case DriverStation::kBlue:
		Red->Set(Relay::kOff);
		Blue->Set(Relay::kOn);
		break;
	case DriverStation::kRed:
		Red->Set(Relay::kOn);
		Blue->Set(Relay::kOff);
		break;
	case DriverStation::kInvalid:
		Red->Set(Relay::kOff);
		Blue->Set(Relay::kOn);
		break;
	}
}

void RelayController::RobotInit()
{
	DriverStation::Alliance alligent = DriverStation::GetInstance().GetAlliance();
	switch(alligent){
	case DriverStation::kBlue:
		Red->Set(Relay::kOff);
		Blue->Set(Relay::kOn);
		break;
	case DriverStation::kRed:
		Red->Set(Relay::kOn);
		Blue->Set(Relay::kOff);
		break;
	case DriverStation::kInvalid:
		Red->Set(Relay::kOff);
		Blue->Set(Relay::kOn);
		break;
	}
}

void RelayController::DisabledInit()
{
	DriverStation::Alliance alligent = DriverStation::GetInstance().GetAlliance();
	switch(alligent){
	case DriverStation::kBlue:
		Red->Set(Relay::kOff);
		Blue->Set(Relay::kOn);
		break;
	case DriverStation::kRed:
		Red->Set(Relay::kOn);
		Blue->Set(Relay::kOff);
		break;
	case DriverStation::kInvalid:
		Red->Set(Relay::kOff);
		Blue->Set(Relay::kOn);
		break;
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
