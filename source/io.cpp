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
    // ----  MATRIX ----
    file << "MATRIX\n";
    file << "----------------\n\n";

     // ===== LOCAL HELPER (LAMBDA) =====
    auto printMatrix = [&](const std::vector<std::vector<double>>& A,
                           const std::string& title,
                           const std::string& mode)
    {
        int n = A.size();

        file << title << "\n";
        file << "----------------\n\n";
       if(mode == "scientific")
       {
         file << std::scientific << std::setprecision(2);
       }
       else if(mode == "normal")
       {
         file << std::fixed << std::setprecision(0);
       }
         // header
        file << std::setw(10) << " ";
        for(int j=1; j<=n; j++)
            file << std::setw(10) << ("mod" + std::to_string(j));

        file << "\n";

        // rows
        for(int i=1; i<=n; i++)
        {
            file << std::setw(10) << ("floor" + std::to_string(i));

            for(int j=1; j<=n; j++)
                file << std::setw(10) << A[i-1][j-1];

            file << "\n";
        }

        file << "\n";
    };
    // ===== END LAMBDA =====
    printMatrix(SA, "SA", "normal");
    printMatrix(Sx, "Sx", "scientific");
    printMatrix(Sy, "Sy", "scientific");
    printMatrix(M, "M", "normal");
    printMatrix(Dx, "Dx", "scientific");
    printMatrix(Dy, "Dy", "scientific");

    file.close();
}

