#include "beam.h"
#include <cmath>

std::vector<double> computeDeflection(const BeamData& d)
{
    std::vector<double> def;

    for(double x : d.stations)
    {
        // simple beam formula example
        double delta =
            (5 * d.w * pow(d.L,4)) /
            (384 * d.E * d.I);

        def.push_back(delta);
    }

    return def;
}

