#ifndef IO_HPP_
#define IO_HPP_
//=======================================
//! \file io.hpp
//! \brief Defines input/output utilities
//=======================================


// STL headers
#include <string>

// OrbitSolver headers
#include "orbitutils.hpp"


// Write out data
void savetxt(const std::string&, const vecdbl&, const vecdbl&);


#endif // IO_HPP_