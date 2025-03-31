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

    while (true) {
        Sleep(0.5);
        lightDetector.debugVisualizeLineState();
    }
    // stateMachine.lineFollow(35, &lightDetector);

	return 0;
}
