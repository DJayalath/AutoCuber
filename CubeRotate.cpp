#include "CubeRotate.h"
CubeRotate::CubeRotate(MotorDriver A, MotorDriver B, MotorDriver C, MotorDriver D) : M1(A), M2(B), M3(C), M4(D)
{

}

void CubeRotate::ShowAll()
{
	delay(500);
	this->RACW(M2);
	delay(500);
	this->RACW(M2);
	delay(500);
	this->RACW(M2);
}

void CubeRotate::Retract(MotorDriver& M)
{
	M.Turn(Direction::ACW, 50 * 32, 600);
}

void CubeRotate::Extend(MotorDriver& M)
{
	M.Turn(Direction::CW, 50 * 32, 600);
}

void CubeRotate::RACW(MotorDriver& M)
{
	M.Turn(Direction::CW, 90, 600);
}

void CubeRotate::RAACW(MotorDriver& M)
{
	M.Turn(Direction::ACW, 90, 600);
}
