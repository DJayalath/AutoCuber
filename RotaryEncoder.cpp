#include "RotaryEncoder.h"
#include <Arduino.h>

RotaryEncoder::RotaryEncoder(int encoderCLK, int encoderDT, int encoderSW) : encoderCLK(encoderCLK), encoderDT(encoderDT), pushButton(encoderSW)
{
	pinMode(encoderCLK, INPUT);
	pinMode(encoderDT, INPUT);

	this->previousState = digitalRead(encoderCLK);
}

int RotaryEncoder::PollRotate()
{
	int movement = 0;
	presentState = digitalRead(encoderCLK);
	if (presentState != previousState) {
		if (digitalRead(encoderDT) != presentState) {
			movement++;
		}
		else {
			movement--;
		}
	}
	previousState = presentState;
	return movement;
}

bool RotaryEncoder::PollSwitch()
{
	pushButton.read();
	return pushButton.wasReleased();
}
