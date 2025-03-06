#include <string.h>

#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "core/utility.h"
#include "core/movement.h"
#include "sensing/light.h"

#define VERSION_STR "v1.3.0 Milestone 2"
#define START_LIGHT_THRESH 0.5

StateMachine stateMachine;
LightDetector lightDetector;

/**
 * Waits for the start light, then drives to the upper
 * level and positions itself at the humidifier light.
 */
void cue1()
{
    LCD.WriteLine("CUE 1: Waiting for light");
    while (lightDetector.getCdSIntens() < START_LIGHT_THRESH);
    LCD.WriteLine("CUE 1: Moving!");
    // Turn to face the ramp
    stateMachine.turn(12345); // FIND ANGLE
    // Drive to and up the ramp
    stateMachine.drive(35, 12345); // FIND DISTANCE (possibly drive slower up the ramp? faster?)
    // Turn to face the humidifier light
    stateMachine.turn(12345); // FIND ANGLE
    // Get onto the followable line
    stateMachine.drive(35);
    while (lightDetector.getLineFollowState() == lightDetector.UNKNOWN);
    stateMachine.stop();
    // Follow the line to its end to straighten out
    stateMachine.lineFollow(35, &lightDetector);
    // Reverse a known distance, hopefully now straightened.
    stateMachine.drive(-35, 12345); // FIND DISTANCE
}

/**
 * Reads and displays the color of the humidifier light, 
 * then pushes the corresponding button in front of it.
 */
void taskHumidifier()
{
    // Wait for the light to be detected
    unsigned int color = lightDetector.getCdSColor();
    while (color == BLACK) { color = lightDetector.getCdSColor(); }

    if (color == RED)
    {
        // Display red and press red button
        LCD.Clear(RED);
        stateMachine.turn(12345); // FIND ANGLE
        stateMachine.drive(35, 12345); // FIND DISTANCE
    }
    else//                                 ALSO THESE BUTTONS HAVE LINES IN FRONT OF THEM!!
    {
        // Display blue and press blue button
        LCD.Clear(BLUE);
        stateMachine.turn(12345); // FIND ANGLE
        stateMachine.drive(35, 12345); // FIND DISTANCE
    }
    LCD.Clear(BLACK);
}

/**
 * Drives back to the lower level and positions itself 
 * in the start box, ready to press the final button.
 */
void cue2()
{
    // Turn around
    stateMachine.turn(12345); // FIND ANGLE
    // Drive back to ramp
    stateMachine.drive(35, 12345); // FIND DISTANCE
    // Turn to face down ramp
    stateMachine.turn(12345); // FIND ANGLE
    // Drive back to start box
    stateMachine.drive(35, 12345);
    // Turn to face stop button
    stateMachine.turn(12345); // FIND ANGLE
}

/**
 * When aligned with the stop button, presses it.
 */
void taskStop()
{
    stateMachine.drive(35, 12345); // FIND DISTANCE
}

int main(void)
{
    LCD.Clear(BLACK);
    LCD.WriteRC(VERSION_STR, 0, (25-strlen(VERSION_STR))*0.5 + 1);
    LCD.WriteRC("(TAP ANYWHERE TO START)", 5, 2);

    waitForTouch();
    LCD.Clear(BLACK);

    LCD.WriteLine("Executing CUE 1");
    cue1();
    
    LCD.WriteLine("Executing TASK Humidifier");
    taskHumidifier();

    LCD.WriteLine("Executing CUE 2");
    cue2();

    LCD.WriteLine("Pressing STOP!");
    taskStop();

	return 0;
}
