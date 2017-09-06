////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    construct_laplacian.cpp
/// @brief   The implementation of Laplacian construction.
///
/// @author  Yen Chen Chen
/// @author  Yuhsiang Mike Tsai
///

#include <harmonic.hpp>
#include <iostream>
#include <cmath>
#include <cassert>
#include <numeric>
#include <mkl_spblas.h>
using namespace std;

double CrossNorm(const double *x, const double *y) {
  double z[3];
  z[0] = x[1]*y[2] - x[2]*y[1];
  z[1] = x[2]*y[0] - x[0]*y[2];
  z[2] = x[0]*y[1] - x[1]*y[0];
  return sqrt(z[0]*z[0]+z[1]*z[1]+z[2]*z[2]);
}

double Sum(const int n, const double *x, const int incx) {
  double sum = 0;
  for (int i = 0; i < n; ++i)
  {
    sum += x[i*incx];
  }
  return sum;
}

double Dot(const int n, const double *x, const double *y) {
  double ans=0;
  for (int i=0; i<n; i++){
    ans+= x[i]*y[i];
  }
  return ans;
}
void constructLaplacian(
    const Method method,
    const int nv,
    const int nf,
    const double *V,
    const int *F,
    double *L
) {
  for (int i=0; i<nv*nv; i++)
  {
    L[i]=0;
  }
  if (method == Method::KIRCHHOFF) // Kirchhoff Laplacian Matrix
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
  }else if (method == Method::COTANGENT) // Cotangent Laplacian Matrix
  {
    double *v_ki = new double [3];
    double *v_kj = new double [3];
    double *v_ij = new double [3];
    for (int i = 0; i < nf; ++i)
    {
      int F_x = F[i]-1;
      int F_y = F[nf+i]-1;
      int F_z = F[2*nf+i]-1;

      v_ki[0] = V[F_x] - V[F_z];
      v_ki[1] = V[nv+F_x] - V[nv+F_z];
      v_ki[2] = V[2*nv+F_x] - V[2*nv+F_z];
      v_kj[0] = V[F_y] - V[F_z];
      v_kj[1] = V[nv+F_y] - V[nv+F_z];
      v_kj[2] = V[2*nv+F_y] - V[2*nv+F_z];
      v_ij[0] = V[F_y] - V[F_x];
      v_ij[1] = V[nv+F_y] - V[nv+F_x];
      v_ij[2] = V[2*nv+F_y] - V[2*nv+F_x];
      L[F_x*nv+F_y] += -0.5*Dot(3, v_ki, v_kj)/CrossNorm(v_ki, v_kj);
      L[F_y*nv+F_x] = L[F_x*nv+F_y];
      L[F_y*nv+F_z] += 0.5*Dot(3, v_ij, v_ki)/CrossNorm(v_ij, v_ki);
      L[F_z*nv+F_y] = L[F_y*nv+F_z];
      L[F_z*nv+F_x] += -0.5*Dot(3, v_kj, v_ij)/CrossNorm(v_kj, v_ij);
      L[F_x*nv+F_z] = L[F_z*nv+F_x];
    }
    for (int i = 0; i<nv; i++){
      L[i*nv+i]=-1*Sum(nv, L+i*nv, 1);
    }
  }
}

void GraphLaplacian(int nnz, int *cooRowPtrA,
  int *cooColIndA, double *cooValA, int n){
  double *rowsum, tmp=0;
  int *sumInd, k=0;
  sparse_matrix_t A, D;
  sparse_index_base_t indexing = SPARSE_INDEX_BASE_ZERO;
  sparse_operation_t op = SPARSE_OPERATION_NON_TRANSPOSE;
  sparse_status_t stat;

  sumInd = new int[n];
  rowsum = new double[n];

  cout << "test point 1" << endl;

  for (int i = 0; i < n; i++)
  {
    rowsum[i] = 0;
  }

  for (int i = 0; i < nnz; i++)
  {
    if (cooRowPtrA[i]!=cooRowPtrA[i-1])
    {
      rowsum[k] = tmp;
      tmp = 0;
      k++;
      //cout << "sum[" << k << "] = " << sum[k] << endl;
    }
    tmp = tmp + cooValA[i];
  }

  cout << "test point 2" << endl;

  for (int i = 0; i < n; i++)
  {
    sumInd[i] = i;
  }

  cout << "test point 3" << endl;
  delete rowsum;
  delete sumInd;
/*
  stat = mkl_sparse_d_create_coo(&A, indexing, n, n, cooRowPtrA, cooRowPtrA+1, csrColIndA, csrValA);
  assert( stat == SPARSE_STATUS_SUCCESS );
  stat = mkl_sparse_d_create_coo(&D, indexing, n, n, n, sumInd, sumInd, sum);
  assert( stat == SPARSE_STATUS_SUCCESS );
  stat = mkl_sparse_d_add(op, A, -1.0, D, &A);
  assert( stat == SPARSE_STATUS_SUCCESS );*/
}