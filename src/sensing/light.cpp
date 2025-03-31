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

void LightDetector::debugVisualizeLineState()
{
    if (optR.Value() > 2.6)
    {
        LCD.SetFontColor(GREEN);
        LCD.FillRectangle(0,0,106,240);
    } else 
    {
        LCD.SetFontColor(RED);
        LCD.FillRectangle(0,0,106,240);
    }
    if (optC.Value() > 2.6) 
    {
        LCD.SetFontColor(GREEN);
        LCD.FillRectangle(106,0,213,240);
    } else 
    {
        LCD.SetFontColor(RED);
        LCD.FillRectangle(106,0,213,240);
    }
    if (optL.Value() > 2.6)
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