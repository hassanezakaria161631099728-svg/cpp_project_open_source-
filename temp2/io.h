#pragma once
#include "structs.h"
#include <string>

BeamData readInput(const std::string& filename);
void writeOutput(const std::string& filename,
                 const std::vector<double>& x,
                 const std::vector<double>& def);
void writeMatrix(const std::string& filename,
                 const std::vector<std::vector<double>>& K);

