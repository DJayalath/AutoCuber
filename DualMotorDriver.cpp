#include "DualMotorDriver.h"

const float DualMotorDriver::deg_per_step = 1.8;

DualMotorDriver::DualMotorDriver(int stepPinA, int dirPinA, int stepPinB, int dirPinB) : stepPinA(stepPinA), dirPinA(dirPinA), stepPinB(stepPinB), dirPinB(dirPinB)
{
	// Declare step and dir pins as outputs
	pinMode(stepPinA, OUTPUT);
	pinMode(dirPinA, OUTPUT);
	pinMode(stepPinB, OUTPUT);
	pinMode(dirPinB, OUTPUT);
}

void DualMotorDriver::Turn(Direction dir, int angle, int pulse_delay, bool lin=false)
{
	// Calculate step count required for turn angle
	int steps = (float)angle / this->deg_per_step;
	// Set direction pin
	digitalWrite(dirPinA, dir);

	// Spin opposite clocks if circular, or same if linear
	if (!lin)
		digitalWrite(dirPinB, 1 - (int)dir);
	else
		digitalWrite(dirPinB, dir);

	for (int i = 0; i < steps; i++)
	{
		digitalWrite(this->stepPinA, HIGH);
		digitalWrite(this->stepPinB, HIGH);
		delayMicroseconds(pulse_delay);
		digitalWrite(this->stepPinA, LOW);
		digitalWrite(this->stepPinB, LOW);
		delayMicroseconds(pulse_delay);
	}
}

void DualMotorDriver::Retract()
{
	this->Turn(Direction::ACW, 90 * 8, 1000, true);
}

void DualMotorDriver::Extend()
{
	this->Turn(Direction::CW, 90 * 8, 1000, true);
}
