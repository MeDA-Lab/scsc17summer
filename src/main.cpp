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
  cout<<"nv"<<nv<<endl;
  for (int i=0; i<nv; i++){
    printf("%lf %lf %lf %lf %lf %lf\n", V[i], V[nv+i], V[2*nv+i], C[i], C[nv+i], C[2*nv+i]);
  }
  cout<<"nf"<<nf<<endl;
  for (int i=0; i<nf; i++){
    printf("%d %d %d\n", F[i], F[nf+i], F[2*nf+i]);
  }
  // Verify boundary
  idx_b = (int*) malloc(sizeof(int) * nv);
  verifyBoundary(nv, nf, F, &nb, idx_b);

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
