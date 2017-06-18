////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    verify_boundary.cpp
/// @brief   The implementation of boundary verification.
///
/// @author  Yuhsiang Mike Tsai
///

#include <harmonic.hpp>
#include <vector>
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @todo  To be implemented!
///


int find_index(int *A, int n, int value){
  int i;
  for (i=0; i<n; i++){
    if (A[i]==value){
      break;
    }
  }
  return i;
}

void verifyBoundary(
    const int nv,
    const int nf,
    const int *F,
    int *ptr_nb,
    int **idx_b
) {
  static_cast<void>(nv);
  static_cast<void>(nf);
  static_cast<void>(F);
  static_cast<void>(ptr_nb);
  static_cast<void>(idx_b);
  int *Gvv = new int [nv*nv];
  memset(G, 0, nv*nv*siezof(int));
  int p[3];
  for (int i=0; i<nf; i++){
    p[0]=F[i];
    p[1]=F[nf+i];
    p[2]=F[2*nf+i];
    Gvv[(p[1]-1)*nv+(p[0]-1)]++; // p0->p1
    Gvv[(p[2]-1)*nv+(p[1]-1)]++; // p1->p2
    Gvv[(p[0]-1)*nv+(p[2]-1)]++; // p2->p0
  }
  // int *Gb = new int [nv*nv];
  int nb=0, bd_vertex=nv+1, bd_ind;
  int *Bi= new int [nb], *Bj = new int [nb];
  for (int j=0; j<nv; j++){
    for (int i=0; i<nv; i++){
      // (i,j)
      if (Gvv[j*nv+i]-Gvv[i*nv+j]==1){
        nb++;
        Bi[nb-1]=i;
        Bj[nb-1]=j;
        if (i<bd_vertex){
          bd_vertex = i;
          bd_ind = nb-1;
        }
      }
    }
  }
  vector<int> VB;
  for (int i=0; i<nb; i++){
    VB.push_back(bd_vertex);
    bd_ind = find_index (Bi, nb, Bj[bd_ind]);
    bd_vertex = Bi[bd_ind];
    if (bd_vertex == VB[0]){
      break;
    }
  }
  *ptr_nb = VB.size();
  *idx_b = new int [*ptr_nb];
  for (int i=0; i<*ptr_nb; i++){
    *idx_b[i]=VB[i];
  }
  return;
}
