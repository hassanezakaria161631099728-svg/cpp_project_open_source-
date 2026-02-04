#include "io.h"
#include "beam.h"
#include "stiffness.h"
int main()
{
    // 1. Read TXT
    BeamData data = readInput("input.txt");

    // 2. Calculate
    // old beam part
    auto def = computeDeflection(data);
    // new: stiffness
    auto K = createStiffnessMatrix(data.nFloors);
    // 3. Write results
    writeOutput("output.txt", data.stations, def);
    writeMatrix("stiffness.txt",K);
    return 0;
}
