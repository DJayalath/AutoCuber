#pragma once

#include <Arduino.h>

enum Direction {
	CW = HIGH,
	ACW = LOW,
};

class MotorDriver
{
public:
	MotorDriver(int stepPin, int dirPin);

	// Turn motor in dir by angle (degrees) with pulse delay (micro-seconds)
	void Turn(Direction dir, int angle, int pulse_delay);

private:
	const int stepPin;
	const int dirPin;
	static const float deg_per_step;

};

