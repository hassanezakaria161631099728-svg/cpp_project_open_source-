#include "io.h"
#include "beam.h"
#include "stiffness.h"
int main()
{
    // 1. Read TXT
    BeamData d = readInput("input.txt");

    // 2. Calculate
    // old beam part
    double delta = computeDeflection(d);
    // new: stiffness
    auto K = createStiffnessMatrix(d.nFloors);
    // 3. Write results
    writeOutput("output.txt", delta, K);
    return 0;
}
