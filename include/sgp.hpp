////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    sgp.hpp
/// @brief   The main header for spectral graph partitioning.
///
/// @author  William Liao
///

#ifndef SCSC_SGP_HPP
#define SCSC_SGP_HPP

#include <cassert>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads the graph file.
///
/// @param[in]   input   the path to the object file.
///
/// @param[out]  E       the edge list; pointer.
///
/// @note  The arrays are allocated by this routine (using new).
///
int readGraph(char *input, int **E, int *E_size);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct adjacency matrix of graph.
///
/// @param[in]   E       the edge list; pointer.
///
/// @param[in]   E_size  the path to the object file.
///
/// @param[out]  nnz     number of nonzero elements in the matrix.
///
/// @param[out]  csrRowPtrA     CSR row pointer; pointer.
///
/// @param[out]  csrColIndA     CSR column index; pointer.
///
/// @param[out]  csrValA  nonzero values of the matrix; pointer.
///
/// @param[out]  n        size of the matrix;
///
/// @note  The output arrays are allocated by this routine (using new).
///
int GraphAdjacency(int *E, int E_size,
	int *nnz, int **csrRowPtrA,
	int **csrColIndA, double **csrValA, int *n);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct adjacency matrix of graph.
///
/// @param[in/out]  nnz     number of nonzero elements in the matrix.
///
/// @param[in/out]  csrRowPtrA     CSR row pointer; pointer.
///
/// @param[in/out]  csrColIndA     CSR column index; pointer.
///
/// @param[in/out]  csrValA  nonzero values of the matrix; pointer.
///
/// @param[in/out]  n        size of the matrix;
///
/// @note  The output arrays are allocated by this routine (using new).
///
void GraphLaplacian(int *nnz, int *csrRowPtrA,
  int *csrColIndA, double *csrValA, int n);
#endif  // SCSC_SGP_HPP