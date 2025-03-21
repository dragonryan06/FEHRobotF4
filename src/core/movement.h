#pragma once
#include <FEHMotor.h>
#include <FEHIO.h>

#include "../sensing/light.h"

/**
 * A class for tracking and controlling the movement state of the robot.
 * (Wraps FEHMotor to handle our specific situation.)
 */
class StateMachine 
{
    public:
        enum STATE 
        {
            STOPPED,
            MOVING,
            TURNING
        };

        /**
         * Initializes the robot state.
         */
        StateMachine();

        /**
         * Moves the robot at the given speed % using 
         * the calibrated left-right ratio. A negative
         * percentage indicates reverse.
         */
        void drive(int speed);

        /**
         * Moves the robot a given number of inches at the given 
         * speed % using the calibrated left-right ratio. A 
         * negative percentage indicates reverse.
         * 
         * !!DOES NOT RETURN UNTIL COMPLETE!!
         */
        void drive(int speed, float inches);

        /**
         * Moves the robot a given number of inches at the given
         * speed %s, per-motor. A negative percentage indicates
         * reverse.
         * 
         * !!DOES NOT RETURN UNTIL COMPLETE!!
         */
        void drive(int speedL, int speedR, float inches);

        /**
         * Moves the robot along the line detected by the passed
         * LightDetector context until its state becomes UNKNOWN.
         * 
         * !!DOES NOT RETURN UNTIL COMPLETE!!
         */
        void lineFollow(int speed, LightDetector* lightDetector);

        /**
         * Stops the robot in place
         */
        void stop();

        /**
         * Turns the robot in place a number of degrees, negative
         * being to the left and positive being to the right.
         * Please call with a nonzero value of degrees obviously :)
         * 
         * !!DOES NOT RETURN UNTIL COMPLETE!!
         */
        void turn(float deg);

        /**
         * Turns the robot with the left wheel staying in place.
         * Please call with a nonzero value of degrees obviously :)
         * 
         * !!DOES NOT RETURN UNTIL COMPLETE!!
         */
        void pivotL(float deg);

        /**
         * Turns the robot with the right wheel staying in place.
         * Please call with a nonzero value of degrees obviously :)
         * 
         * !!DOES NOT RETURN UNTIL COMPLETE!!
         */
        void pivotR(float deg);
    private:
        STATE currentState;
        FEHMotor motorL{ FEHMotor::Motor1, 9.0 };
        FEHMotor motorR{ FEHMotor::Motor2, 9.0 };
        DigitalEncoder encoderL{ FEHIO::P0_0 };
        DigitalEncoder encoderR{ FEHIO::P1_0 };
};