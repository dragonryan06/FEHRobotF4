#include <FEHLCD.h>

#include "light.h"

#define LINEFOLLOW_THRESH 2.7

unsigned int LightDetector::getCdSColor() 
{
    unsigned int color = BLACK;
    if (cdS.Value() < 1.5) 
    {
        color = BLUE;
    }
    if (cdS.Value() < 0.75)
    {
        color = RED;
    }
    return color;
}

float LightDetector::getCdSIntens()
{
    return cdS.Value();
}

bool LightDetector::getCenterLine()
{
    return optC.Value() > LINEFOLLOW_THRESH;
}

LightDetector::LINE_STATE LightDetector::getLineFollowState()
{
    lastState = state;
    state = UNKNOWN;
    if (optC.Value() > LINEFOLLOW_THRESH)
    {
        state = OK;
    }
    if (optR.Value() > LINEFOLLOW_THRESH)
    {
        state = TOO_LEFT;
    }
    if (optL.Value() > LINEFOLLOW_THRESH)
    {
        state = TOO_RIGHT;
    }
    return state;
}

LightDetector::LINE_STATE LightDetector::getLastLineState()
{
    return lastState;
}

void LightDetector::debugVisualizeLineState()
{
    if (optL.Value() > LINEFOLLOW_THRESH)
    {
        LCD.SetFontColor(GREEN);
        LCD.FillRectangle(0,0,106,240);
    } else 
    {
        LCD.SetFontColor(RED);
        LCD.FillRectangle(0,0,106,240);
    }
    if (optC.Value() > LINEFOLLOW_THRESH) 
    {
        LCD.SetFontColor(GREEN);
        LCD.FillRectangle(106,0,213,240);
    } else 
    {
        LCD.SetFontColor(RED);
        LCD.FillRectangle(106,0,213,240);
    }
    if (optR.Value() > LINEFOLLOW_THRESH)
    {
        LCD.SetFontColor(GREEN);
        LCD.FillRectangle(213,0,320,240);
    } else
    {
        LCD.SetFontColor(RED);
        LCD.FillRectangle(213,0,320,240);
    }
    LCD.SetFontColor(BLACK);
    LCD.DrawVerticalLine(106,0,240);
    LCD.DrawVerticalLine(213,0,240);
    LCD.SetFontColor(WHITE);
}