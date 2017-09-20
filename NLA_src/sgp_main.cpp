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
#include <timer.hpp>
#include "sgp.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Main function for spectral graph partitioning.
///
int main( int argc, char** argv ){
	int err_test;

	// need at least 2 argument!
    assert( argc >= 2 );

    // check 2nd argument
    assert( argv[1] != NULL );

    // read file
    int E_size_r, E_size_c, *E;
    cout << "read file..." << endl;
    err_test = readGraph(argv[1], &E, &E_size_r, &E_size_c);
    assert( err_test == 0 );

    // set graph type
    int type;
    char flag;
    if ( argc == 2 )
    {
        type = setgraphtype(E_size_c);
    }else if( argc == 3 ){
        type = setgraphtype(argv[2], E_size_c);
    }

    if ( type == 0 )
    {
        flag = 'S';
    }else if( type == 1 ){
        flag = 'D';
    }else if ( type == 2 ){
        flag = 'W';
    }

    // Construct adjacency matrix of graph
    int nnz, *cooRowIndA, *cooColIndA, n;
    double *cooValA;
    cout << "Construct adjacency matrix of graph..." << endl;
    err_test = GraphAdjacency(E, E_size_c, &nnz, &cooRowIndA, &cooColIndA, &cooValA, &n, flag);
    assert( err_test == 0 );
    cout << "nnz = " << nnz << endl;

    // Construct Laplacian
    int *csrRowIndA, *csrColIndA;
    double  *csrValA;
    double shift_sigma = 0;
    GraphLaplacian(&nnz, cooRowIndA, cooColIndA, cooValA, n, &csrRowIndA, &csrColIndA, &csrValA, shift_sigma);
    cout << "nnz = " << nnz << endl;

    // Shift to zero-based indexing
    for (int i = 0; i < nnz; i++)
    {
    	csrColIndA[i] = csrColIndA[i]-1;
    }
    for (int i = 0; i < n+1; i++)
    {
    	csrRowIndA[i] = csrRowIndA[i]-1;
    }

    // Solve EVP
    double mu0 = 1.5, mu;
    double *x, timer;
    x = new double[n];
    char flag = 'H';

    cout << "Solving Eigenvalue Problem..." << endl;

    switch (flag){
    	case 'H':
    		tic(&timer);
    		solveShiftEVPHost(n, nnz, csrValA, csrRowIndA, csrColIndA, mu0, &mu, x);
    		toc(&timer);
    		break;
    	case 'D':
    		tic(&timer);
    		solveShiftEVP(n, nnz, csrValA, csrRowIndA, csrColIndA, mu0, &mu, x);
    		toc(&timer);
    		break;
    }

    cout << "The estimated eigenvalue near " << mu0 << " = " << mu << endl;

    return 0;
}