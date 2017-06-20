////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    solve_harmonic_magma.cpp
/// @brief   The implementation of harmonic problem solving using MAGMA.
///
/// @author  Yuhsiang Mike Tsai
///

#include <harmonic.hpp>
#include <iostream>
#include "magma_v2.h"
#include "magmasparse.h"
#include "magma_lapack.h"
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @todo  To be implemented!
///
void solveHarmonic(
    const int nv,
    const int nb,
    double *L,
    double *U
) {
  // Liiui=Libub
  int64_t nvl=nv;
  magma_init();
  magma_queue_t queue;
  magma_queue_create(0, &queue);
  double *dL = NULL, *dU = NULL;
  magma_malloc((void **)&dL, nvl*nvl*sizeof(double));
  magma_malloc((void **)&dU, nvl*2*sizeof(double));
  magma_setvector(nvl*nvl, sizeof(double), L, 1, dL, 1, queue);
  magma_setvector(nvl*2, sizeof(double), U, 1, dU, 1, queue);
  magmablas_dgemm(MagmaNoTrans, MagmaNoTrans, nvl-nb, 2, nb, -1, dL+nb, nvl, dU, nvl, 0, dU+nb, nvl, queue);
  //
  int *ipiv=new int [nv-nb], info = 0;
  magma_dgesv_gpu(nvl-nb, 2, dL+nvl*nb+nb, nv, ipiv, dU+nb, nvl, &info);
  if (info != 0){
    cerr<<info<<" Magma Solve Error\n";
  }
  magma_getvector(nv*2, sizeof(double), dU, 1, U, 1, queue);
  magma_free(dL);
  magma_free(dU);
  magma_finalize();
}
