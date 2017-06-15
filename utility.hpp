////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    utility.hpp
/// @brief   The utility header
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#pragma once

#include <getopt.h>

const char* const short_opt = ":hf:w:";

const struct option long_opt[] = {
  {"help",   0, NULL, 'h'},
  {"file",   1, NULL, 'f'},
  {"weight", 1, NULL, 'w'},
  {NULL,     0, NULL, 0}
};

void Usage ( const char *bin );
