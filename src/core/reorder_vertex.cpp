////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    reorder_vertex.cpp
/// @brief   The implementation of vertex reordering.
///
/// @author  Yuhsiang Mike Tsai
///

#include <harmonic.hpp>
#include <iostream>
#include <algorithm>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @todo  To be implemented!
///
void reorderVertex(
    const int nv,
    const int nb,
    const int *idx_b,
    double *V,
    double *C
) {
  double *V_cp = new double [nv*3], *C_cp = new double [nv*3];
  bool *used = new bool [nv];
  for (int i=0; i<nv; i++){
    used[i]=false;
  }
  copy(V, V+nv*3, V_cp);
  copy(C, C+nv*3, C_cp);
  for (int i=0; i<nb; i++){
    V[i]=V_cp[idx_b[i]-1];
    V[nv+i]=V_cp[nv+idx_b[i]-1];
    V[2*nv+i]=V_cp[2*nv+idx_b[i]-1];
    C[i]=C_cp[idx_b[i]-1];
    C[nv+i]=C_cp[nv+idx_b[i]-1];
    C[2*nv+i]=C_cp[2*nv+idx_b[i]-1];
    used[idx_b[i]-1]=true;
  }
  int index=nb;
  for (int i=0; i<nv; i++){
    if (!used[i]){
      V[index]=V_cp[i];
      V[nv+index]=V_cp[nv+i];
      V[2*nv+index]=V_cp[2*nv+i];
      C[index]=C_cp[i];
      C[nv+index]=C_cp[nv+i];
      C[2*nv+index]=C_cp[2*nv+i];
      index++;
    }
  }
  if (index!=nv){
    cerr<<"Reorder Error\n";
  }
  delete [] V_cp;
  delete [] C_cp;
  delete [] used;
  return;
}
