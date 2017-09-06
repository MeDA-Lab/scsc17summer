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
#include <algorithm>
#include <vector>
#include <mkl.h>

using namespace std;

int GraphAdjacency(double *E, int E_size,
	int *nnz, int **csrRowPtrA,
	int **csrColIndA, double **csrValA, int *n){
	int pos1, pos2, *cooRowIndA;
	vector<double> v1 (E_size , 1.0);

	pos1 = cblas_idamax(E_size, E, 1);
	pos2 = cblas_idamax(E_size, E+E_size, 1);
	*n    = max(E[pos1] , E[pos2+E_size]);
	cout << "n = " << *n << endl;

	cooRowIndA  = new double[E_size];
	*csrColIndA = new double[E_size];
	*csrValA    = new double[E_size];
	*csrRowPtrA = new double[n+1];

	*nnz = *n;
	copy(E , E+E_size , cooRowIndA);
	copy(E+E_size, E+2*E_size, *csrColIndA);
	copy(v1.begin(),v1.end(),*csrValA);

	return 0;
}