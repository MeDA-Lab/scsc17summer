////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    construct_laplacian.cpp
/// @brief   The implementation of Laplacian construction.
///
/// @author  Unknown
///

#include <harmonic.hpp>
#include <iostream>

using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @todo  To be implemented!
///
// double* Cross(const double *x, const double *y) {
//   double z[3];
//   z[0] = x[1]*y[2] - x[2]*y[1];
//   z[1] = x[2]*y[0] - x[0]*y[2];
//   z[2] = x[0]*y[1] - x[1]*y[0];
//   return z;
// }

double Sum(const int n, const double *x, const int incx) {
  double sum = 0;
  for (int i = 0; i < n; ++i)
  {
    sum += x[i*incx];
  }
  return sum;
}

void constructLaplacian(
    const Method method,
    const int nv,
    const int nf,
    const double *V,
    const double *C,
    const int *F,
    double *L
) {
  std::cout<<"QdddQf\n";
  for (int i=0; i<nv*nv; i++)
  {
    L[i]=0;
  }
  if (method == Method::SIMPLE) //Simple Laplacian Matrix
  {
    for (int i = 0; i < nf; ++i)
    {
      int F_x = F[i]-1;
      int F_y = F[nf+i]-1;
      int F_z = F[2*nf+i]-1;
      L[F_x*nv+F_y] = -1;
      L[F_y*nv+F_z] = -1;
      L[F_z*nv+F_x] = -1;
      L[F_y*nv+F_x] = -1;
      L[F_z*nv+F_y] = -1;
      L[F_x*nv+F_z] = -1;
    }
    for (int i = 0; i<nv; i++){
      L[i*nv+i]=-1*Sum(nv, L+i*nv, 1);
    }
  }else if (method == Method::COMPLEX) // Cotengent Laplacian Matrix
  {
    // double *v_ki = new double [3];
    // double *v_kj = new double [3];
    // double *v_ij = new double [3];
    // double *cross = new double [3];
    // double *tmp1 = new double [3];
    // double *tmp2 = new double [3];
    // for (int i = 0; i < nf; ++i)
    // {
    //   int F_x = F[i];
    //   int F_y = F[nf+i];
    //   int F_z = F[2*nf+i];

    //   v_ki[0] = V[F_x] - V[F_z];
    //   v_ki[1] = V[nv+F_x] - V[nv+F_z];
    //   v_ki[2] = V[2*nv+F_x] - V[2*nv+F_z];
    //   v_kj[0] = V[F_y] - V[F_z];
    //   v_kj[1] = V[nv+F_y] - V[nv+F_z];
    //   v_kj[2] = V[2*nv+F_y] - V[2*nv+F_z];
    //   v_ij[0] = V[F_y] - V[F_x];
    //   v_ij[1] = V[nv+F_y] - V[nv+F_x];
    //   v_ij[2] = V[2*nv+F_y] - V[2*nv+F_x];

    //   corss = Cross(v_ki, v_kj);
    //   for (int i = 0; i < 3; ++i)
    //   {
    //     tmp1[i] = v_ki[i]*v_kj[i];
    //     tmp2[i] = pow(cross[i],2);
    //   }
    //   L[F_x*nv+F_y] = -0.5*Sum(tmp1,3)/sqrt(Sum(tmp2));
    //   L[F_x*nv+F_x] -= L[F_x*nv+F_y];
    //   L[F_y*nv+F_x] = -0.5*Sum(tmp1,3)/sqrt(Sum(tmp2));
    //   L[F_y*nv+F_y] -= L[F_y*nv+F_x];

    //   double m_v_ij[3];
    //   for (int i = 0; i < 3; ++i)
    //   {
    //     m_v_ij[i] = -v_ij[i];
    //   }
    //   corss = Cross(m_v_ij, v_ki);
    //   for (int i = 0; i < 3; ++i)
    //   {
    //     tmp1[i] = m_v_ij[i]*v_ki[i];
    //     tmp2[i] = pow(cross[i],2);
    //   }
    //   L[F_y*nv+F_z] = -0.5*Sum(tmp1,3)/sqrt(Sum(tmp2));
    //   L[F_y*nv+F_y] -= L[F_y*nv+F_z];
    //   L[F_z*nv+F_x] = -0.5*Sum(tmp1,3)/sqrt(Sum(tmp2));
    //   L[F_z*nv+F_z] -= L[F_z*nv+F_x];
      
    //   corss = Cross(v_kj, v_ij);
    //   for (int i = 0; i < 3; ++i)
    //   {
    //     tmp1[i] = v_kj[i]*v_ij[i];
    //     tmp2[i] = pow(cross[i],2);
    //   }
    //   L[F_z*nv+F_y] = -0.5*Sum(tmp1,3)/sqrt(Sum(tmp2));
    //   L[F_z*nv+F_z] -= L[F_z*nv+F_y];
    //   L[F_x*nv+F_z] = -0.5*Sum(tmp1,3)/sqrt(Sum(tmp2));
    //   L[F_x*nv+F_x] -= L[F_x*nv+F_z];
    // }
  }
}
