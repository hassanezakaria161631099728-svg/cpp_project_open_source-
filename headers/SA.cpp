#include "SA.h"

std::vector<std::vector<double>>
createSAMatrix(int n)
{
    // create n x n matrix filled with 0
    std::vector<std::vector<double>> A(n,
        std::vector<double>(n, 0.0));

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(i < j)
                A[i-1][j-1] = i*i * (3*j - i);

            else if(i == j)
                A[i-1][j-1] = 2*i*i*i;

            else // i > j
                A[i-1][j-1] = j*j * (3*i - j);
        }
    }

    return A;
}

