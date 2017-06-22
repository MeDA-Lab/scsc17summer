////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    solve_harmonic_sparse_mkl.cpp
/// @brief   The implementation of harmonic problem solving using MKL.
///
/// @author  Yuhsiang Mike Tsai
///

#include <harmonic.hpp>
#include <mkl.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @todo  To be implemented!
///
void solveHarmonicSparse( 
  const int nv, const int nb,
  double *Lii_val, int *Lii_row, int *Lii_col, const int Lii_nnz,
  double *Lib_val, int *Lib_row, int *Lib_col, const int Lib_nnz, double *U 
) {
  int ni=nv-nb;
  int ncols=2;
  double alpha=1.0, beta=0.0;
  char trans='N';
  char matdescra[6]={'G', 'L', 'N', 'C', ' ',' '};
  mkl_dcsrmm(&trans , &ni ,  &ncols , &nb , &alpha , matdescra , Lib_val , Lib_col , Lib_row, Lib_row+1, 
             U , &nv , &beta , U+nb , &nv );
}
