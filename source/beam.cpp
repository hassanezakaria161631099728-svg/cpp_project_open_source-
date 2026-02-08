#include "beam.h"
#include <cmath>

double computeDeflection(const BeamData& d, double I, double E)

{
        // simple beam formula example
        double delta = (5 * d.w * pow(d.L,4)) /(384 * E * I);
    return delta;
}

