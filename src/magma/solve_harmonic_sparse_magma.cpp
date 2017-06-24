////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    solve_harmonic_sparse_magma.cpp
/// @brief   The implementation of harmonic problem solving using MKL.
///
/// @author  Yuhsiang Mike Tsai
///

#include <harmonic.hpp>
#include <iostream>
#include "magma_v2.h"
#include "magmasparse.h"
#include "magma_lapack.h"
using namespace std;

void solveHarmonicSparse(
  const int nv, const int nb,
  const double *Lii_val, const int *Lii_row, const int *Lii_col,
  const double *Lib_val, const int *Lib_row, const int *Lib_col,
  double *U
) {
  magma_init();
  magma_queue_t queue;
  magma_queue_create(0, &queue);
  magma_d_matrix Lii, Lib, dLii, dLib;
  double *dL = NULL, *dU = NULL;
  magma_malloc((void **)&dU, nv*2*sizeof(double));
  magma_setvector(nv*2, sizeof(double), U, 1, dU, 1, queue);
  int ni=nv-nb;
  magma_dcsrset(ni, nb, Lib_row, Lib_col, Lib_val, &Lib, queue);
  magma_dcsrset(ni, ni, Lii_row, Lii_col, Lii_val, &Lii, queue);
  magma_d_mtransfer(Lii, &dLii, Magma_CPU, Magma_DEV, queue);
  magma_d_mtransfer(Lib, &dLib, Magma_CPU, Magma_DEV, queue);
  
  magma_finalize();

}
