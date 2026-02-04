#pragma once
#include <vector>
struct BeamData {
    double w;
    double L;
    double E;
    double I;
    int nFloors; // new
    std::vector<double> stations;
};
