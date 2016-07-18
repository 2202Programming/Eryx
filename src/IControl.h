/*
 * IControl.h
 *
 *  Created on: Feb 7, 2015
 *      Author: Beasty
 */

#ifndef SRC_ICONTROL_H_
#define SRC_ICONTROL_H_


namespace Global
{
	const int telemetry = 1;
	/*
	 * 1 = Competition
	 * 2 = Debug
	 * 3 = Extreame Debug
	 */

	/*if (Global::telemetry  >= 1) { //Normal

		} else if (Global::telemetry >= 2){ //debug

		} else if (Global::telemetry >= 3) { //advanced debug

		}
		*/
}

class stepBase{
public:

	//Controls the type of steps that exist
	enum step{
		driveStraight,
		turn,
		target,
		shoot,
		stop,
		driveThroughDefence,
		experimentalDriveStraight,
		driveTillHitsWall,
		spinUp,
		BeastModeDanceAttack,
	};

	int stepNum;
	step command;
};

class driveStep: public stepBase{
public:
	float distance;
	float speed;

};

class turnStep:public stepBase{
public:
	float speed;
	float angle;
};


/**
 * IterativeRobot implements a specific type of Robot Program framework, extending the RobotBase class.
 *
 * The IterativeRobot class is intended to be subclassed by a user creating a robot program.
 *
 * This class is intended to implement the "old style" default code, by providing
 * the following functions which are called by the main loop, StartCompetition(), at the appropriate times:
 *
 * RobotInit() -- provide for initialization at robot power-on
 *
 * Init() functions -- each of the following functions is called once when the
 *                     appropriate mode is entered:
 *  - DisabledInit()   -- called only when first disabled
 *  - AutonomousInit() -- called each and every time autonomous is entered from another mode
 *  - TeleopInit()     -- called each and every time teleop is entered from another mode
 *  - TestInit()       -- called each and every time test is entered from another mode
 *
 * Periodic() functions -- each of these functions is called iteratively at the
 *                         appropriate periodic rate (aka the "slow loop").  The default period of
 *                         the iterative robot is synced to the driver station control packets,
 *                         giving a periodic frequency of about 50Hz (50 times per second).
 *   - DisabledPeriodic()
 *   - AutonomousPeriodic()
 *   - TeleopPeriodic()
 *   - TestPeriodic()
 *
 */

class IControl
{
public:
	/*
	 * The default period for the periodic function calls (seconds)
	 * Setting the period to 0.0 will cause the periodic functions to follow
	 * the Driver Station packet rate of about 50Hz.
	 */
	//Identity Profiles


	virtual void RobotInit(){} //
	virtual void DisabledInit(){}
	virtual void AutonomousInit(){}
	virtual void TeleopInit(){}
	virtual void TestInit(){}

	virtual void DisabledPeriodic(){}

	virtual void AutonomousPeriodic(){}
	virtual bool AutonomousPeriodic(stepBase *step) {
		return 1;
	}
	virtual void AutonomousExecute(){}
	virtual void TeleopPeriodic(){}
	virtual void TestPeriodic(){}


protected:

	virtual ~IControl(){}
	IControl(){}


};



#endif /* SRC_ICONTROL_H_ */
