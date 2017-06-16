#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "harmonic.hpp"
#include "utility.hpp"

using namespace std;

int main ( int argc, char** argv ){
    char *filename = nullptr;
    int method = 0; // default : simple weight

    read_args(argc, argv, filename, method);

    // cout << filename << " " << method << endl;
    vector <int> face;
    vector <double> vertex, color, vertex_i, vertex_b;
    double *uvb = nullptr, *A = nullptr, *rhs = nullptr;
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
