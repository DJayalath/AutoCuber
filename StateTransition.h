#pragma once

enum State {
    EXT_V = 0b00,
    EXT_H = 0b01,
    RET_V = 0b10,
    RET_H = 0b11,
};

enum Rail {
    Fr,
    L,
    B,
    R,
};

class StateTransition {
public:
    StateTransition();

    void ChangeState(State Fr, State L, State B, State R);

private:
    State rails[4];
};