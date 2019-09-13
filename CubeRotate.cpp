#include "CubeRotate.h"
#include "Arduino.h"
CubeRotate::CubeRotate(MotorDriver A, MotorDriver B, MotorDriver C, MotorDriver D, MotorDriver E, MotorDriver F, MotorDriver G, MotorDriver H) :
					   M1(A), M2(B), M3(C), M4(D),
					   M5(E), M6(F), M7(G), M8(H), 
					   MFB(B.GetStepPin(), B.GetDirPin(), F.GetStepPin(), F.GetDirPin()),
					   MLR(D.GetStepPin(), D.GetDirPin(), H.GetStepPin(), H.GetDirPin()),
					   MLFB(A.GetStepPin(), A.GetDirPin(), E.GetStepPin(), E.GetDirPin()),
					   MLLR(C.GetStepPin(), C.GetDirPin(), G.GetStepPin(), G.GetDirPin())
{

}

void CubeRotate::ShowNext(int face)
{

	switch (face) {
		// U to R
		case 1:
			this->Retract(M3);
			M4.Turn(Direction::CW, 90, 600);
			this->Extend(M3);
			MLFB.Retract();
			MLR.Turn(Direction::CW, 90, 1000); // Check if CW or ACW - Put F on top

			MLFB.Extend();
			this->Retract(M7);
			M8.Turn(Direction::CW, 90, 600);
			this->Extend(M7);

			this->Retract(M1);
			M2.Turn(Direction::CW, 90, 600);
			this->Extend(M1);
			MLLR.Retract();

			MFB.Turn(Direction::CW, 90, 1000); // R on top
			break;
		case 2:
			MFB.Turn(Direction::ACW, 90, 1000); // F on top
			break;
		case 3:
			MLLR.Extend();

			this->Retract(M1);
			M2.Turn(Direction::CW, 90, 600);
			this->Extend(M1);

			this->Retract(M3);
			M4.Turn(Direction::CW, 90, 600);
			this->Extend(M3);
			MLFB.Retract();

			MLR.Turn(Direction::CW, 90, 1000); // D on top
			break;
		case 4:
			MLR.Turn(Direction::ACW, 90, 1000); // Put F back on top

			MLFB.Extend();

			this->Retract(M3);
			M4.Turn(Direction::CW, 90, 600);
			this->Extend(M3);

			this->Retract(M1);
			M2.Turn(Direction::CW, 90, 600);
			this->Extend(M1);

			MLLR.Retract();

			MFB.Turn(Direction::ACW, 90, 1000); // Put L on top
			break;
		case 5:
			MFB.Turn(Direction::CW, 270, 1000); // Put B on top
			break;
		case 6: // Reset case (bring front to position and reset motor states)
			MFB.Turn(Direction::ACW, 180, 1000); // F on top
			MLLR.Extend();
			this->Retract(M1);
			M2.Turn(Direction::CW, 90, 600);
			this->Extend(M1);

			this->Retract(M3);
			M4.Turn(Direction::CW, 90, 600);
			this->Extend(M3);
			MLFB.Retract();

			MLR.Turn(Direction::ACW, 90, 1000); // Put U on top
			
			MLFB.Extend();
			this->Retract(M7);
			M8.Turn(Direction::CW, 90, 600);
			this->Extend(M7);

			break;
	}

	// this->Retract(M1);
	// M2.Turn(Direction::CW, 90, 600);
	// this->Extend(M1);
	// MLLR.Retract();
	// MFB.Turn(Direction::CW, 90, 600);

	// delay(1000);

	// MLLR.Extend();
	// this->Retract(M5);
	// M6.Turn(Direction::CW, 90, 600);
	// this->Extend(M5);

	// this->Retract(M3);
	// M4.Turn(Direction::CW, 90, 600);
	// this->Extend(M3);
	// MLFB.Retract();
	// MLR.Turn(Direction::CW, 90, 600);

	// delay(1000);

	// // Return to normal
	// MLFB.Extend();
	// this->Retract(M7);
	// M8.Turn(Direction::CW, 90, 600);
	// this->Extend(M7);



	//for (int i = 0; i < 10; i++)
	//{
	//	MFB.Turn(Direction::CW, 90, 1000);
	//	delay(1000);
	//}
	//MLLR.Retract();



	// MLFB.Retract();
	// MFB.Turn(Direction::CW, 90, 600); // FB horizontal
	// // Extend FB
	// MLFB.Extend();
	// MLFB.Turn(Direction::CW, 2 * 8, true);
	// // Retract LR
	// MLLR.Retract();
	// delay(1000); // CAPTURE U
	// MFB.Turn(Direction::CW, 90, 600); // FB vertical, Cube turned
	// MLR.Turn(Direction::CW, 90, 600); // LR horizontal
	// // Extend LR
	// MLLR.Extend();
	// MLLR.Turn(Direction::CW, 2 * 8, true);
	// // Retract FB
	// MLFB.Retract();
	// delay(1000); // CAPTURE L
	// MLR.Turn(Direction::CW, 90, 600); // LR vertical, Cube turned
	// MFB.Turn(Direction::CW, 90, 600); // FB horizontal
	// // Extend FB
	// MLFB.Extend();
	// MLFB.Turn(Direction::CW, 2 * 8, true);
	// // Retract LR
	// MLLR.Retract();
	// delay(1000); // CAPTURE
	// MFB.Turn(Direction::CW, 90, 600); // FB vertical, Cube turned
	// MLR.Turn(Direction::CW, 90, 600); // LR horizontal
	// // Extend LR
	// MLLR.Extend();
	// MLLR.Turn(Direction::CW, 2 * 8, true);
	// // Retract FB
	// MLFB.Retract();
	// delay(1000); // CAPTURE
	// MLR.Turn(Direction::CW, 90, 600); // LR vertical, Cube turned
	// MFB.Turn(Direction::CW, 90, 600); // FB horizontal
	// // Extend FB
	// MLFB.Extend();
	// MLFB.Turn(Direction::CW, 2 * 8, true);
	// // Retract LR
	// MLLR.Retract();
	// delay(1000); // CAPTURE
	// MFB.Turn(Direction::CW, 90, 600); // FB vertical, Cube turned
	// MLR.Turn(Direction::CW, 90, 600); // LR horizontal
	// // Extend LR
	// MLLR.Extend();
	// MLLR.Turn(Direction::CW, 2 * 8, true);
	// // Retract FB
	// MLFB.Retract();
	// delay(1000); // CAPTURE
	// //MFB.Turn(Direction::CW, 90, 600);
	// MLFB.Extend();
	// MLLR.Retract();
	// MLR.Turn(Direction::CW, 90, 600);
	// MLLR.Extend();
}

void CubeRotate::Scramble()
{
	randomSeed(analogRead(0));

	int side[6];
	for (int i = 0; i < 6; i++) {
		side[i] = random(4);
	}

	M2.Turn(Direction::CW, 90 * side[0], 600);
	if (side[0] % 2 != 0) {
		this->Retract(M1);
		M2.Turn(Direction::CW, 90, 600);
		this->Extend(M1);
	}

	M4.Turn(Direction::CW, 90 * side[1], 600);
	if (side[1] % 2 != 0) {
		this->Retract(M3);
		M4.Turn(Direction::CW, 90, 600);
		this->Extend(M3);
	}

	M6.Turn(Direction::CW, 90 * side[2], 600);
	if (side[2] % 2 != 0) {
		this->Retract(M5);
		M6.Turn(Direction::CW, 90, 600);
		this->Extend(M5);
	}

	M8.Turn(Direction::CW, 90 * side[3], 600);
	if (side[3] % 2 != 0) {
		this->Retract(M7);
		M8.Turn(Direction::CW, 90, 600);
		this->Extend(M7);
	}

	this->Retract(M3);
	M4.Turn(Direction::CW, 90, 600);
	this->Extend(M3);
	MLFB.Retract();
	MLR.Turn(Direction::CW, 90, 600);
	MLFB.Extend();
	this->Retract(M7);
	M8.Turn(Direction::CW, 90, 600);
	this->Extend(M7);

	M2.Turn(Direction::CW, 90 * side[4], 600);
	if (side[4] % 2 != 0) {
		this->Retract(M1);
		M2.Turn(Direction::CW, 90, 600);
		this->Extend(M1);
	}

	M6.Turn(Direction::CW, 90 * side[5], 600);
	if (side[5] % 2 != 0) {
		this->Retract(M5);
		M6.Turn(Direction::CW, 90, 600);
		this->Extend(M5);
	}

	this->Retract(M3);
	M4.Turn(Direction::CW, 90, 600);
	this->Extend(M3);
	MLFB.Retract();
	MLR.Turn(Direction::ACW, 90, 600);
	MLFB.Extend();
	this->Retract(M7);
	M8.Turn(Direction::CW, 90, 600);
	this->Extend(M7);

}

void CubeRotate::R(int count, bool n)
{
	M8.Turn((Direction) n, 90 * count, 600);

	if (count % 2 != 0) {
		this->Retract(M7);
		M8.Turn(Direction::ACW, 90, 600);
		this->Extend(M7);
	}
}

void CubeRotate::L(int count, bool n)
{
	M4.Turn((Direction)n, 90 * count, 600);

	if (count % 2 != 0) {
		this->Retract(M3);
		M4.Turn(Direction::ACW, 90, 600);
		this->Extend(M3);
	}
}

void CubeRotate::B(int count, bool n)
{
	M6.Turn((Direction)n, 90 * count, 600);

	if (count % 2 != 0) {
		this->Retract(M5);
		M6.Turn(Direction::ACW, 90, 600);
		this->Extend(M5);
	}
}

void CubeRotate::Fr(int count, bool n)
{
	M2.Turn((Direction)n, 90 * count, 600);

	if (count % 2 != 0) {
		this->Retract(M1);
		M2.Turn(Direction::ACW, 90, 600);
		this->Extend(M1);
	}
}

void CubeRotate::U(int count, bool n)
{
	this->Retract(M3);
	M4.Turn(Direction::CW, 90, 600);
	this->Extend(M3);
	MLFB.Retract();
	MLR.Turn(Direction::ACW, 90, 600);
	MLFB.Extend();
	this->Retract(M7);
	M8.Turn(Direction::CW, 90, 600);
	this->Extend(M7);

	M2.Turn((Direction)n, 90 * count, 600);

	if (count % 2 != 0) {
		this->Retract(M1);
		M2.Turn(Direction::ACW, 90, 600);
		this->Extend(M1);
	}

	this->Retract(M3);
	M4.Turn(Direction::CW, 90, 600);
	this->Extend(M3);
	MLFB.Retract();
	MLR.Turn(Direction::CW, 90, 600);
	MLFB.Extend();
	this->Retract(M7);
	M8.Turn(Direction::CW, 90, 600);
	this->Extend(M7);
}

void CubeRotate::D(int count, bool n)
{
	this->Retract(M3);
	M4.Turn(Direction::CW, 90, 600);
	this->Extend(M3);
	MLFB.Retract();
	MLR.Turn(Direction::ACW, 90, 600);
	MLFB.Extend();
	this->Retract(M7);
	M8.Turn(Direction::CW, 90, 600);
	this->Extend(M7);

	M6.Turn((Direction)n, 90 * count, 600);

	if (count % 2 != 0) {
		this->Retract(M5);
		M6.Turn(Direction::ACW, 90, 600);
		this->Extend(M5);
	}

	this->Retract(M3);
	M4.Turn(Direction::CW, 90, 600);
	this->Extend(M3);
	MLFB.Retract();
	MLR.Turn(Direction::CW, 90, 600);
	MLFB.Extend();
	this->Retract(M7);
	M8.Turn(Direction::CW, 90, 600);
	this->Extend(M7);
}

void CubeRotate::Retract(MotorDriver& M)
{
	M.Turn(Direction::ACW, 90 * 8, 1000);
}

void CubeRotate::Extend(MotorDriver& M)
{
	M.Turn(Direction::CW, 90 * 8, 1000);
}

void CubeRotate::Correct()
{
	MLFB.Turn(Direction::CW, 1 * 8, 1000, true);
	MLLR.Turn(Direction::CW, 1 * 8, 1000, true);
}

void CubeRotate::RACW(MotorDriver& M)
{
	M.Turn(Direction::CW, 90, 600);
}

void CubeRotate::RAACW(MotorDriver& M)
{
	M.Turn(Direction::ACW, 90, 600);
}
