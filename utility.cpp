////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    utility.hpp
/// @brief   The utilities
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include "utility.hpp"

using namespace std;

const char* const short_opt = ":hf:w:";

const struct option long_opt[] = {
  {"help",   0, NULL, 'h'},
  {"file",   1, NULL, 'f'},
  {"weight", 1, NULL, 'w'},
  {NULL,     0, NULL, 0}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Read arguments
///
/// @param  bin  the name of binary file.
///
void read_args( int argc, char** argv, char *&filename, int &method ) {
  int c = 0;
  while ( (c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1 ) {
    switch ( c ) {
      case 'h': {
        disp_usage(argv[0]);
        exit(0);
      }

      case 'f': {
        filename = optarg;
        break;
      }

      case 'w': {
        method = atoi(optarg);
        break;
      }

      case ':': {
        cout << "Option -" << optopt << " requires an argument.\n";
        abort();
      }

      case '?': {
        cout << "Unknown option -" << optopt << endl;
        abort();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Display usage
///
/// @param  bin  the name of binary file.
///
void disp_usage( const char *bin ) {
  cout << "Usage: " << bin << " [OPTIONS]" << endl;
  cout << "Options:" << endl;
  cout << "  -h, --help            Display this information" << endl;
  cout << "  -f, --file            The graph file" << endl;
  cout << "  -w, --weight          0: Simple, 1: Complex" << endl;
}