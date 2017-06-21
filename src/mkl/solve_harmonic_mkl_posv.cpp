////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    solve_harmonic_mkl_posv.cpp
/// @brief   The implementation of harmonic problem solving using MKL.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
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

  // ====================================================================================================================== //
  // Solve Lii Ui = Lib Ub

  // Tmp [in Ui] := Lib * Ub
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, ni, 2, nb, 1.0, Lib, nv, Ub, nv, 0.0, Ui, nv);

  // Solve Lii Ui = Tmp [in Ui]
  int info = LAPACKE_dposv(LAPACK_COL_MAJOR, 'U', ni, 2, Lii, nv, Ui, nv);
  assert(info == 0);
}
