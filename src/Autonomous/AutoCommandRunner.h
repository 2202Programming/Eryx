#pragma once

#include "WPILib.h"
#include "Profile/IProfile.h"
#include "IControl.h"
#include <vector>
#include <Xbox/IXbox.h>
#include <Profile/IProfile.h>
#include <AHRS.h>
#include <Vision/IVision.h>
#include "Shooter/Shooter.h"
#include "WPILib.h"
#include <math.h>
#include <list>
#include "SensorControl/Artificial.cpp"
#include <ctime>

#define ENCODER_PULSE_DISTANCE 151.2f

class EncoderPackage : public IControl
{
public:
    Encoder *Left;
    Encoder *Right;
    Encoder *BackLeft;
    Encoder *BackRight;

    long int previousTime;

    bool DEBUG = true;

    EncoderPackage(Encoder *nL, Encoder *nR, Encoder *nBL, Encoder *nBR)
    {
        Left = nL;
        Right = nR;
        BackLeft = nBL;
        BackRight = nBR;

        Left.SetDistancePerPulse(ENCODER_PULSE_DISTANCE);
        Right.SetDistancePerPulse(ENCODER_PULSE_DISTANCE);
        BackLeft.SetDistancePerPulse(ENCODER_PULSE_DISTANCE);
        BackRight.SetDistancePerPulse(ENCODER_PULSE_DISTANCE);
    }

    void Display()
    {   
        if(DEBUG)
        {
            struct timeval tp;
            gettimeofday(&tp, NULL);
            long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

            if(previousTime == NULL)    //If their is no previousTime set it to the current time
                previousTime = ms;
            
            if(previousTime - ms > 1000)   //Only update these values once every second should save CPU
            {        
                previousTime = ms;
                SmartDashboard::PutString("Left Encoder", Left.GetDistance());
                SmartDashboard::PutString("Right Encoder", Right.GetDistance());
                SmartDashboard::PutString("BackLeft Encoder", BackLeft.GetDistance());
                SmartDashboard::PutString("BackRight Encoder", BackRight.GetDistance());
            }
        }
    }

    void TeleopPeriodic()
    {
        Display();
    }

    void AutonomousPeriodic()
    {
        Display();
    }

    double GetAvarageDistance()
    {
        return (Left.GetDistance() + Right.GetDistance() + BackLeft.GetDistance() + BackRight.GetDistance()) / 4;
    }

    double GetLeftAvarage()
    {
        return (Left.GetDistance() + BackLeft.GetDistance()) / 2;
    }
    
    double GetRightAvarage()
    {
        return (Right.GetDistance() + BackRight.GetDistance()) / 2;
    }
};

class AutoCommandRunner : public IControl
{
public:
    
private:
    Shooter *_shooter;              //Main Shooter
    IXbox *_xbox;                   //Xbox Controller
    AHRS *_ahrs;                    //Nax-MXP Gyro/Accelameter/Compas
    PIDController *turnController;  //Turn Controller
    IVision *_vision;               //Vision Made by @SecondThread

    bool DEBUG = false;

    void AutonomousInit();
    void AutonomousPeriodic();

};
