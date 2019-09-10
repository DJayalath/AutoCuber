#pragma once
#include "MotorDriver.h"
#include "DualMotorDriver.h"

// DEFAULT MOTOR STATE: Vertical
// DEFAULT LAYOUT STATE: All extended

/*
Motor Definitions:
M1 = Linear, Front
M2 = Circular, Front
M3 = Linear, Left
M4 = Circular, Left
M5 = Linear, Back
M6 = Circular, Back
M7 = Linear, Right
M8 = Circular, Right
*/

class CubeRotate
{
public:
	CubeRotate(MotorDriver A, MotorDriver B, MotorDriver C, MotorDriver D, MotorDriver E, MotorDriver F, MotorDriver G, MotorDriver H);

	// Rotate cube to show all sides for camera above
	void ShowAll();
	void Scramble();
	//void R(int count, bool n = false);
	//void L(int count, bool n = false);
	//void U(int count, bool n = false);
	//void D(int count, bool n = false);
	//void B(int count, bool n = false);
	//void Fr(int count, bool n = false);
private:
	void Retract(MotorDriver& M);
	void Extend(MotorDriver& M);

	// Right-Angle Clockwise
	void RACW(MotorDriver& M);
	// Right-Angle Anti-Clockwise
	void RAACW(MotorDriver& M);
	MotorDriver M1, M2, M3, M4, M5, M6, M7, M8;

	// FB = Front + Back, LR = Left + Right
	DualMotorDriver MFB, MLR;
	// L for linear
	DualMotorDriver MLFB, MLLR;
};

