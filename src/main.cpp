////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main.hpp
/// @brief   The main function
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <harmonic.hpp>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Main function
///
int main( int argc, char** argv ) {

  const char *filename = "UNSPECIFIED FILE";
  Method method  = Method::SIMPLE;

  int nv, nf, nb, *F = nullptr, *idx_b;
  double *V = nullptr, *C = nullptr, *L, *U;

  // Read arguments
  read_args(argc, argv, filename, method);

  // Read object
  readObject(filename, &nv, &nf, &V, &C, &F);

  // Verify boundary
  verifyBoundary(nv, nf, F, &nb, &idx_b);

  // Reorder vertex
  for (int i=0; i<nb; i++) {
    cout<<idx_b[i]<<" ";
  }
  cout<<"\n";
  reorderVertex(nv, nb, nf, idx_b, V, C, F);
  for (int i=0; i<nf; i++) {
    for (int j=0; j<3; j++){
      cout<<F[j*nf+i]<<" ";
    }
    cout<<"\n";
  }
  // Construct Laplacian
  L = new double[nv * nv];
  constructLaplacian(method, nv, nf, V, F, L);
  
  // Map boundary
  U = new double[2 * nv];
  mapBoundary(nv, nb, V, U);

  // Solve harmonic
  solveHarmonic(nv, nb, L, U);
  // Free memory
  delete[] V;
  delete[] C;
  delete[] F;
  delete[] L;
  delete[] U;
  delete[] idx_b;

  return 0;
}
