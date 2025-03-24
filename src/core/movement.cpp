#include <cmath>

#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHBattery.h>

#include "movement.h"
#include "../sensing/light.h"

#define COUNTS_PER_INCH 34
#define COUNTS_PER_DEG 2
#define TURN_SPEED 25
#define BATTERY_MAX 11.5

StateMachine::StateMachine() 
{ 
    currentState = STATE::STOPPED;
}

void StateMachine::adjustForBattery(float* speed)
{
    *speed *= (BATTERY_MAX/Battery.Voltage());
}

void StateMachine::drive(float speed) 
{
    adjustForBattery(&speed);
    motorL.SetPercent(-speed);
    motorR.SetPercent(speed);
    if (speed < 0) motorL.SetPercent(-speed-1);
    currentState = STATE::MOVING;
}

void StateMachine::drive(float speed, float inches)
{
    adjustForBattery(&speed);
    encoderL.ResetCounts();
    motorL.SetPercent(-speed);
    motorR.SetPercent(speed);
    currentState = STATE::MOVING;

    while (encoderL.Counts() < (int)(inches * COUNTS_PER_INCH));
    
    stop();
}

void StateMachine::drive(float speedL, float speedR, float inches)
{
    adjustForBattery(&speedL);
    adjustForBattery(&speedR);
    encoderL.ResetCounts();
    motorL.SetPercent(-speedL);
    motorR.SetPercent(speedR);
    currentState = STATE::MOVING;

    while (encoderL.Counts() < (int)(inches * COUNTS_PER_INCH));

    stop();
}

void StateMachine::lineFollow(float speed, LightDetector* lightDetector) 
{
    adjustForBattery(&speed);
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

    while (encoderL.Counts() < abs(deg)*COUNTS_PER_DEG);
    stop();
}

void StateMachine::pivotL(float deg) 
{
    currentState = STATE::TURNING;
    encoderR.ResetCounts();
    if (deg < 0)
    {
        motorR.SetPercent(TURN_SPEED);
    }
    else 
    {
        motorR.SetPercent(-TURN_SPEED);
    }
    while (encoderR.Counts() < abs(deg)*COUNTS_PER_DEG*2);
    stop();
}

void StateMachine::pivotR(float deg)
{
    currentState = STATE::TURNING;
    encoderL.ResetCounts();
    if (deg < 0)
    {
        motorL.SetPercent(-TURN_SPEED);
    }
    else 
    {
        motorL.SetPercent(TURN_SPEED);
    }
    while (encoderL.Counts() < abs(deg)*COUNTS_PER_DEG*2);
    stop();
}

void StateMachine::pivotL(float deg, float speed) 
{
    adjustForBattery(&speed);
    currentState = STATE::TURNING;
    encoderR.ResetCounts();
    if (deg < 0)
    {
        motorR.SetPercent(speed);
    }
    else 
    {
        motorR.SetPercent(-speed);
    }
    while (encoderR.Counts() < abs(deg)*COUNTS_PER_DEG*2);
    stop();
}

void StateMachine::pivotR(float deg, float speed)
{
    adjustForBattery(&speed);
    currentState = STATE::TURNING;
    encoderL.ResetCounts();
    if (deg < 0)
    {
        motorL.SetPercent(-speed);
    }
    else 
    {
        motorL.SetPercent(speed);
    }
    while (encoderL.Counts() < abs(deg)*COUNTS_PER_DEG*2);
    stop();
}