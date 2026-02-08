#include "multiplymatmat.h"

std::vector<std::vector<double>>
multiplymatmat(const std::vector<std::vector<double>>& A,
         const std::vector<std::vector<double>>& B)
{
    int n = A.size();

    std::vector<std::vector<double>> C(n,
        std::vector<double>(n, 0.0));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            for(int k=0; k<n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

