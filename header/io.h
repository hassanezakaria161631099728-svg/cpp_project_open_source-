#pragma once
#include "structs.h"
#include <string>

BeamData readInput(const std::string& filename);
void writeOutput(const std::string& filename,
                 double deflection,double fx,double fy,
                 const std::vector<std::vector<double>>& SA,
                 const std::vector<std::vector<double>>& Sx,
                 const std::vector<std::vector<double>>& Sy,
                 const std::vector<std::vector<double>>& M,
                 const std::vector<std::vector<double>>& Dx,
                 const std::vector<std::vector<double>>& Dy);

