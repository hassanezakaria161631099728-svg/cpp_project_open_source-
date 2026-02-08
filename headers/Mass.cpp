#include "Mass.h"

std::vector<std::vector<double>>
buildMassMatrix(const BeamData& d)
{
    int n = d.nFloors;

    // initialize all zeros
    std::vector<std::vector<double>> M(n,
        std::vector<double>(n, 0.0));

    // ---- RULE 1 ----
    // for i = 1 → n-2
    if(n >= 3)
    {
        for(int i=1; i<=n-2; i++)
        {
            M[i-1][i-1] = d.M1;
        }

        // ---- RULE 2 ----
        M[n-2][n-2] = d.M2;

        // ---- RULE 3 ----
        M[n-1][n-1] = d.M3;
    }

    return M;
}
