#pragma once
#include <FEHMotor.h>

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
         * Stops the robot in place
         */
        void stop();

        /**
         * Turns the robot in place 90 degrees to the 
         * left.
         */
        void turnLeft90();

        /**
         * Turns the robot in place 90 degrees to the
         * right.
         */
        void turnRight90();
    private:
        STATE currentState;
        FEHMotor motorL{ FEHMotor::Motor3, 9.0 };
        FEHMotor motorR{ FEHMotor::Motor2, 9.0 };
};