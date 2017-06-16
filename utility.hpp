////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    utility.hpp
/// @brief   The utility header
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#pragma once

#include <getopt.h>

void read_args( int argc, char** argv, char *&filename, int &method );
void disp_usage( const char *bin );
