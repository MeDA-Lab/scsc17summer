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
    int E_size, *E;
    cout << "read file..." << endl;
    err_test = readGraph(argv[1], &E, &E_size);
    assert( err_test == 0 );

    // Construct adjacency matrix of graph
    int nnz, *cooRowIndA, *cooColIndA, n;
    double *cooValA;
    cout << "Construct adjacency matrix of graph..." << endl;
    err_test = GraphAdjacency(E, E_size, &nnz, &cooRowIndA, &cooColIndA, &cooValA, &n);
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
    double *x;
    x = new double[n];
    char flag = 'D';

    switch (flag){
    	case 'H':
    		solveShiftEVPHost(n, nnz, csrValA, csrRowIndA, csrColIndA, mu0, &mu, x);
    		break;
    	case 'D':
    		solveShiftEVP(n, nnz, csrValA, csrRowIndA, csrColIndA, mu0, &mu, x);
    		break;
    }

    cout << "The estimated eigenvalue near " << mu0 << " = " << mu << endl;

    return 0;
}