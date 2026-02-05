#pragma once
#include "structs.h"
#include <string>

BeamData readInput(const std::string& filename);
void writeOutput(const std::string& filename,
                 double deflection,
                 const std::vector<std::vector<double>>& K);

