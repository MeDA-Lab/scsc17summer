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
#include <cuda_runtime.h>
#include "cusparse.h"
#include <mkl.h>

using namespace std;

int GraphAdjacency(int *E, int E_size,
	int *nnz, int **cooRowIndA,
	int **cooColIndA, double **cooValA, int *n){
	int pos1, pos2;
	int *d_cooRowIndA, *d_cooColIndA;
	double  *d_val, *d_val_sorted;
	double *tmp_array;
	vector<double> v1 (2*E_size , 1.0);
	cusparseHandle_t handle;
	cusparseIndexBase_t idxBase = CUSPARSE_INDEX_BASE_ZERO;
	cusparseStatus_t stat;
	size_t pBufferSizeInBytes = 0;
	void *pBuffer = NULL;
	int *P = NULL;

	tmp_array = new double[2*E_size];
	copy(E, E+2*E_size, tmp_array);

	pos1 = cblas_idamax(E_size, tmp_array, 1);
	pos2 = cblas_idamax(E_size, tmp_array+E_size, 1);
	*n    = max(E[pos1] , E[pos2+E_size]);
	cout << "n = " << *n << endl;

	*cooRowIndA = new int[2*E_size];
	*cooColIndA = new int[2*E_size];
	*cooValA    = new double[2*E_size];

	*nnz = 2*E_size;
	copy(E , E+2*E_size , *cooRowIndA);
	copy(E+E_size, E+2*E_size, *cooColIndA);
	copy(E , E+E_size, *cooColIndA+E_size);
	copy(v1.begin(),v1.end(),*cooValA);

	int *test;
	test = new int[2*E_size];
	copy(E+E_size, E+2*E_size, test);
	copy(E, E+E_size, test);
	cout<<test[E_size-1]<<endl;
	cout<<test[E_size]<<endl;

	stat = cusparseCreate(&handle);
	assert( stat == CUSPARSE_STATUS_SUCCESS );

	cudaMalloc( &d_cooColIndA, 2*E_size*sizeof(int) );
	cudaMalloc( &d_cooRowIndA, 2*E_size*sizeof(int) );
	cudaMalloc( &d_val, 2*E_size*sizeof(double) );
	cudaMalloc( &d_val_sorted, 2*E_size*sizeof(double) );

	cudaMemcpy(d_cooColIndA, *cooColIndA, 2*E_size*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_cooRowIndA, *cooRowIndA, 2*E_size*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_val, *cooValA, 2*E_size*sizeof(double), cudaMemcpyHostToDevice);

	cusparseXcoosort_bufferSizeExt(handle, *n, *n, *nnz, d_cooRowIndA, d_cooColIndA, &pBufferSizeInBytes);
	cudaMalloc( &pBuffer, sizeof(char)* pBufferSizeInBytes);

	cudaMalloc( (void**)&P, sizeof(int)*(*nnz));
	cusparseCreateIdentityPermutation(handle, *nnz, P);

	cusparseXcoosortByRow(handle, *n, *n, *nnz, d_cooRowIndA, d_cooColIndA, P, pBuffer);

	cusparseDgthr(handle, *nnz, d_val, d_val_sorted, P, CUSPARSE_INDEX_BASE_ZERO);

	cudaMemcpy(*cooRowIndA, d_cooRowIndA, 2*E_size*sizeof(int),  cudaMemcpyDeviceToHost);
	cudaMemcpy(*cooColIndA, d_cooColIndA, 2*E_size*sizeof(int),  cudaMemcpyDeviceToHost);
	cudaMemcpy(*cooValA, d_val_sorted, 2*E_size*sizeof(double),  cudaMemcpyDeviceToHost);

/*	stat = cusparseXcoo2csr(handle, cooRowIndA, *nnz, *n, *csrRowPtrA, idxBase);
	assert( stat == CUSPARSE_STATUS_SUCCESS );*/

	stat = cusparseDestroy(handle);
	assert( stat == CUSPARSE_STATUS_SUCCESS );

	return 0;
}