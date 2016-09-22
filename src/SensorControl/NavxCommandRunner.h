//
//  NavxCommandRunner.h
//  Eryx
//
//  Created by Tom Lazar on 09-22-2016.
//
//

#ifndef NavxCommandRunner_h
#define NavxCommandRunner_h

#include <stdio.h>

#include "IControl.h"

class NavxCommandRunner
{
private:

public:
    NavxCommandRunner();
    ~NavxCommandRunner();
    bool RunCommand(stepBase);
protected:
  //All the Auto Methods
  //Drive Straight Methods
  void InitDriveStraight(driveStep *step);
  bool ExecDriveStraight(driveStep *step);
  bool GetDriveStraightContinue(float value);		//Support return the criteria to continue driveing
  double GetEncoderCount(float);							  //Return the current encoder count

  //Turn Methods
  void InitTurn(turnStep *step);
  bool ExecTurn(turnStep *step);

  //Shooting Methods
  void InitAutoShoot();
  bool ExecAutoShoot();

  //Targeting Methods
  void InitAutoTarget();
  bool AutoTarget();

  //Drive Straight with navx stabilization
  void InitExpDriveStraight();
  bool ExecExpDriveStraight(driveStep* ds);
  float GetPIDError();							//Support Return the offset from the correct path

  //Drive Throught Defence With Navx Heading to detect when the Pitch return to zero
  void InitDriveThroughDefence();
  bool ExecDriveThroughDefence();
  float getPitch();

  //DriveUntil it hits the wall
  void InitDriveTillHitsWall();
  bool ExecDriveTillHitsWall();

  //DANCE MODE DANCE DANCE DANCE DANCE DANCE DANCE DANCE DANCE DANCE DANCE DANCE DANCE
  void InitBeastModeDanceAttack();
  bool ExecBeastModeDanceAttack();
};


#endif /* NavxCommandRunner_h */
