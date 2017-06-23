////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main_sparse.hpp
/// @brief   The main function. (sparse version)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <harmonic.hpp>
#include <timer.hpp>
#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Main function
///
int main( int argc, char** argv ) {

  const char *input  = "input.obj";
  const char *output = "output.obj";
  Method method  = Method::SIMPLE;

  int nv, nf, nb, *F = nullptr, *idx_b=NULL;
  int *Lii_row=NULL, *Lii_col=NULL, *Lib_row=NULL, *Lib_col=NULL;
  int Lii_nnz=0, Lib_nnz=0;
  double *Lii_val=NULL, *Lib_val=NULL;
  double *V = nullptr, *C = nullptr, *U;

  // Read arguments
  cout << "Reading arguments ..." << endl;
  readArgs(argc, argv, input, output, method);

  // Read object
  cout << "Reading objects ..." << endl;
  readObject(input, &nv, &nf, &V, &C, &F);

  // Verify boundary
  cout << "Verifying boundary ..." << endl;
  idx_b = new int[nv];
  verifyBoundarySparse(nv, nf, F, &nb, idx_b);

  // Reorder vertex
  cout << "Reordering vertex ..." << endl;
  reorderVertex(nv, nb, nf, idx_b, V, C, F);

  // Construct Laplacian
  cout << "Constructing Laplacian ..." << endl;
  // constructLaplacianSparse(method, nv, nf, V, F, &nnz, &L_val, &L_row, &L_col);
  constructLaplacianSparse( method, nv, nb, nf, V, F,
                            &Lii_val, &Lii_row, &Lii_col, &Lii_nnz,
                            &Lib_val, &Lib_row, &Lib_col, &Lib_nnz);

  // Map boundary
  cout << "Maping boundary ..." << endl;
  U = new double[2 * nv];
  mapBoundary(nv, nb, V, U);

  
  // Solve harmonic
  cout << "Solving harmonic ..." << endl;
  solveHarmonicSparse(nv, nb,
                      Lii_val, Lii_row, Lii_col, Lii_nnz,
                      Lib_val, Lib_row, Lib_col, Lib_nnz, U );
  // Write object
  cout << "Writing object ..." << endl;
  writeObject(output, nv, nf, U, C, F);

  // Free memory
  cout << "Done." << endl;
  delete[] V;
  delete[] C;
  delete[] F;
  // delete[] L_val;
  // delete[] L_row;
  // delete[] L_col;
  delete[] U;
  delete[] idx_b;

  return 0;
}
