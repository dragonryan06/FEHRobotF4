#include <FEHMotor.h>

#include "movement.h"

StateMachine::StateMachine() 
{ 
    currentState = STATE::STOPPED;
}

void StateMachine::drive(int speed) 
{
    motorL.SetPercent(speed);
    motorR.SetPercent(speed);
    currentState = STATE::MOVING;
}

void StateMachine::stop() 
{
    motorL.Stop();
    motorR.Stop();
    currentState = STATE::STOPPED;
}