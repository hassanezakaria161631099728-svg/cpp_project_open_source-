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
        else if(word == "HFLOOR") file >> d.h;
        else if(word == "EC") file >> d.EC;
        else if(word == "IX") file >> d.IX;
        else if(word == "IY") file >> d.IY;
    }

    return d;
}

#include <iomanip>     // VERY IMPORTANT


void writeOutput(const std::string& filename,
                 double deflection,double fx,double fy,
                 const std::vector<std::vector<double>>& SA,
                 const std::vector<std::vector<double>>& Sx,
                 const std::vector<std::vector<double>>& Sy,
                 const std::vector<std::vector<double>>& M,
                 const std::vector<std::vector<double>>& Dx,
                 const std::vector<std::vector<double>>& Dy)
{
    std::ofstream file(filename);

    file << "============================\n";
    file << "      STRUCTURAL RESULTS    \n";
    file << "============================\n\n";

    // ---- DEFLECTION PART ----
    file << "-----------------\n";
    file << "Deflection " << deflection << "\n\n";
    // ---- f PART ----
    file << "-----------------\n";
    file << "fx " << fx << "\n\n";
    // ---- f PART ----
    file << "-----------------\n";
    file << "fy " << fy << "\n\n";
    // ---- SA MATRIX ----
    file << "SA MATRIX\n";
    file << "----------------\n\n";

    int n = SA.size();

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
            file << std::setw(10) << SA[i-1][j-1];

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

    // ---- STIFFNESS MATRIX ----
    file << "STIFFNESS MATRIX\n";
    file << "----------------\n\n";
    file << "X\n\n";
    file << std::scientific<<std::setprecision(1);
    file << std::setw(10) << " ";
    for(int j=1; j<=n; j++)
        file << std::setw(10) << ("mod" + std::to_string(j));

    file << "\n";

    for(int i=1; i<=n; i++)
    {
        file << std::setw(10) << ("floor" + std::to_string(i));

        for(int j=1; j<=n; j++)
            file << std::setw(10) << Sx[i-1][j-1];

        file << "\n";
    }
    file << "----------------\n\n";
    file << "Y\n\n";
    file << std::setw(10) << " ";
    for(int j=1; j<=n; j++)
        file << std::setw(10) << ("mod" + std::to_string(j));

    file << "\n";

    for(int i=1; i<=n; i++)
    {
        file << std::setw(10) << ("floor" + std::to_string(i));

        for(int j=1; j<=n; j++)
            file << std::setw(10) << Sy[i-1][j-1];

        file << "\n";
    }

    // ---- Dynamic MATRIX ----
    file << "Dynamic MATRIX\n";
    file << "----------------\n\n";
    file << "X\n\n";
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
            file << std::setw(10) << Dx[i-1][j-1];

        file << "\n";
    }
    file << "----------------\n\n";
    file << "Y\n\n";
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
            file << std::setw(10) << Dy[i-1][j-1];

        file << "\n";
    }

    file.close();
}

