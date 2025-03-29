#include <string.h>

#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHBattery.h>
#include <FEHRCS.h>

#include "core/utility.h"
#include "core/movement.h"
#include "sensing/light.h"
#include "interaction/arm.h"

#define VERSION_STR "v1.5.4 Milestone 4"
#define START_LIGHT_THRESH 2.0

#define RCS_ID "0150F4CPJ"

StateMachine stateMachine;
LightDetector lightDetector;
RobotArm robotArm;

/**
 * Waits for the start light, then drives to and aligns with
 * the apple bucket on the tree stump.
 */
void cue1()
{
    LCD.WriteLine("CUE 1: Waiting for light");
    while (lightDetector.getCdSIntens() > START_LIGHT_THRESH);
    LCD.WriteLine("CUE 1: Moving!");
    // Lower arm
    robotArm.moveTo(136, 1.0);
    // Turn slightly
    stateMachine.pivotL(-11.5);
    // Drive up to stump
    stateMachine.drive(35, 16.0);
}

/**
 * Spears the apple bucket with the arm, then lifts it into
 * the air.
 */
void taskApplePickup() 
{
    stateMachine.drive(35, 1.0);
    Sleep(1.0);
    robotArm.moveTo(100, 1.0);
}

/**
 * Turns around from the trunk and drives up to the upper
 * level, aligning with the table.
 */
void cue2()
{
    stateMachine.pivotL(135);
    stateMachine.drive(35,15);
    stateMachine.turn(-80);
    Sleep(0.5);
    stateMachine.drive(40,40,28);
    Sleep(0.5);
    stateMachine.turn(-50);
    stateMachine.drive(35,15.5);
    robotArm.moveTo(160,1);
    stateMachine.turn(-10);
    robotArm.moveTo(180,1);
    stateMachine.turn(10);
    robotArm.moveTo(120,1);
    // Sleep(0.5);
    // stateMachine.drive(35,6);
    // Sleep(0.5);
    // stateMachine.turn(98);
    // Sleep(0.5);
    // stateMachine.drive(35,11);
}

/**
 * Sets the apple bucket down on the table.
 */
void taskAppleDropoff()
{
    // robotArm.moveTo(150,2.0);
    // stateMachine.drive(-35, 5);
}

/**
 * Moves over to and aligns with the fertlizer levers.
 */
void cue3()
{
    // stateMachine.turn(-60);
}

/**
 * Gets the correct lever using RCS, then flips that arm.
 * After 5 seconds, lifts the lever back up to where it
 * started at.
 */
void taskFertilizer()
{
    // Sleep(1.0);
    // arm.SetDegree(90);
    // Sleep(1.0);
    // arm.SetDegree(170);
    // Sleep(0.5);
    // stateMachine.drive(-35, 1.0);
    // arm.SetDegree(180);
    // Sleep(0.5);
    // arm.SetDegree(100);
    // Sleep(0.5);
}

int main(void)
{
    // RCS builtin setup menu
    //RCS.InitializeTouchMenu(RCS_ID);
    // Our setup menu
    LCD.Clear(BLACK);
    LCD.WriteRC(VERSION_STR, 0, (25-strlen(VERSION_STR))*0.5 + 1);
    LCD.WriteRC("Battery: ", 1, 8);
    LCD.WriteRC((int)(Battery.Value()*100.0/11.2), 1, 17);
    LCD.WriteRC("%", 1, 19);
    LCD.WriteRC("(TAP ANYWHERE TO START)", 5, 2);
    // Wait for tap to ready light listener
    waitForTouch();
    LCD.Clear(BLACK);

    LCD.WriteLine("Executing CUE 1");
    cue1();
    LCD.WriteLine("Executing TASK ApplePickup");
    taskApplePickup();
    LCD.WriteLine("Executing CUE 2");
    cue2();
    LCD.WriteLine("Executing TASK AppleDropOff");
    taskAppleDropoff();
    LCD.WriteLine("Executing CUE 3");
    cue3();
    LCD.WriteLine("Executing TASK Fertilizer");
    taskFertilizer();
    LCD.WriteLine("DONE!");

	return 0;
}
