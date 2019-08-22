#pragma once
#include <JC_Button.h>
class RotaryEncoder
{
public:
	RotaryEncoder(int encoderCLK, int encoderDT, int encoderSW);
	int PollRotate();
	bool PollSwitch();
private:
	const int encoderCLK, encoderDT;
	int presentState, previousState;
	Button pushButton;
};

