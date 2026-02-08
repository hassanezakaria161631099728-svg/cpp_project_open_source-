#include "multiplyscamat.h"
std::vector<std::vector<double>>

multiplyscamat(double a,
         const std::vector<std::vector<double>>& B)
{
    int n = B.size();

    std::vector<std::vector<double>> C(n,
        std::vector<double>(n));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
                C[i][j] = a * B[i][j];
            }
        }

    return C;
}
