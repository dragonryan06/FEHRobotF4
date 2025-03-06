#include <cmath>

#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>

#include "movement.h"
#include "../sensing/light.h"

#define COUNTS_PER_INCH 34
#define COUNTS_PER_DEG 2
#define TURN_SPEED 25

StateMachine::StateMachine() 
{ 
    currentState = STATE::STOPPED;
}

void StateMachine::drive(int speed) 
{
    motorL.SetPercent(-speed);
    motorR.SetPercent(speed);
    if (speed < 0) motorL.SetPercent(-speed-1);
    currentState = STATE::MOVING;
}

void StateMachine::drive(int speed, float inches)
{
    encoderL.ResetCounts();
    motorL.SetPercent(-speed);
    motorR.SetPercent(speed);
    // Reverse causes a bit of a veer
    if (speed < 0) motorL.SetPercent(-speed-1);
    currentState = STATE::MOVING;

    while (encoderL.Counts() < (int)(inches * COUNTS_PER_INCH));
    
    stop();
}

void StateMachine::lineFollow(int speed, LightDetector* lightDetector) 
{
    motorL.SetPercent(-speed);
    motorR.SetPercent(speed);
    currentState = STATE::MOVING;
    LightDetector::LINE_STATE state = lightDetector->getLineFollowState();
    while (state != LightDetector::UNKNOWN) 
    {
        switch (state) 
        {
            case LightDetector::OK:
                motorL.SetPercent(-speed);
                motorR.SetPercent(speed);
                break;
            case LightDetector::TOO_LEFT:
                motorL.SetPercent(-speed-1);
                motorR.SetPercent(speed-1);
                break;
            case LightDetector::TOO_RIGHT:
                motorL.SetPercent(-speed+1);
                motorR.SetPercent(speed+1);
                break;
        }
        state = lightDetector->getLineFollowState();
    }
    stop();
}

void StateMachine::stop() 
{
    motorL.Stop();
    motorR.Stop();
    currentState = STATE::STOPPED;
}

void StateMachine::turn(float deg)
{
    currentState = STATE::TURNING;
    encoderL.ResetCounts();
    if (deg < 0)
    {
        // Turn left
        motorL.SetPercent(TURN_SPEED);
        motorR.SetPercent(TURN_SPEED);
    }
    else
    {
        // Turn right
        motorL.SetPercent(-TURN_SPEED);
        motorR.SetPercent(-TURN_SPEED);
    }

    while (encoderL.Counts() < deg*COUNTS_PER_DEG);
    stop();
}