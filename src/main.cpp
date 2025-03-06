#include <string.h>

#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "core/utility.h"
#include "core/movement.h"
#include "sensing/light.h"

#define VERSION_STR "v1.2.0 Milestone 2"
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

}

/**
 * Reads and displays the color of the humidifier light, 
 * then pushes the corresponding button in front of it.
 */
void taskHumidifier()
{

}

/**
 * Drives back to the lower level and positions itself 
 * in the start box, ready to press the final button.
 */
void cue2()
{

}

/**
 * When aligned with the stop button, presses it.
 */
void taskStop()
{

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
