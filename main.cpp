#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#define VERSION_STR "1.0.0 Milestone 1"

FEHMotor MotorL(FEHMotor::Motor2, 9.0);
FEHMotor MotorR(FEHMotor::Motor3, 9.0);



int main(void)
{
    LCD.Clear(BLACK);
    LCD.WriteLine(VERSION_STR);

    MotorL.SetPercent(20);
    MotorR.SetPercent(20);
    int x, y;
    while (!LCD.Touch(&x, &y));
    MotorL.Stop();
    MotorR.Stop();

	return 0;
}
