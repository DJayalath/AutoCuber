﻿#include "MotorDriver.h"
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
int counter = 0;
int msg = 1;
void setup()
{
	Serial.begin(9600);

	//CR.ShowAll();
	//CR.Scramble();
	//CR.R(1, false);
	//delay(1000);
	//CR.L(1, false);
	//delay(1000);
	//CR.B(1, false);
	//delay(1000);
	//CR.Fr(1, false);
	//delay(1000);
	//CR.U(1, false);
	//delay(1000);
	//CR.D(1, false);
}

void loop() {
	byte n = 10;
	Serial.write(n);
	delay(100);
	int rc = Serial.read();
	switch (rc) {
	case 'A':
		CR.ShowAll();
		break;
	case 'Z':
		CR.Scramble();
		break;
	case 'R':
		CR.R(1);
		counter += 1;
		break;
	case 'S':
		CR.R(1, true);
		counter += 1;
		break;
	case 'L':
		CR.L(1);
		counter += 1;
		break;
	case 'M':
		CR.L(1, true);
		counter += 1;
		break;
	case 'U':
		CR.U(1);
		counter += 1;
		break;
	case 'V':
		CR.U(1, true);
		counter += 1;
		break;
	case 'D':
		CR.D(1);
		counter += 1;
		break;
	case 'E':
		CR.D(1, true);
		counter += 1;
		break;
	case 'F':
		CR.Fr(1);
		counter += 1;
		break;
	case 'G':
		CR.Fr(1, true);
		counter += 1;
		break;
	case 'B':
		CR.B(1);
		counter += 1;
		break;
	case 'C':
		CR.B(1, true);
		counter += 1;
		break;
	}
	Serial.write(rc + 33);
	Serial.flush();
	delay(100);
	if (counter % 2 == 0 && counter != 0) {
		//CR.Correct();
	}
	//char inByte = ' ';
	//if (Serial.available()) { // only send data back if data has been sent
	//	char inByte = Serial.read(); // read the incoming data
	//	Serial.println(inByte); // send the data back in a new line so that it is not all one long line
	//}
	//delay(100); // delay for 1/10 of a second
	//if (Serial.available() > 0) {
	//	Serial.read();
	//	CR.ShowAll();
	//	//Serial.write(Serial.read());
	//}
	//delay(500);

	//bool start = false;
	//while (!start) {
	//	if (Serial.available() > 0) {
	//		CR.ShowAll();
	//		start = true;
	//		//msg = Serial.read();
	//		//if (msg == 'A') {
	//		//	start = true;
	//		//	CR.ShowAll();
	//		//}
	//	}
	//}


	//for (byte n = 0; n < 255; n++) {
	//	Serial.write(n);
	//	delay(100);
	//}

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