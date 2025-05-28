//=======================================
//! \file orbits.cpp
//! \brief Implements the solver and orbit classes
//=======================================


// STL headers
#include <iostream>

// OrbitSolver headers
#include "orbitsolver/orbits.hpp"


//=======================================


int EOBgslrk54Solver::RHS(
    double t,
    const double y[],
    double ydot[],
    void *params
)
{
    // Dereference the params pointer
    // This is old C-style and is not recommended for modern codes
    // A better alternative would be for GSL to use templates
    const EOBgslrk54Solver* solver = static_cast<EOBgslrk54Solver*>(params);

    ydot[0] = solver->phidot(y[0]);

    return GSL_SUCCESS;
}

//! \param e: The orbital eccentricity
//! \param omega: The longitude of pericenter
//! \param phi0: The initial phi value
EOBgslrk54Solver::EOBgslrk54Solver(
    double e,
    double omega,
    double phi0
)
{
    // Set the parameters
    this->e = e;
    this->omega = omega;
    this->phi0 = phi0;

    // The absolute error tolerance
    double epsabs = 1e-8;
    // The relative error tolerance
    double epsrel = 1e-8;
    // Compute the initial step-size
    double h = h_guess(phi0, epsabs, epsrel);
    std::cout << "Initial step-size: " << h << std::endl;

    // Set up the solver
    sys = {RHS, nullptr, 1, this};
    driver = gsl_odeiv2_driver_alloc_y_new(
        &sys, gsl_odeiv2_step_rkf45, h, epsabs, epsrel
    );
}

EOBgslrk54Solver::~EOBgslrk54Solver()
{
    // Free memory to driver
    gsl_odeiv2_driver_free(driver);
}

// Follows "Starting Step Size" of Sec. II.4
// in Hairer et al., Solving Ordinary Differential Equations I
double EOBgslrk54Solver::h_guess(
    double y0,
    double epsabs,
    double epsrel
)
{
    // The error scale
    double scale = epsabs + abs(y0)*epsrel;
    // Derivative at the first point
    double dy0 = phidot(y0);

    double d0 = abs(y0/scale);
    double d1 = abs(dy0/scale);
    // First guess
    double h0 = 1.e-6;
    if (!(d0 < 1.e-5 || d1 < 1.e-5))
    {
        h0 = 0.01*(d0/d1);
    }

    // Do an explicit Euler step
    double y1 = y0 + h0*dy0;
    // Compare the sizes of the consecutive derivatives
    double dy1 = phidot(y1);
    double d2 = abs(dy1-dy0)/scale/h0;
    // Returns the larger of (d1,d2)
    double maxd = max(d1,d2);

    // Estimate a new step size
    double h1 = h0*1.e-3;
    if (maxd <= 1.e-15)
    {
        h1 = max(1.e-6, h1);
    }
    else
    {
        h1 = pow(0.01/maxd, 0.2); // 4th order --> 1/(p+1) = 1/5
    }

    h0 *= 100;
    return min(h0,h1);
}

double EOBgslrk54Solver::phidot(double phi) const
{
    double out = 1. + e * cos(phi-omega);

    return out*out;
}

int EOBgslrk54Solver::solve(
    vecdbl& phi,
    const vecdbl& times
)
{
    int status;
    double last_t = times.front();
    double y[1] = {phi0};

    for (auto t = times.begin()+1; t != times.end(); t++)
    {
        status = gsl_odeiv2_driver_apply(driver, &last_t, *t, y);

        if (status != GSL_SUCCESS)
        {
            std::cerr << "!! error at t=" << *t << "\n";
            std::cerr << "!! return status=" << status << std::endl;
            break;
        }

        phi.push_back(y[0]);
    }

    return GSL_SUCCESS;
}

//! \param phi: [out] Output vector of phi values
//! \param times: Vector of points in time to evaluate orbit, sec
//! \param mass: Total mass of system, kg
//! \param a: Semi-major axis, m
//! \param omega: Longitude of pericenter
//! \param solverT: solverType
void EOBorbit(
    vecdbl& phi, 
    const vecdbl& times, 
    double mass, 
    double a, 
    double e, 
    double omega, 
    solverType solverT
)
{
    // Compute the semi-latus rectum
    double p = a / (1.-e*e);
    std::cout << "p = " << p << " m\n";

    // Compute the time scale
    double tStar = sqrt(p*p*p / (G_SI*mass));
    std::cout << "t* = " << tStar << " s\n";

    // Rescale time
    vecdbl scaled_times;
    for (auto &t: times)
    {
        scaled_times.push_back(t/tStar);
    }

    // If phi vector is empty, set phi0 to 0
    double phi0 = 0.;
    if (phi.empty())
    {
        phi.push_back(phi0);
    }
    // Else, use first element as phi0
    else
    {
        phi0 = phi.front();
    }

    // Initialize the solver
    // This is simply a pointer to an abstract class
    EOBsolver * solver;
    // This will bind a derived class to the pointer
    switch (solverT)
    {
    case gsl_rk54:
        solver = new EOBgslrk54Solver(e, omega, phi0);
        break;
    default:
        std::cerr << "The input solver is not supported.\n";
        break;
    }

    // We never actually explicitly call the derived class!
    // Solve the system
    solver->solve(phi, scaled_times);
    std::cout << "Integration successful!\n";

    delete solver;
}