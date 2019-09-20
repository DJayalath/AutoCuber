#pragma once

// For controlling individual rails
#include "Rail.h"

// For selecting a rail which will rotate the cube
enum RotSide {
	FRO,
	LEF,
	BAC,
	RIG,
};

// For selecting the motion type of a rail
enum MoveMode {
	RETRACT,
	EXTEND,
	TURN_ACW,
	TURN_CW,
};

class CubeRotate
{
public:
	CubeRotate(Rail front, Rail left, Rail back, Rail right);

	// Rotate cube to show all sides for camera above
	// - 'face' selects the next face to show
	void ShowNext(int face);
	// Rotate R
	// - 'count' is number of 90 degree rotations
	// - 'n' = true when opposite rotation required
	void R(int count, bool n = false);
	// Rotate L
	// - 'count' is number of 90 degree rotations
	// - 'n' = true when opposite rotation required
	void L(int count, bool n = false);
	// Rotate U
	// - 'count' is number of 90 degree rotations
	// - 'n' = true when opposite rotation required
	void U(int count, bool n = false);
	// Rotate D
	// - 'count' is number of 90 degree rotations
	// - 'n' = true when opposite rotation required
	void D(int count, bool n = false);
	// Rotate B
	// - 'count' is number of 90 degree rotations
	// - 'n' = true when opposite rotation required
	void B(int count, bool n = false);
	// Rotate F
	// - 'count' is number of 90 degree rotations
	// - 'n' = true when opposite rotation required
	void Fr(int count, bool n = false);
	// Rotate Y
	// - 'count' is number of 90 degree rotations
	// - 'n' = true when opposite rotation required
	void Y(int count, bool n = false);
	// Move U to top position
	void UTop();
	// Move F to top position
	void FTop();
	// Make all rails extended and vertical
	void RestoreDefaultState();
private:
	// Declare each rail in horizontal plane
	Rail front, left, back, right;
	// Is U on top?
	bool u_top = true;
	// Move rail to a new state
	void MoveRail(MoveMode M, Rail& A);
	// Move two rails to a new state together
	void MoveRail(MoveMode M, Rail& A, Rail& B);
	// Prepare rails for a LR rotation and then rotate
	void LRRotateState();
	// Prepare rails for a rotation of the side given
	// - 'side' is the side to be rotated afterwards
	void RotateState(RotSide side);
};

