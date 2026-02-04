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

void writeMatrix(const std::string& filename,
                 const std::vector<std::vector<double>>& K)
{
    std::ofstream file(filename);

    file << "STIFFNESS MATRIX\n";

    for(size_t i=0; i<K.size(); i++)
    {
        for(size_t j=0; j<K[i].size(); j++)
        {
            file << K[i][j] << " ";
        }
        file << "\n";
    }
}
