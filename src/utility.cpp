#include <FEHLCD.h>
#include "utility.h"

void waitForTouch()
{
    int _x, _y;
    // Wait for downpress
    while (!LCD.Touch(&_x,&_y));
    // Wait for release
    while (LCD.Touch(&_x,&_y));
}