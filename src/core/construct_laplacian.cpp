////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    construct_laplacian.cpp
/// @brief   The implementation of Laplacian construction.
///
/// @author  Unknown
///

#include <harmonic.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @todo  To be implemented!
///
void constructLaplacian(
    const Method method,
    const int nv,
    const int nf,
    const double *V,
    const double *C,
    const int *F,
    double *L
) {
  double *L_d = new double [nv];
  
  if (method == 0) //Simple Laplacian Matrix
  {
    for (int i = 0; i < nf; ++i)
    {
      L[i*nv+i*2] = 1;
      L[i*nv+i] += 1;
      L[i*2*nv+i*3] = 1;
      L[i*2*nv+i*2] += 1;
      L[i*3*nv+i] = 1;
      L[i*3*nv+i*3] += 1;
      L[i*2*nv+i] = 1;
      L[i*2*nv+i*2] += 1;
      L[i*3*nv+i*2] = 1;
      L[i*3*nv+i*3] += 1;
      L[i*nv+i*3] = 1;
      L[i*nv+i] += 1;
    }
  }else if (method == 1) // Cotengent Laplacian Matrix
  {
    /* code */
  }
}
