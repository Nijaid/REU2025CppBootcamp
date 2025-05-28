#ifndef ORBITS_HPP_
#define ORBITS_HPP_
//=======================================
//! \file orbits.hpp
//! \brief Defines the solver and orbit classes
//=======================================


// OrbitSolver headers
#include "orbitutils.hpp"

// GSL headers
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>


//=======================================


//! \enum solverType
enum solverType
{
    gsl_rk54,    //< GSL RK5(4) method
};

//! \class EOBsolver
//! \brief Abstract class for effective one-body orbit solvers.
//! All that this class needs to know is that there is a
//! differential equation for phi, but it doesn't need to implement it.
class EOBsolver
{
public:
    // Virtual destructor
    // Allows derived classes to safely handle its destruction,
    // even if they don't need an explicit destructor.
    virtual ~EOBsolver() = default;

    // Declaration of the diff eq. The only argument is phi itself
    virtual double phidot(double) const = 0;

    virtual int solve(vecdbl&, const vecdbl&) = 0;
};

class EOBgslrk54Solver : public EOBsolver
{
public:
    EOBgslrk54Solver(double, double, double);
    ~EOBgslrk54Solver();

    double phidot(double) const override;
    // The RHS for GSL
    static int RHS(double, const double [], double [], void*);
    double h_guess(double, double, double);
    int solve(vecdbl&, const vecdbl&) override;

private:
    // The orbital eccentricity
    double e;
    // The longitude of pericenter
    double omega;
    // Initial phi value
    double phi0;
    
    gsl_odeiv2_system sys;
    gsl_odeiv2_driver *driver;
};


void EOBorbit(vecdbl&, const vecdbl&, double, double, double, double, solverType);

#endif // ORBITS_HPP_
