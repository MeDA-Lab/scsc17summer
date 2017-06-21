////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    solve_harmonic_mkl_getrfi.cpp
/// @brief   The implementation of harmonic problem solving using MKL.
///
/// @author  Unknown
///

#include <harmonic.hpp>
#include <mkl.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @todo  To be implemented!
///
void solveHarmonic(
    const int nv,
    const int nb,
    double *L,
    double *U
) {
  const int ni = nv-nb;

  const double *Lib = L+nb;
  double       *Lii = L+nb+nb*nv;
  const double *Ub  = U;
  double       *Ui  = U+nb;

  int *ipiv = new int[ni];

  // ====================================================================================================================== //
  // Solve Lii Ui = Lib Ub

  // Tmp [in Ui] := Lib * Ub
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, ni, 2, nb, 1.0, Lib, nv, Ub, nv, 0.0, Ui, nv);

  // Solve Lii Ui = Tmp [in Ui]
  int info;
  info = LAPACKE_dgetrf(LAPACK_COL_MAJOR, ni, ni, Lii, nv, ipiv); assert(info == 0);
  info = LAPACKE_dgetrs(LAPACK_COL_MAJOR, CblasNoTrans, ni, 2, Lii, nv, ipiv, Ui, nv); assert(info == 0);
}