#include "io.h"
#include <fstream>
#include <iostream>

BeamData readInput(const std::string& filename)
{
    BeamData d{};
    std::ifstream file(filename);

    if(!file)
    {
        std::cout << "Cannot open input!\n";
        return d;
    }

    std::string word;

    while(file >> word)
    {
        if(word == "w") file >> d.w;
        else if(word == "L") file >> d.L;
        else if(word == "E") file >> d.E;
        else if(word == "I") file >> d.I;
        else if(word == "FLOORS") file >> d.nFloors;
        else if(word == "Mass1") file >> d.M1;
        else if(word == "Mass2") file >> d.M2;
        else if(word == "Mass3") file >> d.M3;

    }

    return d;
}

#include <iomanip>     // VERY IMPORTANT


void writeOutput(const std::string& filename,
                  double deflection,
                  const std::vector<std::vector<double>>& K,
                  const std::vector<std::vector<double>>& M)
{
    std::ofstream file(filename);

    file << "============================\n";
    file << "      STRUCTURAL RESULTS    \n";
    file << "============================\n\n";

    // ---- DEFLECTION PART ----
    file << "DEFLECTION RESULT\n";
    file << "-----------------\n";
    file << "Deflection = " << deflection << "\n\n";

    // ---- STIFFNESS MATRIX ----
    file << "STIFFNESS MATRIX\n";
    file << "----------------\n\n";

    int n = K.size();

    // Header
    file << std::setw(10) << " ";
    for(int j=1; j<=n; j++)
        file << std::setw(10) << ("mod" + std::to_string(j));

    file << "\n";

    // Matrix rows
    for(int i=1; i<=n; i++)
    {
        file << std::setw(10) << ("floor" + std::to_string(i));

        for(int j=1; j<=n; j++)
            file << std::setw(10) << K[i-1][j-1];

        file << "\n";
    }
    // ---- MASS MATRIX ----
    file << "MASS MATRIX\n";
    file << "----------------\n\n";
    // Header
    file << std::setw(10) << " ";
    for(int j=1; j<=n; j++)
        file << std::setw(10) << ("mod" + std::to_string(j));

    file << "\n";

    // Matrix rows
    for(int i=1; i<=n; i++)
    {
        file << std::setw(10) << ("floor" + std::to_string(i));

        for(int j=1; j<=n; j++)
            file << std::setw(10) << M[i-1][j-1];

        file << "\n";
    }

    file.close();
}

