////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    sgp.hpp
/// @brief   The main header for spectral graph partitioning.
///
/// @author  William Liao
///

#ifndef SCSC_SGP_HPP
#define SCSC_SGP_HPP

#include <cassert>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads the graph file.
///
/// @param[in]   input   the path to the object file.
///
/// @param[out]  E       the edge list; pointer.
///
/// @note  The arrays are allocated by this routine (using new).
///
int readGraph(char *input, double *E);
#endif  // SCSC_SGP_HPP