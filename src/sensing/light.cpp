#include <FEHLCD.h>

#include "light.h"

unsigned int LightDetector::getCdSColor() 
{
    unsigned int color = BLACK;
    if (cdS.Value() < 2.0) 
    {
        color = BLUE;
    }
    if (cdS.Value() < 1.5)
    {
        color = RED;
    }
    return color;
}

float LightDetector::getCdSIntens()
{
    return cdS.Value();
}

LightDetector::LINE_STATE LightDetector::getLineFollowState()
{
    state = UNKNOWN;
    if (optC.Value() > 3)
    {
        state = OK;
    }
    if (optL.Value() > 2.7)
    {
        state = TOO_LEFT;
    }
    if (optR.Value() > 2.7)
    {
        state = TOO_RIGHT;
    }
    return state;
}