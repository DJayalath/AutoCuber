#include "MotorDriver.h"

const float MotorDriver::deg_per_step = 1.8;

MotorDriver::MotorDriver(int stepPin, int dirPin) : stepPin(stepPin), dirPin(dirPin)
{
	// Declare step and dir pins as outputs
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
}

void MotorDriver::Turn(Direction dir, int angle, int pulse_delay)
{
	// Calculate step count required for turn angle
	int steps = (float) angle / this->deg_per_step;
	// Set direction pin
	digitalWrite(dirPin, dir);

	for (int i = 0; i < steps; i++)
	{
		digitalWrite(this->stepPin, HIGH);
		delayMicroseconds(pulse_delay);
		digitalWrite(this->stepPin, LOW);
		delayMicroseconds(pulse_delay);
	}
}

int MotorDriver::GetStepPin()
{
	return this->stepPin;
}

int MotorDriver::GetDirPin()
{
	return this->dirPin;
}
