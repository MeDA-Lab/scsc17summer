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

int GraphAdjacency(int *E, int E_size,
	int *nnz, int **csrRowPtrA,
	int **csrColIndA, double **csrValA, int *n){
	int pos1, pos2, *cooRowIndA;
	double *tmp_array;
	vector<double> v1 (E_size , 1.0);

	tmp_array = new double[2*E_size];
	copy(E, E+2*E_size, tmp_array);

	pos1 = cblas_idamax(E_size, tmp_array, 1);
	pos2 = cblas_idamax(E_size, tmp_array+E_size, 1);
	*n    = max(E[pos1] , E[pos2+E_size]);
	cout << "n = " << *n << endl;

	cooRowIndA  = new int[E_size];
	*csrColIndA = new int[E_size];
	*csrValA    = new double[E_size];
	*csrRowPtrA = new int[(*n)+1];

	*nnz = *n;
	copy(E , E+E_size , cooRowIndA);
	copy(E+E_size, E+2*E_size, *csrColIndA);
	copy(v1.begin(),v1.end(),*csrValA);

	return 0;
}