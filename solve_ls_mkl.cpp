////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    solve_ls_mkl.cpp
/// @brief   Solve the linear system
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <mkl.h>

void SolveLS(int n, double* A, int lda, int nrhs, double *rhs, int ldr, double *x, int ldx) {
  int ipiv[n];
  LAPACKE_dgesv(LAPACK_COL_MAJOR, n, nrhs, A, lda, ipiv, x, ldx);
}
