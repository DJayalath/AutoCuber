#pragma once

#include <Arduino.h>
#include "Direction.h"

class DualMotorDriver
{
public:
	DualMotorDriver(int stepPinA, int dirPinA, int stepPinB, int dirPinB);

	// Turn motor in dir by angle (degrees) with pulse delay (micro-seconds)
	void Turn(Direction dir, int angle, int pulse_delay, bool lin=false);
	void Retract();
	void Extend();

private:
	const int stepPinA, stepPinB;
	const int dirPinA, dirPinB;
	static const float deg_per_step;

};



