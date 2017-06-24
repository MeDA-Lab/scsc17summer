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
  Method method = Method::KIRCHHOFF;

  int nv, nf, nb, *F = nullptr, *idx_b = nullptr;
  int Lii_nnz = 0, Lib_nnz = 0, *Lii_row = nullptr, *Lii_col = nullptr, *Lib_row = nullptr, *Lib_col = nullptr;
  double *Lii_val = nullptr, *Lib_val = nullptr;
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
  constructLaplacianSparse(method, nv, nb, nf, V, F,
                           &Lii_val, &Lii_row, &Lii_col, &Lii_nnz,
                           &Lib_val, &Lib_row, &Lib_col, &Lib_nnz);

  // Map boundary
  cout << "Maping boundary ..." << endl;
  U = new double[2 * nv];
  mapBoundary(nv, nb, V, U);


  // Solve harmonic
  cout << "Solving harmonic ..." << endl;
  solveHarmonicSparse(nv, nb, Lii_val, Lii_row, Lii_col, Lib_val, Lib_row, Lib_col, U);
  // Write object
  cout << "Writing object ..." << endl;
  writeObject(output, nv, nf, U, C, F);

  // Free memory
  cout << "Done." << endl;
  delete[] V;
  delete[] C;
  delete[] F;
  delete[] Lii_val;
  delete[] Lii_row;
  delete[] Lii_col;
  delete[] Lib_val;
  delete[] Lib_row;
  delete[] Lib_col;
  delete[] U;
  delete[] idx_b;

  return 0;
}
