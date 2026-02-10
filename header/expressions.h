#pragma once
#include "structs.h"
#include <vector>

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

