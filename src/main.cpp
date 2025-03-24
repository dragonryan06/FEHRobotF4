#include <string.h>

#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHBattery.h>

#include "core/utility.h"
#include "core/movement.h"
#include "sensing/light.h"

#define VERSION_STR "v1.4.1 Milestone 3"
#define START_LIGHT_THRESH 2.5

StateMachine stateMachine;
LightDetector lightDetector;

/**
 * Waits for the start light, then drives to the upper
 * level and positions itself ready to back into the window.
 */
void cue1()
{
    LCD.WriteLine("CUE 1: Waiting for light");
    while (lightDetector.getCdSIntens() > START_LIGHT_THRESH);
    LCD.WriteLine("CUE 1: Moving!");
    // Turn to face the ramp
    stateMachine.turn(86);
    // Drive to and up the ramp
    stateMachine.drive(35, 39.75);
    // Pivot to align with the window
    stateMachine.pivotL(122);
}

/**
 * Backs into the window, opening it, then pulls around to
 * put the handle on the other side of the block, closing
 * it again.
 */
void taskWindow()
{
    // Reverse to the window
    stateMachine.drive(-35, 6);
    // HIT the window!!
    stateMachine.drive(-35, -100, 1);
    stateMachine.drive(-35, -60, 7);
    // Turn all the way around to be on the other side
    stateMachine.drive(35, 9);
    stateMachine.pivotL(15);
    stateMachine.drive(-35, 11);
    stateMachine.pivotR(-30);
    stateMachine.drive(100, 35, 0.75);
    stateMachine.pivotL(-5, 100);
    stateMachine.pivotL(-50);
}

int main(void)
{
    LCD.Clear(BLACK);
    LCD.WriteRC(VERSION_STR, 0, (25-strlen(VERSION_STR))*0.5 + 1);
    LCD.WriteRC("Battery: ", 1, 8);
    LCD.WriteRC((int)(Battery.Value()*100.0/11.2), 1, 17);
    LCD.WriteRC("%", 1, 19);
    LCD.WriteRC("(TAP ANYWHERE TO START)", 5, 2);

    waitForTouch();
    LCD.Clear(BLACK);

    stateMachine.drive(50.0);

    // LCD.WriteLine("Executing CUE 1");
    // cue1();
    
    // LCD.WriteLine("Executing TASK WINDOW");
    // taskWindow();

	return 0;
}
