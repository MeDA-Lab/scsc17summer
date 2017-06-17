////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    read_object.cpp
/// @brief   The implementation of object reading.
///
/// @author  Yuhisang Mike Tsai
///
#include <iostream>
#include <fstream>
#include <harmonic.hpp>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @todo  To be implemented!
///
void readObject(
    const char *filename,
    int *ptr_nv,
    int *ptr_nf,
    double **V,
    double **C,
    int **F
) {
  ifstream fin(filename, ifstream::in);
  if ( fin.good() == 0 ) {
    cerr<<"Open File "<<filename<<" Error\n";
    exit(1);
  }
  // Read the vertex
  string tail, head;
  if (fin.peek()=='#'){
    // # nv vertex
    fin>>head>>*ptr_nv>>tail;
    // cout<<head<<" "<<*ptr_nv<<" "<<tail<<endl;
    while (fin.get()!='\n');
  }
  int nv=*ptr_nv;
  
  *V = new double [nv * 3];
  *C = new double [nv * 3];
  double *VV=*V, *CC=*C;
  // v x y z (R G B)
  
  for (int i=0; i<nv; i++){
    if (fin.peek()!='v'){
      cerr<<"Read vertex error\n";
      printf("%c",fin.peek());
      exit(1);
    }
    fin>>head>>VV[i]>>VV[nv+i]>>VV[2*nv+i];
    if (fin.peek()!='\n'){
      // Obeject has color information
      fin>>CC[i]>>CC[nv+i]>>CC[2*nv+i];
    }
    else{
      CC[i]        = -1;
      CC[nv+i]     = -1;
      CC[2*nv+i]  = -1;
    }
    // cout<<head<<" "<<V[i]<<" "<<V[nv+i]<<" "<<V[nv+nv+i];
    // cout<<" "<<C[i]<<" "<<C[nv+i]<<" "<<C[nv+nv+i]<<endl;
    while (fin.get()!='\n');
  }

  // Read the face
  if (fin.peek()=='#'){
    // # nf faces
    fin>>head>>*ptr_nf>>tail;
    // cout<<head<<" "<<*ptr_nf<<" "<<tail<<endl;
    while (fin.get()!='\n');
  }
  int nf = *ptr_nf;
  
  *F = new int [ nf * 3 ];
  int *FF=*F;
  for (int i=0; i<nf; i++){
    if (fin.peek()!='f'){
      cerr<<"Read Face error\n";
      printf("%c",fin.peek());
      exit(1);
    }
    fin>>head>>FF[i]>>FF[nf+i]>>FF[2*nf+i];
    // cout<<head<<" "<<F[i]<<" "<<F[nv+i]<<" "<<F[nv+nv+i]<<endl;
    while (fin.get()!='\n');
  }
  while (fin.get()=='\n');
  if ( fin.eof() != 1) {
    cerr<<"Notice: something are not load\n";
  }
  fin.close();
}
