#pragma once
#include <FEHServo.h>

/**
 * A class for handling the robot's front arm; wraps
 * FEHServo to add functionality for moving the arm more
 * slowly and such.
 */
class RobotArm 
{
    public:
        /**
         * Initializes the servo
         */
        RobotArm();

        /**
         * Turns the servo as fast as it can go to the
         * provided angle (0-180 deg).
         * 
         * ( FEHServo.SetDegree(float) )
         */
        void setRotation(float degrees);

        /**
         * Turns the servo to the provided angle, interpolating
         * over the given time. (moves more slowly)
         * 
         * !!DOES NOT RETURN UNTIL COMPLETE!!
         */
        void moveTo(float degrees, float seconds);

        /**
         * Swings the arm down slightly from its current
         * position, at max speed.
         */
        void swingDown();

        /**
         * Swings the arm up slightly from its current
         * position, at max speed.
         */
        void swingUp();
    private:
        const int min = 600;
        const int max = 2150;
        float rotation;
        FEHServo arm { FEHServo::Servo0 };
};