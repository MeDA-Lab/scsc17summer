////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    graph_adjacency.cpp
/// @brief   Construct adjacency matrix of graph
///
/// @author  William Liao
///

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <iostream>
#include <fstream>
#include <mkl.h>

using namespace std;

int GraphAdjacency(double *E, int E_size,
	int **nnz, int **csrRowPtrA,
	int **csrColIndA, double **csrValA){
	int n, pos1, pos2, *cooRowIndA;

	pos1 = cblas_idamax(E_size, E, 1);
	cout << "pos1 = " << pos1;
	pos2 = cblas_idamax(E_size, E+E_size, 1);
	cout << "pos2 = " << pos2;
	n    = max(E[pos1-1],E[pos2-1]);
	cout << "n = " << n << endl;

	return 0;
}