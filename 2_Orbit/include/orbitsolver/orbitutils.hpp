#ifndef ORBITUTILS_HPP_
#define ORBITUTILS_HPP_
//=======================================
//! \file orbitutils.hpp
//! \brief Defines constants and utilities for use across OrbitSolver
//=======================================

// STL headers
#include <vector>


// Declarations
using vecdbl = std::vector<double>;


//=======================================
// Scientific constants
//=======================================

//! \brief Gravitational constant, m^3 kg^-1 s^-2
constexpr double G_SI = 6.67408e-11;
//! \brief Seconds in a year
constexpr double SECONDS_IN_YEAR = 31536000.0;

//! Return the larger argument
template <class T> const T& max (const T& a, const T& b)
{
  return (a<b)?b:a;
}
//! Return the smaller argument
template <class T> const T& min (const T& a, const T& b)
{
  return (a>b)?b:a;
}


#endif // ORBITUTILS_HPP_
