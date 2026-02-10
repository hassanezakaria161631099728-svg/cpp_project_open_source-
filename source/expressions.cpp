#include "expressions.h"
#include <cmath>

double computeDeflection(const BeamData& d, double I, double E)

{
        // simple beam formula example
        double delta = (5 * d.w * pow(d.L,4)) /(384 * E * I);
    return delta;
}

double computef(const BeamData& d, double I, double E)

{
        // expression for a factor we multiply on SA to get stiffness matrix
        double f = (pow(d.h,3)) / (6 * E * I );
    return f;
}

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
