#include "CubeRotate.h"
CubeRotate::CubeRotate(MotorDriver A, MotorDriver B, MotorDriver C, MotorDriver D, MotorDriver E, MotorDriver F, MotorDriver G, MotorDriver H) :
					   M1(A), M2(B), M3(C), M4(D),
					   M5(E), M6(F), M7(G), M8(H), 
					   MFB(B.GetStepPin(), B.GetDirPin(), F.GetStepPin(), F.GetDirPin()),
					   MLR(D.GetStepPin(), D.GetDirPin(), H.GetStepPin(), H.GetDirPin()),
					   MLFB(A.GetStepPin(), A.GetDirPin(), E.GetStepPin(), E.GetDirPin()),
					   MLLR(C.GetStepPin(), C.GetDirPin(), G.GetStepPin(), G.GetDirPin())
{

}

void CubeRotate::ShowAll()
{
	MFB.Turn(Direction::CW, 90, 600); // FB horizontal
	// Extend FB
	MLFB.Extend();
	// Retract LR
	MLLR.Retract();
	delay(500); // CAPTURE
	MFB.Turn(Direction::CW, 90, 600); // FB vertical, Cube turned
	MLR.Turn(Direction::CW, 90, 600); // LR horizontal
	// Extend LR
	MLLR.Extend();
	// Retract FB
	MLFB.Extend();
	delay(500); // CAPTURE
	MLR.Turn(Direction::CW, 90, 600); // LR vertical, Cube turned
	MFB.Turn(Direction::CW, 90, 600); // FB horizontal
	// Extend FB
	MLFB.Extend();
	// Retract LR
	MLLR.Retract();
	delay(500); // CAPTURE
	MFB.Turn(Direction::CW, 90, 600); // FB vertical, Cube turned
	MLR.Turn(Direction::CW, 90, 600); // LR horizontal
	// Extend LR
	MLLR.Extend();
	// Retract FB
	MLFB.Extend();
	delay(500); // CAPTURE
	MLR.Turn(Direction::CW, 90, 600); // LR vertical, Cube turned
	MFB.Turn(Direction::CW, 90, 600); // FB horizontal
	// Extend FB
	MLFB.Extend();
	// Retract LR
	MLLR.Retract();
	delay(500); // CAPTURE
	MFB.Turn(Direction::CW, 90, 600); // FB vertical, Cube turned
	MLR.Turn(Direction::CW, 90, 600); // LR horizontal
	// Extend LR
	MLLR.Extend();
	// Retract FB
	MLFB.Extend();
	delay(500); // CAPTURE
}

void CubeRotate::Retract(MotorDriver& M)
{
	M.Turn(Direction::ACW, 50 * 8, 1000);
}

void CubeRotate::Extend(MotorDriver& M)
{
	M.Turn(Direction::CW, 50 * 8, 1000);
}

void CubeRotate::RACW(MotorDriver& M)
{
	M.Turn(Direction::CW, 90, 600);
}

void CubeRotate::RAACW(MotorDriver& M)
{
	M.Turn(Direction::ACW, 90, 600);
}
