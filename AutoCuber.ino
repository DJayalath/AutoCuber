#include "MotorDriver.h"

MotorDriver M1 = MotorDriver(3, 4);

void setup()
{
}

void loop()
{
	M1.Turn(Direction::ACW, 360, 1000);
	delay(500);
	M1.Turn(Direction::CW, 360, 1000);
	delay(500);
}