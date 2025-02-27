#include <FEHLCD.h>
#include <FEHUtility.h>

#include "utility.h"

void waitForTouch()
{
    int _x, _y;
    // Wait for downpress
    while (!LCD.Touch(&_x,&_y));
    // Wait for release
    while (LCD.Touch(&_x,&_y));
}

void breakpoint() 
{
    int _x, _y;
    unsigned long tStart = TimeNowMSec();
    // Wait for downpress, flash screen
    while (!LCD.Touch(&_x,&_y)) 
    {
        // Approx. every other second
        if ((TimeNowMSec() - tStart)%2000 < 50) 
        {
            LCD.Clear(BLACK);
            LCD.SetFontColor(WHITE);
            LCD.WriteRC("BREAKPOINT", 6, 8);
        }
        else if ((TimeNowMSec() - tStart)%1000 < 50)
        {
            LCD.Clear(WHITE);
            LCD.SetFontColor(BLACK);
            LCD.WriteRC("BREAKPOINT", 6, 8);
        }
    }
    // Wait for release
    while (LCD.Touch(&_x,&_y));
    LCD.Clear(BLACK);
}