////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    sgp_main.cpp
/// @brief   The main function.
///
/// @author  William Liao
///

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include "sgp.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Main function for spectral graph partitioning.
///
int main( int argc, char** argv ){
	int err_test;

	// need 2 argument!
    assert( argc == 2 );

    // check 2nd argument
    assert( argv[1] != NULL );

    // read file
    double *E;
    cout << "read file..." << endl;
    err_test = readGraph(argv[1], &E);
    for (int i = 0; i < 1298; i++)
    {
    	cout << E[i] << "\t" << E[i+count] << endl;
    }

    return 0;
}