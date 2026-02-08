#include "f.h"
#include <cmath>

double computef(const BeamData& d, double I, double E)

{
        // expression for a factor we multiply on SA to get stiffness matrix
        double f = (pow(d.h,3)) / (6 * E * I );
    return f;
}

