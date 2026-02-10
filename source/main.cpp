#include "io.h"
#include "expressions.h"
int main()
{
    // 1. Read TXT
    BeamData d = readInput("input.txt");

    // 2. Calculate
    // scalar
    double delta = computeDeflection(d, d.I, d.E);
    double fx = computef(d, d.IX, d.EC);
    double fy = computef(d, d.IY, d.EC);
    //  matrices
    auto SA = createSAMatrix(d.nFloors);
    auto Sx  = multiplyscamat(fx, SA);
    auto Sy  = multiplyscamat(fy, SA);
    auto M = buildMassMatrix(d);
    auto Dx = multiplymatmat(Sx, M);
    auto Dy = multiplymatmat(Sy, M);
    // 3. Write results
    writeOutput("output.txt", delta, fx, fy, SA, Sx, Sy, M, Dx, Dy);
    return 0;
}
