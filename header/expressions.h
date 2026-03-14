#pragma once
#include <vector>
struct BeamData {
    double w,L,E,I; // deflection
    int nFloors;    // stiffness Mass Dynamic matrices
    double M1, M2, M3, h, EC, IX, IY;
};
double computeDeflection(const BeamData& d, double I, double E);
double computef(const BeamData& d, double I, double E);
std::vector<std::vector<double>>
buildMassMatrix(const BeamData& d);
std::vector<std::vector<double>>
createSAMatrix(int n);
std::vector<std::vector<double>>
multiplymatmat(const std::vector<std::vector<double>>& A,
         const std::vector<std::vector<double>>& B);
std::vector<std::vector<double>>
multiplyscamat(double a,
         const std::vector<std::vector<double>>& B);
using Matrix = std::vector<std::vector<double>>;

void eigenDecomposition(
    const Matrix& A,
    Matrix& B,
    Matrix& C);


