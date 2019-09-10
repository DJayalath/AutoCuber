#include "MotorDriver.h"
#include "RotaryEncoder.h"
#include "CubeRotate.h"

MotorDriver M1 = MotorDriver(2, 3);
MotorDriver M2 = MotorDriver(4, 5);
MotorDriver M3 = MotorDriver(6, 7);
MotorDriver M4 = MotorDriver(8, 9);
MotorDriver M5 = MotorDriver(10, 11);
MotorDriver M6 = MotorDriver(12, 13);
MotorDriver M7 = MotorDriver(22, 23);
MotorDriver M8 = MotorDriver(24, 25);
//MotorDriver M3 = MotorDriver(10, 11);
//MotorDriver M4 = MotorDriver(12, 13);
//MotorDriver M5 = MotorDriver(23, 22);
//MotorDriver M6 = MotorDriver(24, 25);
//RotaryEncoder R = RotaryEncoder(7, 6, 5);
CubeRotate CR = CubeRotate(M2, M1, M4, M3, M6, M5, M8, M7);
int speed = 1000;

void setup()
{
	//CR.ShowAll();
	//CR.Scramble();
	CR.R(1, false);
	delay(1000);
	CR.L(1, false);
	delay(1000);
	CR.B(1, false);
	delay(1000);
	CR.Fr(1, false);
	delay(1000);
	CR.U(1, false);
	delay(1000);
	CR.D(1, false);
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

	//M4.Turn(Direction::ACW, 50 * 8, 1000);
	//delay(5000);
	//M4.Turn(Direction::CW, 50 * 8, 1000);
	//delay(5000);
	

	//M1.Turn(Direction::ACW, 360, 1000);
	//delay(500);
	//M1.Turn(Direction::CW, 720, 1000);
	//delay(500);
	//M2.Turn(Direction::CW, 120 * 8, 1000);
	//delay(100);
	//M2.Turn(Direction::ACW, 120 * 8, 1000);
	//delay(100);

	//M3.Turn(Direction::ACW, 360, 1000);
	//delay(500);
	//M3.Turn(Direction::CW, 720, 1000);
	//delay(500);
	//M4.Turn(Direction::ACW, 50 * 8, 1000);
	//delay(100);
	//M4.Turn(Direction::CW, 50 * 8, 1000);
	//delay(100);

	//M5.Turn(Direction::ACW, 360, 1000);
	//delay(500);
	//M5.Turn(Direction::CW, 720, 1000);
	//delay(500);
	//M6.Turn(Direction::ACW, 50 * 8, 1000);
	//delay(100);
	//M6.Turn(Direction::CW, 60 * 8, 1000);
	//delay(100);

	//M7.Turn(Direction::ACW, 360, 1000);
	//delay(500);
	//M7.Turn(Direction::CW, 720, 1000);
	//delay(500);
	//M8.Turn(Direction::ACW, 50 * 8, 1000);
	//delay(100);
	//M8.Turn(Direction::CW, 50 * 8, 1000);
	//delay(100);
}