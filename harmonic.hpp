#ifndef SCSC_HARMONIC_HPP
#define SCSC_HARMONIC_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <getopt.h>
#include <tuple>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;
void ReadObj (const string filename, vector<int> &face,  vector<double> &vertex, vector<double> &color);
void ConstructLaplacian (const int method, vector<int> &face, vector<double> &vertex, double *A, int lda);
void VerifyBoundary(vector<int> &face, vector<int> &vertex_b, vector<int> &vertex_i);
void Finduvb(vector<double> &vertex, vector<int> &vertex_b, double *uvb, int ldu);
void BuildLS(vector<int> &face, vector<double> &vertex, double *uvb, int ldu, double *A, int lda, double* rhs, int ldr);
void SolveLS(int n, double* A, int lda, int nrhs, double *rhs, int ldr, double *x, int ldx);
#endif