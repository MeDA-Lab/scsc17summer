////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    utility.hpp
/// @brief   The utilities
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include "utility.hpp"

using namespace std;

void Usage ( const char *bin ) {
  cout << "Usage: " << bin << " [OPTIONS]" << endl;
  cout << "Options:" << endl;
  cout << "  -h, --help            Display this information" << endl;
  cout << "  -f, --file            The graph file" << endl;
  cout << "  -w, --weight          0: Simple, 1: Complex" << endl;
}
