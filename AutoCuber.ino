#include "MotorDriver.h"
#include "RotaryEncoder.h"

MotorDriver M1 = MotorDriver(3, 4);
RotaryEncoder R = RotaryEncoder(7, 6, 5);
int speed = 1000;

void setup()
{
}

void loop()
{
	//switch (R.PollRotate()) {
	//case 1:
	//	M1.Turn(Direction::CW, 360 / 20, speed);
	//	break;
	//case -1:
	//	M1.Turn(Direction::ACW, 360 / 20, speed);
	//default:
	//	break;
	//}

	//if (R.PollSwitch()) {
	//	speed -= 100;
	//}

	M1.Turn(Direction::ACW, 50, 1000);
	delay(1000);
	M1.Turn(Direction::CW, 50, 1000);
	delay(1000);
}