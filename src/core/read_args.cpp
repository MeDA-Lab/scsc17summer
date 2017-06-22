////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    read_args.cpp
/// @brief   The implementation of arguments reader.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
/// @author  Yuhsiang Tsai <<yhmtsai@gmail.com>>
///

#include <iostream>
#include <harmonic.hpp>

using namespace std;

const char* const short_opt = ":hf:w:o:";

const struct option long_opt[] = {
  {"help",   0, NULL, 'h'},
  {"file",   1, NULL, 'f'},
  {"weight", 1, NULL, 'w'},
  {"output", 1, NULL, 'o'},
  {NULL,     0, NULL, 0}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Display the usage.
///
/// @param  bin  the name of binary file.
///
void dispUsage( const char *bin ) {
  cout << "Usage: " << bin << " [OPTIONS]" << endl;
  cout << "Options:" << endl;
  cout << "  -h, --help            Display this information" << endl;
  cout << "  -f, --file            The graph file" << endl;
  cout << "  -w, --weight          0: Simple, 1: Complex" << endl;
  cout << "  -o, --output          The output file" << endl;
}

void readArgs( int argc, char** argv, const char *&input, const char *&output, Method &method ) {
  int c = 0;
  while ( (c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1 ) {
    switch ( c ) {
      case 'h': {
        dispUsage(argv[0]);
        exit(0);
      }

      case 'f': {
        input = optarg;
        break;
      }

      case 'w': {
        method = static_cast<Method>(atoi(optarg));
        assert(method >= Method::SIMPLE && method < Method::COUNT );
        break;
      }

      case 'o': {
        output = optarg;
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
