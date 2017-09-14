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

int readGraph(char *input, int **E, int *E_size){
	std::fstream pfile;
	int count = 0, n = 0;
	int *a, *b;
	int tmp;

	pfile.open(input,std::ios::in);
    assert( pfile );

    // skip first line
    pfile.ignore(4096, '\n');

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Count size
    while( !pfile.eof() ) {
    	count++;
    	pfile.ignore(4096, '\n');
    }
    std::cout << "Size of data is " << count << "x" << 2 << std::endl;

    // Return to top of file
    pfile.clear();
  	pfile.seekg(0, std::ios::beg);

  	a  = new int[count];
    b  = new int[count];
    *E = new int[2*count];

    // Read graph
  	pfile.ignore(4096, '\n');
  	while( !pfile.eof() ) {
    	pfile >> a[n];
    	pfile >> b[n];
    	n++;
    	pfile.ignore(4096, '\n');
    }
    // Change to zero base
    for (int i = 0; i < count; i++)
    {
    	a[i] = a[i] - 1;
    	b[i] = b[i] - 1;
    }
    std::copy(a, a+count, *E);
    std::copy(b, b+count, *E+count);
    *E_size = count;

    pfile.close();

    return 0;
}