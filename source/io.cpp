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

        else if(word == "STATIONS")
        {
            double x;
            while(file >> x)
            {
                d.stations.push_back(x);

                // stop when END appears
                if(file.peek() == 'E') break;
            }
        }
    }

    return d;
}

void writeOutput(const std::string& filename,
                 const std::vector<double>& x,
                 const std::vector<double>& def)
{
    std::ofstream file(filename);

    file << "X  Deflection\n";

    for(size_t i=0; i<x.size(); i++)
    {
        file << x[i] << "  " << def[i] << "\n";
    }
}

#include <iomanip>     // VERY IMPORTANT

void writeMatrix(const std::string& filename,
                 const std::vector<std::vector<double>>& K)
{
    std::ofstream file(filename);

    int n = K.size();

    file << "STIFFNESS MATRIX\n\n";

    // ===== HEADER =====
    file << std::setw(10) << " ";

    for(int j=1; j<=n; j++)
    {
        file << std::setw(10) << ("mod" + std::to_string(j));
    }

    file << "\n";

    // ===== MATRIX =====
    for(int i=1; i<=n; i++)
    {
        file << std::setw(10) << ("floor" + std::to_string(i));

        for(int j=1; j<=n; j++)
        {
            file << std::setw(10) << K[i-1][j-1];
        }

        file << "\n";
    }

    file.close();
}

