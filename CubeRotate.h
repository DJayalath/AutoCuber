#pragma once
#include "MotorDriver.h"

// DEFAULT MOTOR STATE: Extended, Vertical

// Motor Definitions: 
// M1 = Circular, Left
// M2 = Linear, Left
// M3 = Circular, Front
// M4 = Linear, Front

class CubeRotate
{
public:
	CubeRotate(MotorDriver A, MotorDriver B, MotorDriver C, MotorDriver D);
	void ShowAll();
private:
	void Retract(MotorDriver& M);
	void Extend(MotorDriver& M);

	// Right-Angle Clockwise
	void RACW(MotorDriver& M);
	// Right-Angle Anti-Clockwise
	void RAACW(MotorDriver& M);
	MotorDriver M1, M2, M3, M4;
};

