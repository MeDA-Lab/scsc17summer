////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    construct_laplacian_sparse.cpp
/// @brief   The implementation of Laplacian construction.
///
/// @author  Yen Chen Chen, Yuhsiang Mike Tsai
///

#include <harmonic.hpp>
#include <iostream>
#include <cmath>
#include <tuple>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @todo  To be implemented!
///
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
int compareTuple(const void *a, const void *b){
  tuple<int, int, double> *A=(tuple<int, int, double>*) a;
  tuple<int, int, double> *B=(tuple<int, int, double>*) b;
  if ( get<0>(*A) < get<0>(*B) ) {
    return -1;
  }
  else if ( get<0>(*A) > get<0>(*B) ) {
    return 1;
  }
  else {
    if ( get<1>(*A) < get<1>(*B) ){
      return -1;
    }
    else if ( get<1>(*A) == get<1>(*B) ){
      return 0;
    }
    else {
      return 1;
    }
  }
}
void coo2csr(
  const int coo_num, tuple<int, int, double> *coo,
  const int csr_row_num, double ** csr_a, int **csr_row, int **csr_col, int *nnz){

  qsort(coo, coo_num, sizeof(tuple<int,int,double>), compareTuple);
  *csr_row = new int [csr_row_num+1];
  int temp_nnz=1;
  for (int i=1; i<coo_num; i++) {
    if (get<0>(coo[i])!=get<0>(coo[i-1]) || get<1>(coo[i])!=get<1>(coo[i-1])){
      temp_nnz++;
    }
  }
  *nnz=temp_nnz;
  cout<<"temp:"<<temp_nnz<<"\n";
  *csr_a = new double [temp_nnz];
  *csr_col = new int [temp_nnz];
  double *A=*csr_a;
  int *row=*csr_row, *col=*csr_col;
  for (int i=0; i<csr_row_num+1; i++){
    row[i]=0;
  }
  int index=0;
  for (int i=0; i<coo_num; i++){
    if (i==0){
      A[index]=get<2>(coo[i]);
      col[index]=get<1>(coo[i]);
      cout<<col[0]<<"\n";
      index++;
    }
    else if (get<0>(coo[i])==get<0>(coo[i-1]) && get<1>(coo[i])==get<1>(coo[i-1])){
      A[index-1]+=get<2>(coo[i]);
    }
    else if (get<0>(coo[i])!=get<0>(coo[i-1])){
      for (int j=get<0>(coo[i-1]); j<get<0>(coo[i]); j++){
        row[j+1]=index;
      }
      A[index]=get<2>(coo[i]);
      col[index]=get<1>(coo[i]);
      index++;
    }
    else {
      A[index]=get<2>(coo[i]);
      col[index]=get<1>(coo[i]);
      index++;
    }
  }
  for (int i=get<0>(coo[coo_num-1])+1; i<=csr_row_num; i++ ){
    row[i]=index;
  }
  // for (int i=0; i<csr_row_num; i++){
  //   cout<<row[i]<<"->"<<row[i+1]<<"\n";
  //   for (int j=row[i]; j<row[i+1]; j++){
      
  //     cout<<i<<" "<<col[j]<<" "<<A[j]<<"\n";
  //   }
  // }
  if (index!=temp_nnz){
    cerr<<"coo2csr Error\n";
    exit(1);
  }
}

void constructLaplacianSparse( 
  const Method method, const int nv, const int nb, const int nf, const double *V, const int *F,
  double **ptr_Lii_val, int **ptr_Lii_row, int **ptr_Lii_col, int *ptr_Lii_nnz,
  double **ptr_Lib_val, int **ptr_Lib_row, int **ptr_Lib_col, int *ptr_Lib_nnz
) {
  int Lii_nnz=nv-nb, Lib_nnz=0, F_x=0, F_y=0, F_z=0;
  for (int i=0; i<nf; i++) {
    F_x = F[i]-1;
    F_y = F[nf+i]-1;
    F_z = F[2*nf+i]-1;
    if (F_x >= nb && F_y >= nb) Lii_nnz++;
    if (F_y >= nb && F_z >= nb) Lii_nnz++;
    if (F_z >= nb && F_x >= nb) Lii_nnz++;
    if (F_x >= nb && F_y < nb)  Lib_nnz++;
    if (F_y >= nb && F_z < nb)  Lib_nnz++;
    if (F_z >= nb && F_x < nb)  Lib_nnz++;
    if (method==Method::COMPLEX) {
      if (F_x >= nb && F_y >= nb) Lii_nnz++;
      if (F_y >= nb && F_z >= nb) Lii_nnz++;
      if (F_z >= nb && F_x >= nb) Lii_nnz++;
      if (F_x < nb && F_y >= nb) Lib_nnz++;
      if (F_y < nb && F_z >= nb) Lib_nnz++;
      if (F_z < nb && F_x >= nb) Lib_nnz++;
    }
    
  }
  tuple<int, int, double> *Lib= new tuple<int, int , double> [Lib_nnz];
  tuple<int, int, double> *Lii= new tuple<int, int , double> [Lii_nnz];
  for (int i=0; i<nv-nb; i++) {
    get<2>(Lii[i])=0;
    get<1>(Lii[i])=i;
    get<0>(Lii[i])=i;
  }
  int index_Lii=nv-nb, index_Lib=0;
  int row=0, col=0;
  if (method == Method::SIMPLE) //Simple Laplacian Matrix
  {
    for (int i = 0; i < nf; ++i)
    {
      for (int k=0; k<3; k++) {
        row =F[k*nf+i]-1;
        col =F[((k+1)%3)*nf+i]-1;
        if (row >= nb && col>= nb) {
          get<2>(Lii[index_Lii])=-1;
          get<1>(Lii[index_Lii])=col-nb;
          get<0>(Lii[index_Lii])=row-nb;
          get<2>(Lii[row-nb])++;
          index_Lii++;
        }
        else if (row>=nb && col< nb) {
          get<2>(Lib[index_Lib])=-1;
          get<1>(Lib[index_Lib])=col;
          get<0>(Lib[index_Lib])=row-nb;
          get<2>(Lii[row-nb])++;
          index_Lib++;
        }
      }
    }
    if (index_Lib!=Lib_nnz || index_Lii != Lii_nnz) {
      cerr<<"SIMPLE: nnz, index  Error\n";
      exit(1);
    }
    
  }else if (method == Method::COMPLEX) // Cotengent Laplacian Matrix
  {

    index_Lib=0;
    index_Lii=nv-nb;
    for (int i = 0; i < nf; ++i)
    {
      for (int k=0; k<3; k++){
        
        int row=F[k*nf+i]-1;
        int col=F[(k+1)%3*nf+i]-1;
        int mid=F[(k+2)%3*nf+i]-1;
        // double v[3]={V[F]-V[col], V[nv+row]-V[nv+col], V[2*nv+row]-V[2*nv+col]};
        double v[3]={V[row]-V[mid], V[nv+row]-V[nv+mid], V[2*nv+row]-V[2*nv+mid]};
        double b[3]={V[col]-V[mid], V[nv+col]-V[nv+mid], V[2*nv+col]-V[2*nv+mid]};
        if (row >= nb && col >= nb) {
          // Lii
          get<0>(Lii[index_Lii])=row-nb;
          get<1>(Lii[index_Lii])=col-nb;
          get<2>(Lii[index_Lii])=-0.5*Dot(3, v, b)/CrossNorm(v, b);
          get<2>(Lii[row-nb])-=get<2>(Lii[index_Lii]);
          index_Lii++;
          //swap
          get<0>(Lii[index_Lii])=col-nb;
          get<1>(Lii[index_Lii])=row-nb;
          get<2>(Lii[index_Lii])=-0.5*Dot(3, v, b)/CrossNorm(v, b);
          get<2>(Lii[col-nb])-=get<2>(Lii[index_Lii]);
          index_Lii++;
        }
        else if (row >= nb && col < nb) {
          // Lib
          get<0>(Lib[index_Lib])=row-nb;
          get<1>(Lib[index_Lib])=col;
          get<2>(Lib[index_Lib])=-0.5*Dot(3, v, b)/CrossNorm(v, b);
          get<2>(Lii[row-nb])-=get<2>(Lib[index_Lib]);
          index_Lib++;
        }
        else if (row < nb && col >= nb) {
          // Lbi swap col, row 
          get<0>(Lib[index_Lib])=col-nb;
          get<1>(Lib[index_Lib])=row;
          get<2>(Lib[index_Lib])=-0.5*Dot(3, v, b)/CrossNorm(v, b);
          get<2>(Lii[col-nb])-=get<2>(Lib[index_Lib]);
          index_Lib++;
        }
      }
    }
    if (index_Lib != Lib_nnz || index_Lii != Lii_nnz) {
      cerr<<"Complex: index, nnz Error\n";
      cerr<<index_Lib<<" "<<Lib_nnz<<"\n";
      exit(1);
    }
    
  }
  coo2csr(Lib_nnz, Lib, nv-nb, ptr_Lib_val, ptr_Lib_row, ptr_Lib_col, ptr_Lib_nnz);
  coo2csr(Lii_nnz, Lii, nv-nb, ptr_Lii_val, ptr_Lii_row, ptr_Lii_col, ptr_Lii_nnz);
  delete [] Lii;
  delete [] Lib;
}
