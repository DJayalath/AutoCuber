// For tracking the state of a rail
enum RailState {
    EXT_V = 0b00,
    EXT_H = 0b01,
    RET_V = 0b10,
    RET_H = 0b11,
};

class Rail {
public:
    Rail::Rail(int linStep, int linDir, int circStep, int circDir) : linStep(linStep), linDir(linDir), circStep(circStep), circDir(circDir) {};
    // Store pins for linear and circular motors
    int linStep, linDir, circStep, circDir;
    // Store rail state
    RailState railState = EXT_V;
};