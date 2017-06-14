#ifndef SCSC_HARMONIC_HPP
#define SCSC_HARMONIC_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <getopt.h>
#include <tuple>
#include <vector>
using namespace std;
typedef tuple<int, int, int> int3;
typedef tuple<double, double, double> double3;
void ReadObj (string filename, vector<double3> &face, vector<int3> &vertex, vector<double3> &color);

#endif