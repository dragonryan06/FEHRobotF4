#pragma once

/**
 * Until the screen has been pressed down on, checks the 
 * state every cycle, then repeats the same process until
 * the screen press has been released.
 * 
 * (Synchronously awaits one tap).
 */
void waitForTouch();