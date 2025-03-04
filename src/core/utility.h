#pragma once
#include <FEHUtility.h>

/**
 * Until the screen has been pressed down on, checks the 
 * state every cycle, then repeats the same process until
 * the screen press has been released.
 * 
 * (Synchronously awaits one tap).
 */
void waitForTouch();

/**
 * Functions similarly to waitForTouch, but clears and
 * slowly flashes the screen to indicate execution has
 * been paused for a debugging reason. Should not be used
 * in the final program.
 * 
 * !!CLEARS SCREEN!!
 */
void breakpoint();