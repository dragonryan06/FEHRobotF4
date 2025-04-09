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

#define VERSION_STR "v1.6.5 FINAL"
#define START_LIGHT_THRESH 2.0

#define RCS_ID "0150F4CPJ"

StateMachine stateMachine;
LightDetector lightDetector;
RobotArm robotArm;

/**
 * Moves over to the composter from
 * the start point.
 */
void cue1()
{
    LCD.WriteLine("CUE 1: Waiting for light");
    while (lightDetector.getCdSIntens() > START_LIGHT_THRESH);
    LCD.WriteLine("CUE 1: Moving!");
    stateMachine.drive(35, 11.0);
    stateMachine.turn(-89);
    stateMachine.drive(35, 3.0);
}

/**
 * Turns the composter by repeatedly 
 * pressing down on its paddles with
 * the servo arm.
 */
void taskComposter()
{
    robotArm.moveTo(75, 1.0);
    robotArm.moveTo(180, 0.5);
    for (int i = 0; i < 3; i++)
    {
        stateMachine.drive(-35, 1.0);
        robotArm.moveTo(75, 1.0);
        stateMachine.turn(-0.1);
        stateMachine.drive(35, 1.0);
        robotArm.moveTo(180, 0.5);
    }
    // robotArm.moveTo(75, 1.0);
    // for (int i = 0; i < 4; i++)
    // {
    //     stateMachine.drive(-35, 1.0);
    //     robotArm.moveTo(180, 1.0);
    //     stateMachine.turn(-0.1);
    //     stateMachine.drive(35, 1.0);
    //     robotArm.moveTo(75, 1.0);
    // }
    robotArm.moveTo(180, 0.5);
    stateMachine.drive(-35, 0.75);
}

/**
 * Moves from the composter to the window
 * wall, using it to align with the apple 
 * bucket pickup.
 */
void cue2()
{
    robotArm.moveTo(0, 0.5);
    stateMachine.turn(135);
    stateMachine.drive(35, 10.0);
    // Align with the wall
    stateMachine.drive(25);
    Sleep(1.5);
    stateMachine.stop();
    stateMachine.drive(-35, 1);
    stateMachine.pivotR(100);
}

/**
 * Drives towards and picks up the 
 * apple bucket, then puts it back down.
 */
void taskAppleBucketPickup() 
{
    robotArm.moveTo(120, 1.0);
    stateMachine.drive(20, 9.0);
    stateMachine.drive(20);
    Sleep(0.5);
    stateMachine.stop();
    robotArm.moveTo(30, 1.0);
    robotArm.moveTo(120, 1.0);
    stateMachine.drive(-20, 4.0);
    robotArm.moveTo(0, 1.0);
}

/**
 * Aligns with the wall then climbs the ramp, turning
 * to align with the humidifier.
 */
void cue3()
{
    stateMachine.turn(-150);
    stateMachine.drive(35, 12.0);
    stateMachine.turn(-30);
    stateMachine.drive(35, 5.0);
    stateMachine.drive(35);
    Sleep(1.0);
    stateMachine.stop();
    stateMachine.turn(-90);
    // drive up ramp
    stateMachine.drive(35, 32.0);
    stateMachine.turn(-110);
    breakpoint();
}

/**
 * Follows the line to the color light, taking a reading
 * before then pressing one of the two buttons on the humidifier.
 */
void taskHumidifier()
{
    LCD.WriteLine("DEBUG: Driving a base distance!");
    stateMachine.drive(20, 2.0);
    LCD.WriteLine("DEBUG: Driving till line found!");
    stateMachine.driveUntilLineFound(20, &lightDetector);
    LCD.WriteLine("DEBUG: Following line!");
    stateMachine.lineFollow(20, &lightDetector);
    LCD.WriteLine("DEBUG: Driving a base distance!");
    stateMachine.drive(20, 5.0);
    // get color
    unsigned int color = lightDetector.getCdSColor();
    while (color == BLACK) { color = lightDetector.getCdSColor(); }
    if (color == RED) 
    {
        LCD.SetFontColor(RED);
        LCD.WriteLine("Saw RED!");
        LCD.SetFontColor(WHITE);
        stateMachine.turn(8);
    } else 
    {
        LCD.SetFontColor(BLUE);
        LCD.WriteLine("Saw BLUE!");
        LCD.SetFontColor(WHITE);
        stateMachine.turn(-8);
    }
    stateMachine.lineFollow(20, &lightDetector);
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

    robotArm.moveTo(0, 0.5);

    // LCD.WriteLine("Executing CUE 1");
    // cue1();
    // LCD.WriteLine("Executing TASK Composter");
    // taskComposter();
    // LCD.WriteLine("Executing CUE 2");
    // cue2();
    // LCD.WriteLine("Executing TASK ApplePickup");
    // taskAppleBucketPickup();
    // LCD.WriteLine("Executing CUE 3");
    // cue3();
    LCD.WriteLine("Executing TASK Humidifier");
    taskHumidifier();
    LCD.WriteLine("DONE!");

	return 0;
}
