////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main.hpp
/// @brief   The main function
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <harmonic.hpp>
#include <utility.hpp>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Main function
///
int main( int argc, char** argv ){

  char *filename = nullptr;
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
  reorderVertex(nv, nb, idx_b, V, C);

  // Construct Laplacian
  L = (double*) malloc(sizeof(double) * nv * nv);
  constructLaplacian(method, nv, nf, V, C, F, L);

  // Map boundary
  U = (double*) malloc(sizeof(double) * nv);
  mapBoundary(nv, nb, V, U);

  // Solve harmonic
  solveHarmonic(nv, nb, L, V, U);

  // Free memory
  free(V);
  free(C);
  free(F);
  free(L);
  free(U);
  free(idx_b);

  return 0;
}
