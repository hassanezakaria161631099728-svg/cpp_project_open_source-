#include "beam.h"
#include <cmath>

double computeDeflection(const BeamData& d)

{
        // simple beam formula example
        double delta = (5 * d.w * pow(d.L,4)) /(384 * d.E * d.I);
    return delta;
}

