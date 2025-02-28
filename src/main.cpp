#include <string.h>

#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "core/utility.h"
#include "core/movement.h"

#define VERSION_STR "v1.1.3 Milestone 1"

StateMachine stateMachine;

/**
 * Starting with the robot's back to the far right side of the 
 * outdoor area, drives in a straight line until it reaches 
 * the far left wall, then returns.
 */
void cue1() 
{
    stateMachine.drive(32, 27);
}

/**
 * Starting with the robot's front facing the ramp, drives all of
 * the way up until no drive surfaces are touching the ramp once
 * again.
 */
void cue2() 
{
    stateMachine.drive(32, 24.5);
}

/**
 * (BONUS STEP)
 * Starting at the top of the ramp, goes back down to the bottom of the
 * ramp, once again with no drive surfaces touching the ramp.
 */
void cue3() 
{
    stateMachine.drive(-32, 24.5);
}

int main(void)
{
    LCD.Clear(BLACK);
    LCD.WriteRC(VERSION_STR, 0, (25-strlen(VERSION_STR))*0.5 + 1);
    LCD.WriteRC("(TAP ANYWHERE TO START)", 5, 2);

    waitForTouch();
    LCD.Clear(BLACK);

    LCD.WriteRC("Executing CUE 1...",0,0);
    cue1();
    LCD.WriteRC("done",0,18);

    breakpoint();

    LCD.WriteRC("Executing CUE 2...",1,0);
    cue2();
    LCD.WriteRC("done",1,18);

    LCD.WriteRC("Executing CUE 3...",2,0);
    cue3();
    LCD.WriteRC("done",2,18);

	return 0;
}
