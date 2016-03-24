/*
 * LineReader.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: Beast
 */

#include <LineReader/LineReader.h>


LineReader::LineReader() {
	navx14=new DigitalInput(14);
}

LineReader::~LineReader() {
}

void LineReader::TeleopPeriodic() {
	SmartDashboard::PutBoolean("***NAVX14***", navx14->Get());
}
