#include "CubeRotate.h"
#include "Arduino.h"
CubeRotate::CubeRotate(Rail front, Rail left, Rail back, Rail right) : front(front), left(left), back(back), right(right)
{}

// Run a set of fixed instructions to go from showing one face
// to another. Transitions are fixed and must be in sequence.
void CubeRotate::ShowNext(int face)
{
	switch(face) {
		case 1: // Show U
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_CW, left, right);
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			break;
		case 2: // Show L
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_CW, left); // M4 vertical
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, left, right); // F top M4 horizontal
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_CW, left); // M4 vertical
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, front); // M2 horizontal
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_ACW, front, back); // L on top M6 horizontal
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, front); // M2 horizontal
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			break;
		case 3: // Show F
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, front); // M2 vertical
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_CW, front, back); // F on top M2 horizontal
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, back); // M6 horizontal
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			break;
		case 4: // Show R
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, front); // M2 vertical
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_CW, front, back); // F on top M2 horizontal
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, back); // M6 horizontal
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			break;
		case 5: // Show B
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, front); // M2 vertical
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_CW, front, back); // F on top M2 horizontal
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, back); // M6 horizontal
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			break;
		case 6: // MFB Extended Horizontal // MLR Retracted Vertical
			// Restore F top then show D
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, front); // M2 is now vertical, M6 remains horizontal
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_CW, front, back);
			this->MoveRail(TURN_CW, front, back); // F is now on top
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, back); // M6 is now vertical too
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_CW, left); // M4 is now horizontal, M8 remains vertical
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_CW, left, right); // D is now on top
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_CW, left); // M4 and M8 now horizontal
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			break;
		case 7: // Restore cube and motor states
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_CW, right); // M8 now vertical, M4 remains horizontal
			this->MoveRail(EXTEND, left, right);
			this->MoveRail(RETRACT, front, back);
			this->MoveRail(TURN_ACW, left, right);
			this->MoveRail(TURN_ACW, left, right); // U now on top
			this->MoveRail(EXTEND, front, back);
			this->MoveRail(RETRACT, left, right);
			this->MoveRail(TURN_CW, left); // M8 and M4 vertical after turning M4
			this->MoveRail(EXTEND, left, right);
			break;
	}
}

void CubeRotate::R(int count, bool n)
{
	// Put U on top if not already
	if (!u_top) {
		this->UTop();
	}

	// Prepare for rotation
	this->RotateState(RIG);

	// Rotate 90 degrees 'count' times in direction
	for (int i = 0; i < count; i++) {
		this->MoveRail((MoveMode) ((int) n + 2), right);
	}
}

void CubeRotate::L(int count, bool n)
{
	// Put U on top if not already
	if (!u_top) {
		this->UTop();
	}

	// Prepare for rotation
	this->RotateState(LEF);

	// Rotate 90 degrees 'count' times in direction
	for (int i = 0; i < count; i++) {
		this->MoveRail((MoveMode) ((int) n + 2), left);
	}
}

void CubeRotate::B(int count, bool n)
{
	// Put U on top if not already
	if (!u_top) {
		this->UTop();
	}

	// Prepare for rotation
	this->RotateState(BAC);

	// Rotate 90 degrees 'count' times in direction
	for (int i = 0; i < count; i++) {
		this->MoveRail((MoveMode) ((int) n + 2), back);
	}
}

void CubeRotate::Fr(int count, bool n)
{
	// Put U on top if not already
	if (!u_top) {
		this->UTop();
	}

	// Prepare for rotation
	this->RotateState(FRO);

	// Rotate 90 degrees 'count' times in direction
	for (int i = 0; i < count; i++) {
		this->MoveRail((MoveMode) ((int) n + 2), front);
	}
}

void CubeRotate::U(int count, bool n)
{
	// Put F on top if not already
	if (u_top) {
		this->FTop();
	}

	// Prepare for rotation
	this->RotateState(FRO);

	// Rotate 90 degrees 'count' times in direction
	for (int i = 0; i < count; i++) {
		this->MoveRail((MoveMode) ((int) n + 2), front);
	}
}

void CubeRotate::D(int count, bool n)
{
	// Put F on top if not already
	if (u_top) {
		this->FTop();
	}

	// Prepare for rotation
	this->RotateState(BAC);

	// Rotate 90 degrees 'count' times in direction
	for (int i = 0; i < count; i++) {
		this->MoveRail((MoveMode) ((int) n + 2), back);
	}
}

// Yet to be optimized. Runs fixed set of instructions for Y turn.
void CubeRotate::Y(int count, bool n) 
{
	this->MoveRail(RETRACT, front, back);
	this->MoveRail(TURN_CW, front);
	this->MoveRail(EXTEND, front, back);
	this->MoveRail(RETRACT, left, right);
	this->MoveRail(TURN_CW, front, back);
	this->MoveRail(EXTEND, left, right);
	this->MoveRail(RETRACT, front, back);
	this->MoveRail(TURN_CW, back);
	this->MoveRail(EXTEND, front, back);
	this->MoveRail(RETRACT, left, right);
	this->MoveRail(TURN_CW, left);
	this->MoveRail(EXTEND, left, right);
	this->MoveRail(RETRACT, front, back);
	for (int i = 0; i < count; i++) {
		this->MoveRail(TURN_ACW, left, right);
	}
	this->MoveRail(EXTEND, front, back);
	this->MoveRail(RETRACT, left, right);
	this->MoveRail(TURN_CW, right);
	this->MoveRail(EXTEND, left, right);
	this->MoveRail(RETRACT, front, back);
	this->MoveRail(TURN_CW, front);
	this->MoveRail(EXTEND, front, back);
	this->MoveRail(RETRACT, left, right);
	this->MoveRail(TURN_ACW, front, back);
	this->MoveRail(EXTEND, left, right);
	this->MoveRail(RETRACT, front, back);
	this->MoveRail(TURN_CW, back);
	this->MoveRail(EXTEND, front, back);
}

void CubeRotate::FTop() {
	// Prepare for rotation
	this->LRRotateState();
	// Rotate!
	this->MoveRail(TURN_ACW, left, right);
	// Update state
	u_top = false;
}

void CubeRotate::UTop() {
	// Prepare for rotation
	this->LRRotateState();
	// Rotate!
	this->MoveRail(TURN_CW, left, right);
	// Update state
	u_top = true;
}

void CubeRotate::MoveRail(MoveMode M, Rail& A) {

	// Multiply steps by 8 for linear movements due to microstepping
	// Set pins and pulse delay depending on if linear or circular movement
	int steps, stepPin, dirPin, dir, pulse_delay;
	if ((int) M > 1) {
		steps = 50;
		stepPin = A.circStep;
		dirPin = A.circDir;
		dir = (int) M - 2;
		pulse_delay = 1000;
	} else {
		steps = 50 * 8;
		stepPin = A.linStep;
		dirPin = A.linDir;
		dir = (int) M;
		pulse_delay = 600;
	}

	// Set direction pin
	digitalWrite(dirPin, dir);

	// Send pulses to motor driver
	for (int i = 0; i < steps; i++)
	{
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(pulse_delay);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(pulse_delay);
	}

	// Set new rail state
	if (M > 1) {
		A.railState = (RailState) ((int) A.railState ^ 0b01);
	} else {
		A.railState = (RailState) ((int) A.railState ^ 0b10);
	}
}

// Simulatanous
void CubeRotate::MoveRail(MoveMode M, Rail& A, Rail& B) {

	// Multiply steps by 8 for linear movements due to microstepping
	// Set pins and pulse delay depending on if linear or circular movement
	int steps, stepPinA, dirPinA, stepPinB, dirPinB, dir, pulse_delay;
	bool linear;
	if (M > 1) {
		steps = 50;
		stepPinA = A.circStep;
		dirPinA = A.circDir;
		stepPinB = B.circStep;
		dirPinB = B.circDir;
		dir = (int) M - 2;
		pulse_delay = 1000;
		linear = false;
	} else {
		// If extending opposite rails add one microstep
		// to maintain a firm grip on the cube
		if (M == EXTEND) {
			steps = 50 * 8 + 1;
		} else {
			steps = 50 * 8;
		}
		// steps = 50 * 8 + 6;
		stepPinA = A.linStep;
		dirPinA = A.linDir;
		stepPinB = B.linStep;
		dirPinB = B.linDir;
		dir = (int) M;
		pulse_delay = 600;
		linear = true;
	}

	// Set direction pin
	digitalWrite(dirPinA, dir);

	// Spin opposite clocks if circular, or same if linear
	if (!linear)
		digitalWrite(dirPinB, 1 - (int)dir);
	else
		digitalWrite(dirPinB, dir);

	// Send pulses to motor drivers
	for (int i = 0; i < steps; i++)
	{
		digitalWrite(stepPinA, HIGH);
		digitalWrite(stepPinB, HIGH);
		delayMicroseconds(1000);
		digitalWrite(stepPinA, LOW);
		digitalWrite(stepPinB, LOW);
		delayMicroseconds(1000);
	}

	// Set new rail states
	if (M > 1) {
		A.railState = (RailState) ((int) A.railState ^ 0b01);
		B.railState = (RailState) ((int) B.railState ^ 0b01);
	} else {
		A.railState = (RailState) ((int) A.railState ^ 0b10);
		B.railState = (RailState) ((int) B.railState ^ 0b10);
	}
}

void CubeRotate::LRRotateState() {

	// Targets:
	// - Alternate sides must be vertical
	// - One of current side must be horizontal

	// Make F and B vertical
	if (front.railState == EXT_H || back.railState == EXT_H) {
		this->MoveRail(RETRACT, front, back);
		if (front.railState == RET_H) {
			this->MoveRail(TURN_CW, front);
		}
		if (back.railState == RET_H) {
			this->MoveRail(TURN_CW, back);
		}
		this->MoveRail(EXTEND, front, back);
	}

	// Make sure one of L and R are horizontal and one vertical
	if (left.railState == right.railState) {
		this->MoveRail(RETRACT, left, right);
		this->MoveRail(TURN_CW, left);
		this->MoveRail(EXTEND, left, right);
	}

	this->MoveRail(RETRACT, front, back);
}

void CubeRotate::RotateState(RotSide side) {

	// FB Rotations not used in solve (so simplify)
	// Aim for no adjacent horizontals

	switch (side) {
	case BAC: // Applies for Back too
	case FRO: // Front - Ensure F and B can extend. Then ensure L and R are both vertical
		// Retracted case
		if (front.railState > 1 && back.railState > 1) {
			if (front.railState == RET_H && (left.railState == EXT_H || right.railState == EXT_H)) {
				this->MoveRail(TURN_CW, front);
			}
			if (back.railState == RET_H && (left.railState == EXT_H || right.railState == EXT_H)) {
				this->MoveRail(TURN_CW, back);
			}
			this->MoveRail(EXTEND, front, back);
		}
		// Ensure space (includes extended case)
		if (left.railState == EXT_H || right.railState == EXT_H) {
			this->MoveRail(RETRACT, left, right);
			if (left.railState == RET_H) {
				this->MoveRail(TURN_CW, left);
			}
			if (right.railState == RET_H) {
				this->MoveRail(TURN_CW, right);
			}
			this->MoveRail(EXTEND, left, right);
		}
		break;
	case LEF:
	case RIG:
		// Ensure F and B extend vertical
		if (front.railState > 1 && back.railState > 1) {
			if (front.railState == RET_H) {
				this->MoveRail(TURN_CW, front);
			}
			if (back.railState == RET_H) {
				this->MoveRail(TURN_CW, back);
			}
			this->MoveRail(EXTEND, front, back);
		} else {
			// F and B must be vertical
			if (front.railState == EXT_H || back.railState == EXT_H) {
				this->MoveRail(RETRACT, front, back);
				if (front.railState == RET_H) {
					this->MoveRail(TURN_CW, front);
				}
				if (back.railState == RET_H) {
					this->MoveRail(TURN_CW, back);
				}
				this->MoveRail(EXTEND, front, back);
			}
		}
		break;
	default:
		break;
	}
}

void CubeRotate:: RestoreDefaultState() {

	// Put front and back into vertical extended positions
	if (front.railState == EXT_H || back.railState == EXT_H) {
		this->MoveRail(RETRACT, front, back);
		if (front.railState == back.railState) {
			this->MoveRail(TURN_CW, front, back);
		} else if (front.railState == RET_H) {
			this->MoveRail(TURN_CW, front);
		} else if (back.railState == RET_H) {
			this->MoveRail(TURN_CW, back);
		}
		this->MoveRail(EXTEND, front, back);
	}

	// Put left and right into vertical extended positions
	if (left.railState == EXT_H || right.railState == EXT_H) {
		this->MoveRail(RETRACT, left, right);
		if (left.railState == right.railState) {
			this->MoveRail(TURN_CW, left, right);
		} else if (left.railState == RET_H) {
			this->MoveRail(TURN_CW, left);
		} else if (right.railState == RET_H) {
			this->MoveRail(TURN_CW, right);
		}
		this->MoveRail(EXTEND, left, right);
	}
}