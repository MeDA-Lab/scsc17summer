////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    read_graph.cpp
/// @brief   Read graph from file
///
/// @author  William Liao
///

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <iostream>
#include <fstream>

int readGraph(char *input, double *E){
	fstream pfile;
	int count = 0;
	double *a, *b;

	pfile.open(input,ios::in);
    assert( pfile );

    while( !pfile.eof() ) {
    	++count;
    }
    std::cout << "Size of data is " << count/2 << "x" << 2 << std::endl;

    return 0;
}