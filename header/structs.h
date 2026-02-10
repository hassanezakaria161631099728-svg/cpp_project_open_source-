#pragma once
#include <vector>
struct BeamData {
    double w,L,E,I; // deflection
    int nFloors;    // stiffness Mass Dynamic matrices
    double M1, M2, M3, h, EC, IX, IY;
};
