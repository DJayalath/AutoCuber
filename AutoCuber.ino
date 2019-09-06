#include "MotorDriver.h"
#include "RotaryEncoder.h"

MotorDriver M1 = MotorDriver(2, 3);
MotorDriver M2 = MotorDriver(4, 5);
MotorDriver M3 = MotorDriver(6, 7);
MotorDriver M4 = MotorDriver(8, 9);
MotorDriver M5 = MotorDriver(10, 11);
//MotorDriver M3 = MotorDriver(10, 11);
//MotorDriver M4 = MotorDriver(12, 13);
//MotorDriver M5 = MotorDriver(23, 22);
//MotorDriver M6 = MotorDriver(24, 25);
//RotaryEncoder R = RotaryEncoder(7, 6, 5);
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

	//M1.Turn(Direction::ACW, 50 * 8, 1000);
	//delay(100);
	//M2.Turn(Direction::CW, 360, 600);
	//delay(100);
	//M1.Turn(Direction::CW, 50 * 8, 1000);
	//delay(100);

	////M4.Turn(Direction::ACW, 50 * 8, 1000);
	////delay(100);
	//M3.Turn(Direction::CW, 360, 600);
	//delay(100);
	////M4.Turn(Direction::CW, 50 * 8, 1000);
	////delay(100);

	//M6.Turn(Direction::ACW, 50 * 8, 1000);
	//delay(100);
	////M5.Turn(Direction::CW, 360, 600);
	////delay(100);
	//M6.Turn(Direction::CW, 50 * 8, 1000);
	//delay(100);
	

	M1.Turn(Direction::ACW, 360, 1000);
	delay(500);
	M1.Turn(Direction::CW, 720, 1000);
	delay(500);
	M2.Turn(Direction::ACW, 50 * 8, 1000);
	delay(100);
	M2.Turn(Direction::CW, 50 * 8, 1000);
	delay(100);

	M3.Turn(Direction::ACW, 360, 1000);
	delay(500);
	M3.Turn(Direction::CW, 720, 1000);
	delay(500);
	M4.Turn(Direction::ACW, 50 * 8, 1000);
	delay(100);
	M4.Turn(Direction::CW, 50 * 8, 1000);
	delay(100);

	M5.Turn(Direction::ACW, 360, 1000);
	delay(500);
	M5.Turn(Direction::CW, 720, 1000);
	delay(500);
}