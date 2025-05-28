//=======================================
//! \file orbit_example.hpp
//! \brief Runs a sample EOBorbit
//! This is our ultimate executable.
//! It will use the library we created.
//=======================================


// STL headers
#include <iostream>

// OrbitSolver headers
#include <orbitsolver/io.hpp>
#include <orbitsolver/orbits.hpp>


//=======================================


int main(int argc, char*argv[])
{
    if (argc<=1)
    {
        std::cerr << "No argument was passed, ";
        std::cerr << "please specify file name to save to.\n";

        return EXIT_FAILURE;
    }

    // Sun-Earth system
    double mass = 1.9884e30;    // kg
    double a = 1.49598e11;      // m
    double e = 0.0167;

    // Set the time vector
    // Track the evolution once per day
    double seconds_in_a_day = 24*3600;
    int days = 365;
    vecdbl times = {0}; times.reserve(days+1);
    for (int i = 1; i <= days; i++)
    {
       times.push_back(i*seconds_in_a_day);
    }
    
    vecdbl phi;
    // Evolve phi
    EOBorbit(phi, times, mass, a, e, 0., gsl_rk54);

    // Store data
    savetxt(argv[1], times, phi);

    return 0;
}