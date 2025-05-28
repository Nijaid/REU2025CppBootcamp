//=======================================
//! \file io.cpp
//! \brief Implements the input/output utilities
//=======================================


// STL headers
#include <iostream>
#include <fstream>

// OrbitSolver headers
#include "orbitsolver/io.hpp"


//=======================================


void savetxt(
    const std::string& filename,
    const vecdbl& col1,
    const vecdbl& col2
)
{
    // Open the file
    std::ofstream file (filename);
    // Set precision to double
    file.precision(15);

    if (file.good())
    {
        // Write header
        file << "#time [s]        phi\n";

        // Write each row
        for (size_t i = 0; i < col1.size(); i++)
        {
            file << col1.at(i) << " " << col2.at(i) << "\n";
        }
    }
    else
    {
        // Error
        std::cerr << "Unable to write out to " << filename << std::endl;
    }
    
    file.close();
}