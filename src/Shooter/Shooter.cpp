/*
 * Shooter.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Daniel Owen
 */

#include <Shooter/Shooter.h>

#define RPM 2500
#define SOL_ACTIVATE DoubleSolenoid::kForward
#define SOL_DEACTIVATED DoubleSolenoid::kReverse

Shooter::Shooter(Motor *motor, IXbox *xbox, IProfile *p) {
	this->xbox = xbox;
	this->motor = motor;

	c = new Compressor();

	angleSol = new DoubleSolenoid(0, 1); //1
	trigger = new DoubleSolenoid(2, 3); //2
	intakeSol = new DoubleSolenoid(4, 5); //3

	/*
	 encFrontLeft = new Encoder(p->getInt("SHOOTERFL_ENC1"),
	 p->getInt("SHOOTERFL_ENC2"));
	 encFrontRight = new Encoder(p->getInt("SHOOTEFR_ENC1"),
	 p->getInt("SHOOTERLR_ENC2"));
	 encBackLeft = new Encoder(p->getInt("SHOOTERBL_ENC1"),
	 p->getInt("SHOOTERBL_ENC2"));
	 encBackRight = new Encoder(p->getInt("SHOOTERBR_ENC1"),
	 p->getInt("SHOOTERBR_ENC2"));
	 encFrontLeft->SetReverseDirection(p->getBool("SHOOTERFL_ENC1_INVERT")); //For test board
	 encFrontRight->SetReverseDirection(p->getBool("SHOOTERFR_ENC1_INVERT")); //For test board
	 encBackLeft->SetReverseDirection(p->getBool("SHOOTERBL_ENC1_INVERT")); //For test board
	 encBackRight->SetReverseDirection(p->getBool("SHOOTERBR_ENC1_INVERT")); //For test board */

	runShoot = false;
	runIntake = false;
	runTrigger = false;
	angle = false;
	intakePos = false;
	shot = false;
	leftSpeed = 0.0;
	rightSpeed = 0.0;
	intakeSpeed = 0.0;

}

Shooter::~Shooter() {
}

void Shooter::AutonomousInit() {
	motor->setShoot(0.0, 0.0);
	motor->setIntake(0.0);
	runShoot = false;

	c->Start();

	angleSol->Set(SOL_DEACTIVATED);
	angle = false;
	trigger->Set(SOL_DEACTIVATED);
	runTrigger = false;
	intakeSol->Set(SOL_DEACTIVATED);
	intakePos = false;
}

void Shooter::AutonomousPeriodic() {
	updateMotor2();
	setPnumatics();
	motor->setShoot(leftSpeed, rightSpeed);

	/*if (encFrontLeft->GetRate() > RPM) {
		runTrigger = true;
		shot = true;
	}*/
}

void Shooter::shoot() {
	runShoot = true;
	angle = true;
}

bool Shooter::hasShot() {
	if (shot == true) {
		shot = false;
		return true;
	}

	return false;
}

void Shooter::TeleopInit() {
	SmartDashboard::PutNumber("ShooterSpeed", 1.0);
	motor->setShoot(0.0, 0.0);
	motor->setIntake(0.0);
	runShoot = false;

	c->Start();

	angleSol->Set(SOL_DEACTIVATED);
	angle = false;
	trigger->Set(SOL_ACTIVATE);
	runTrigger = false;
	intakeSol->Set(SOL_DEACTIVATED);
	intakePos = false;
}

void Shooter::TeleopPeriodic() {
	readXbox();
	updateMotor2();
	setPnumatics();

	motor->setShoot(leftSpeed, rightSpeed);
	motor->setIntake(intakeSpeed);

	SmartDashboard::PutNumber("Shoot Left", leftSpeed);
	SmartDashboard::PutNumber("Shoot Right", rightSpeed);
	SmartDashboard::PutNumber("Intake Speed", intakeSpeed);

	SmartDashboard::PutBoolean("Angle", angle);
	SmartDashboard::PutBoolean("Trigger", trigger);
	SmartDashboard::PutBoolean("Intake", intakePos);

	/*SmartDashboard::PutNumber("Left Shoot Speed", encFrontLeft->GetRate());
	 SmartDashboard::PutNumber("Right Shoot Speed", encFrontRight->GetRate());
	 SmartDashboard::PutNumber("Left Shoot Speed", encBackLeft->GetRate());
	 SmartDashboard::PutNumber("Right Shoot Speed", encBackRight->GetRate()); */
}

void Shooter::readXbox() {
	//Toggle - not hold
	if (xbox->getR3Pressed()) { //Turn shooter on/off
		runShoot = !runShoot;
	}

	if (xbox->getRightTriggerPressed()) { //Toggle trigger
		runTrigger = !runTrigger;
	}

	if (xbox->getRightBumperPressed()) { //Up
		angle = !angle;
	}

	if (xbox->getLeftBumperPressed()) {	//Reverse Intake
		intakePos = !intakePos;
	}

	if (xbox->getBackHeld()) {	//Activate Piston
		runIntake = true;
	} else {
		runIntake = false;
	}
}

void Shooter::setPnumatics() {

	if (angle) {
		angleSol->Set(SOL_ACTIVATE); //Up
	} else {
		angleSol->Set(SOL_DEACTIVATED); //Down
	}

	if (runTrigger) {
		trigger->Set(SOL_DEACTIVATED);	//In
	} else {
		trigger->Set(SOL_ACTIVATE);	//Out
	}

	if (intakePos) {
		intakeSol->Set(SOL_ACTIVATE);	//Out
	} else {
		intakeSol->Set(SOL_DEACTIVATED);	//In
	}
}

/*void Shooter::updateMotor1() {
 double rateR = encFrontRight->GetRate();
 double rateL = encFrontLeft->GetRate();

 if (runShoot) {
 //Logic to keep the wheels within 150 of the desired RPM
 //Left side
 if (rateL < RPM) {
 if (rateL < RPM - 150)
 leftSpeed += 0.01;
 else
 leftSpeed += 0.005;

 } else if (rateL == RPM) {
 leftSpeed = 0.75;
 } else {
 if (rateL > RPM + 150)
 leftSpeed -= 0.01;
 else
 leftSpeed -= 0.005;
 }

 //Right Side
 if (rateR < RPM) {
 if (rateR < RPM - 150)
 rightSpeed += 0.01;
 else
 rightSpeed += 0.005;

 } else if (rateR == RPM) {
 rightSpeed = 0.75;
 } else {
 if (rateR > RPM + 150)
 rightSpeed -= 0.01;
 else
 rightSpeed -= 0.005;
 }
 } else {
 leftSpeed = 0.0;\

 rightSpeed = 0.0;
 }
 } */

void Shooter::updateMotor2() {
	float appliedSpeed = SmartDashboard::GetNumber("ShooterSpeed", 1.0);
	if (runShoot) {
		leftSpeed = appliedSpeed;
		rightSpeed = appliedSpeed;
	} else {
		leftSpeed = 0.0;
		rightSpeed = 0.0;
	}

	if (runIntake) {
		intakeSpeed = -0.88;
	} else {
		intakeSpeed = 0.0;
	}
}
