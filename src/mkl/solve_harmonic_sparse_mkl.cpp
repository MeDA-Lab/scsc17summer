////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    solve_harmonic_sparse_mkl.cpp
/// @brief   The implementation of harmonic problem solving using MKL.
///
/// @author  Yuhsiang Mike Tsai
///

#include <harmonic.hpp>
#include <mkl.h>
#include <iostream>
#include <fstream>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @todo  To be implemented!
///
void solveHarmonicSparse( 
  const int nv, const int nb,
  const double *Lii_val, const int *Lii_row, const int *Lii_col, const int Lii_nnz,
  const double *Lib_val, const int *Lib_row, const int *Lib_col, const int Lib_nnz, double *U 
) {
//   int ni=nv-nb;
//   int ncols=2;
//   double alpha=1.0, beta=0.0;
//   char trans='N';
//   char matdescra[6]={'G', 'L', 'N', 'C', ' ',' '};
//   double *b=new double [ni*2], *x=new double [ni*2];
//   cout<<"@@\n";
// //   for (int i=0; i<ni; i++){
// //     for (int j=Lib_row[i]; j<Lib_row[i+1]; j++){
// //       cout<<i<<" "<<Lib_col[j]<<" "<<Lib_val[j]<<"\n";
// //     }
// //   }
//   cout<<"nv"<<nv<<"nb"<<nb<<"\n";
// //   mkl_dcsrmm(&trans , &ni ,  &ncols , &nb , &alpha , matdescra , Lib_val , Lib_col , Lib_row, Lib_row+1, 
// //              U , &nv , &beta , b , &ni);
//   ofstream fout("U.txt", ofstream::out);
//   for (int i=0; i<nb; i++) {
//     fout<<U[i]<<" "<<U[nv+i]<<"\n";
//   }
//   // fout.close();
//   mkl_cspblas_dcsrgemv (&trans , &ni , Lib_val , Lib_row , Lib_col , U , b );
//   mkl_cspblas_dcsrgemv (&trans , &ni , Lib_val , Lib_row , Lib_col , U+nv , b+ni );
//   // fout.open("b.txt", ofstream::out);
//   for (int i=0; i<ni; i++) {
//     fout<<b[i]<<" "<<b[ni+i]<<"\n";
//   }
  
//   cout<<"Q\n";
//   // pardiso x needs to be different from x;
//   int iparm[64], mtype = 11;
//   int maxfct, mnum, phase, error, msglvl;
//   void *pt[64];
//   for (int i=0; i<64; i++){
//     iparm[i]=0;
//   }
//   iparm[0] = 1;         /* No solver default */
//   iparm[1] = 3;         /* Fill-in reordering from METIS */
//   iparm[3] = 0;         /* No iterative-direct algorithm */
//   iparm[4] = 0;         /* No user fill-in reducing permutation */
//   iparm[5] = 0;         /* Write solution into x */
//   iparm[6] = 0;         /* Not in use */
//   iparm[7] = 5;         /* Max numbers of iterative refinement steps */
//   iparm[8] = 0;         /* Not in use */
//   iparm[9] = 13;        /* Perturb the pivot elements with 1E-13 */
//   iparm[10] = 1;        /* Use nonsymmetric permutation and scaling MPS */
//   iparm[11] = 0;        /* Conjugate transposed/transpose solve */
//   iparm[12] = 1;        /* Maximum weighted matching algorithm is switched-on (default for non-symmetric) */
//   iparm[13] = 0;        /* Output: Number of perturbed pivots */
//   iparm[14] = 0;        /* Not in use */
//   iparm[15] = 0;        /* Not in use */
//   iparm[16] = 0;        /* Not in use */
//   iparm[17] = -1;       /* Output: Number of nonzeros in the factor LU */
//   iparm[18] = -1;       /* Output: Mflops for LU factorization */
//   iparm[19] = 0;        /*  Output: Numbers of CG Iterations */
//   iparm[23] = 1;
//   iparm[34] = 1;        /* Zero-based indexing */
//   maxfct = 13;
//   mnum = 1;
//   msglvl = 3;
//   msglvl = 0;
//   // error = 0;
//   for(int i = 0; i < 64; i++) {
// 	pt[i] = 0;
//   }
//   phase = 11;
//   int nrhs=2;
//   pardiso (pt, &maxfct, &mnum, &mtype, &phase, &ni, Lii_val, Lii_row, Lii_col, NULL, &nrhs, iparm, &msglvl, NULL, NULL, &error);
//   if (error != 0){
//       cerr<<"Symbolic Factor Error\n";
//       exit(1);
//   }
//   phase = 22;
//   pardiso (pt, &maxfct, &mnum, &mtype, &phase, &ni, Lii_val, Lii_row, Lii_col, NULL, &nrhs, iparm, &msglvl, b, x, &error);
//   if (error != 0){
//       cerr<<"Numerical Factor Error\n";
//       exit(1);
//   }
//   phase = 33;
//   pardiso (pt, &maxfct, &mnum, &mtype, &phase, &ni, Lii_val, Lii_row, Lii_col, NULL, &nrhs, iparm, &msglvl, b, x, &error);
//   if (error !=0){
//       cerr<<"Solve Error\n";
//       exit(1);
//   }
//   for (int i=0; i<2; i++){
//     for (int j=0; j<ni; j++){
//       U[i*nv+nb+j]=x[i*ni+j];
//     }
//   }
//   for (int i=0; i<ni; i++) {
//     fout<<x[i]<<" "<<x[ni+i]<<"\n";
//   }
//   fout.close();
//   delete [] b;
//   delete [] x;

  int ni = nv-nb;
  cout<<"1\n";
  double *Lii=new double [ni*ni], *Lib=new double [ni*nb];
  for (int i=0; i<ni*ni; i++){
    Lii[i]=0;
  }
  for (int i=0; i<ni*nb; i++){
    Lib[i]=0;
  }
  for (int i=0; i<ni; i++){
    for (int j=Lii_row[i]; j<Lii_row[i+1]; j++) {
      Lii[Lii_col[j]*ni+i]=Lii_val[j];
    }
    for (int j=Lib_row[i]; j<Lib_row[i+1]; j++) {
      Lib[Lib_col[j]*ni+i]=Lib_val[j];
    }
  }
  cout<<"2\n";
  int *ipiv = new int[ni];
  const double *Ub  = U;
  double       *Ui  = U+nb;
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, ni, 2, nb, -1.0, Lib, ni, Ub, nv, 0.0, Ui, nv);
  // Solve Lii Ui = Tmp [in Ui]
  int info = LAPACKE_dgesv(LAPACK_COL_MAJOR, ni, 2, Lii, ni, ipiv, Ui, nv);
  cout<<"info="<<info<<"\n";
  assert(info == 0);
  delete [] Lii;
  delete [] Lib;
}
