#include <FEHServo.h>

#include <arm.h>

#define LERP_TICK_LEN 0.01
#define SWING_DEG 5

RobotArm::RobotArm() 
{
    arm.SetMin(min);
    arm.SetMax(max);
    // May or may not be true here
    rotation = 0;
}

void RobotArm::setRotation(float degrees) 
{
    rotation = degrees;
    arm.SetDegree(degrees);
}

void RobotArm::moveTo(float degrees, float seconds)
{
    // This int cast doesnt matter into the hundreths of seconds.
    int ticks = (int)(seconds/LERP_TICK_LEN);
    float perTick = (rotation-degrees)/(float)ticks;
    for (int i = 0; i < ticks; i++) 
    {
        setRotation(rotation+perTick);
    }
}

void RobotArm::swingDown()
{
    setRotation(rotation+SWING_DEG);
}

void RobotArm::swingUp()
{
    setRotation(rotation-SWING_DEG);
}