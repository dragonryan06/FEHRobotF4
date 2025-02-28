#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>

#include "movement.h"

#define COUNTS_PER_INCH 34

StateMachine::StateMachine() 
{ 
    currentState = STATE::STOPPED;
}

void StateMachine::drive(int speed) 
{
    motorL.SetPercent(speed);
    motorR.SetPercent(-speed);
    currentState = STATE::MOVING;
}

void StateMachine::drive(int speed, float inches)
{
    encoderL.ResetCounts();
    motorL.SetPercent(speed);
    motorR.SetPercent(-speed);
    currentState = STATE::MOVING;
    while (encoderL.Counts() < (int)(inches * COUNTS_PER_INCH)) {}
    motorL.Stop();
    motorR.Stop();
    currentState = STATE::STOPPED;
}

void StateMachine::stop() 
{
    motorL.Stop();
    motorR.Stop();
    currentState = STATE::STOPPED;
}