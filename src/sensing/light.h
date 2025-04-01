#pragma once
#include <FEHIO.h>

/**
 * A wrapper class for AnalogInputPin that handles
 * the robot's three optosensors and CdS sensor.
 */
class LightDetector
{
    public:
        enum LINE_STATE
        {
            UNKNOWN,
            TOO_LEFT,
            TOO_RIGHT,
            OK
        };

        /**
         * Determines the color of the light under
         * the CdS sensor and returns an FEHLCD
         * value based on color.
         */
        unsigned int getCdSColor();

        /**
         * Returns the raw-er CdS cell Value().
         */
        float getCdSIntens();

        /**
         * Returns whether the robot sees a line in 
         * its center.
         */
        bool getCenterLine();

        /**
         * Checks all optosensors and the previous
         * LINE_STATE to determine what the current
         * LINE_STATE should be, and returns it.
         */
        LINE_STATE getLineFollowState();

        /**
         * Reads out the private state from the last
         * reading, useful for more context when the 
         * line disappears.
         */
        LINE_STATE getLastLineState();

        /**
         * Clears the screen and draws a colorful
         * image representing line following state.
         */
        void debugVisualizeLineState();

    private:
        LINE_STATE state = LINE_STATE::UNKNOWN;
        LINE_STATE lastState = LINE_STATE::UNKNOWN;
        AnalogInputPin cdS{ FEHIO::P3_0 };
        AnalogInputPin optR{ FEHIO::P2_0 };
        AnalogInputPin optC{ FEHIO::P2_2 };
        AnalogInputPin optL{ FEHIO::P2_4 };
};