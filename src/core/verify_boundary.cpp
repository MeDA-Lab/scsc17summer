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
  long long int nvl=nv;
  int *Gvv = new int [nvl*nvl];
  for (int i=0; i<nvl*nvl; i++){
    Gvv[i] = 0;
  }
  int p[3];
  for (int i=0; i<nf; i++){
    p[0]=F[i];
    p[1]=F[nf+i];
    p[2]=F[2*nf+i];
    Gvv[(p[1]-1)*nvl+(p[0]-1)]++; // p0->p1
    Gvv[(p[2]-1)*nvl+(p[1]-1)]++; // p1->p2
    Gvv[(p[0]-1)*nvl+(p[2]-1)]++; // p2->p0
  }
  int nb=0, bd_vertex=nv+1, bd_ind=nv+1;
  int *Bi= new int [nvl], *Bj = new int [nvl];
  for (int j=0; j<nv; j++){
    for (int i=0; i<nv; i++){
      // (i,j)
      if (Gvv[j*nvl+i]-Gvv[i*nvl+j]==1){
        nb++;
        Bi[nb-1]=i+1;
        Bj[nb-1]=j+1;
        if (i+1<bd_vertex){
          bd_vertex = i+1;
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
    (*idx_b)[i]=VB[i];
  }
  delete [] Bi;
  delete [] Bj;
  delete [] Gvv;
  return;
}
