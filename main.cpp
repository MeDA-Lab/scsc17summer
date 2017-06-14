#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <getopt.h>
#ifdef USEMKL
#include <mkl.h>
#endif
using namespace std;
const char *const short_opt = ":hf:w:";
const struct option long_opt[] = {
    {"help",        0, NULL, 'h'},
    {"file",        1, NULL, 'f'},
    {"weight",      1, NULL, 'w'},
    {NULL,          0, NULL, 0}
};

void Usage ( char *call ) {
    cout << "Usage: " << call << " [OPTIONS]\n";
    cout << "Options:\n";
    cout << "\t-h or --help         Display this information\n";
    cout << "\t-f or --file         The graph file\n";
    cout << "\t-w or --weight       0:Simple or 1:Complex\n";
}
int main ( int argc, char** argv ){
    int c=0;
    string filename="";
    int method = 0; // default : simple weight
    while ( (c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1 ) {
        switch ( c ) {
            case 'h':
                Usage( argv[0] );
                return 0;
            case 'f':
                filename = optarg;
                break;
            case 'w':
                method = atoi(optarg);
                break;
            case ':':
                cout << "Option -" << optopt << " requires an argument.\n";
                return -1;
            case '?':
                char c_char = optopt;
                cout << "Unknown option -" << c_char << endl;
                return -1;
        }
    }
    // cout << filename << " " << method << endl;
    return 0;
}