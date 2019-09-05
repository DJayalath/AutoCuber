#pragma once

#include <Arduino.h>
#include "Direction.h"

class MotorDriver
{
public:
	MotorDriver(int stepPin, int dirPin);

	// Turn motor in dir by angle (degrees) with pulse delay (micro-seconds)
	void Turn(Direction dir, int angle, int pulse_delay);

	int GetStepPin();
	int GetDirPin();

private:
	const int stepPin;
	const int dirPin;
	static const float deg_per_step;

};

