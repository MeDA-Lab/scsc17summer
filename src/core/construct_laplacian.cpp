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
  if (method == 0) //Simple Laplacian Matrix
  {
    for (int i = 0; i < nf; ++i)
    {
      double F_x = F[i];
      double F_y = F[nf+i];
      double F_z = F[2*nf+i];
      L[F_x*nv+F_y] = 1;
      L[F_x*nv+F_x] += L[F_x*nv+F_y];
      L[F_y*nv+F_z] = 1;
      L[F_y*nv+F_y] += L[F_y*nv+F_z];
      L[F_z*nv+F_x] = 1;
      L[F_z*nv+F_z] += L[F_z*nv+F_x];
      L[F_y*nv+F_x] = 1;
      L[F_y*nv+F_y] += L[F_y*nv+F_x];
      L[F_z*nv+F_y] = 1;
      L[F_z*nv+F_z] += L[F_z*nv+F_y];
      L[F_x*nv+F_z] = 1;
      L[F_x*nv+F_x] += L[F_x*nv+F_z];
    }
  }else if (method == 1) // Cotengent Laplacian Matrix
  {
    double *v_ki = new double [3]
  }
}
