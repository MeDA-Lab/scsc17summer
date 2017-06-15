#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "harmonic.hpp"
#include "utility.hpp"
using namespace std;
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
    vector <int> face;
    vector <double> vertex, color, vertex_i, vertex_b;
    double *uvb = NULL, *A = NULL, *rhs = NULL;
    int ldu = 0, ldr = 0, lda = 0;
    // // Read Obj file
    // void ReadObj (filename, face, vertex, color);
    // // Construct Laplacian matrix
    // void ConstrutLaplacian (method, face, vertex);
    // // Find the boundary and interior vertex
    // void VerifyBoundary(face, vertex_b, vertex_i);
    // // Find the uvb
    // ldu = vertex_b.size();
    // uvb = new double [ ldu * 2 * sizeof(double)];
    // lda = vertex_i.size();
    // A   = new double [ lda * lda * sizeof(double)];
    // ldr = vertex_i.size();
    // rhs = new double [ ldr * 2 * sizeof(double)];
    // void Finduvb(&vertex, &vertex_b, *uvb, ldu);
    // // Build linear system (Ax=b, A=L_ii b=-L_ibub)
    // void BuildLS(vector<int> &face, vector<double> &vertex,
    //             double *uvb, int ldu, double *A, int lda, double* rhs, int ldr);
    // Solve linear system

    // Connect the answer u_i and u_b

    // Plot mesh

    delete [] uvb;
    delete [] A;
    delete [] rhs;
    return 0;
}