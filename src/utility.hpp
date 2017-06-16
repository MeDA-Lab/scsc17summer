////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    utility.hpp
/// @brief   The utility header
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef SCSC_UTILITY_HPP
#define SCSC_UTILITY_HPP

#include <getopt.h>
#include <def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads the arguments.
///
/// @param[in]   argc      The number of input arguments.
/// @param[in]   argv      The input arguments.
///
/// @param[out]  filename  The filename.
/// @param[out]  method    The method.
///
void read_args( int argc, char** argv, char *&filename, Method &method );

#endif  // SCSC_UTILITY_HPP
