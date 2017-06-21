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
  const char *output = "output.obj";
  Method method  = Method::SIMPLE;

  int nv, nf, nb, *F = nullptr, *idx_b;
  double *V = nullptr, *C = nullptr, *L, *U;

  // Read arguments
  cout << "Reading arguments ..." << endl;
  read_args(argc, argv, filename, output, method);
  
  // Read object
  cout << "Reading objects ..." << endl;
  readObject(filename, &nv, &nf, &V, &C, &F);

  // Verify boundary
  cout << "Verifying boundary ..." << endl;
  idx_b = new int[nv];
  verifyBoundary(nv, nf, F, &nb, idx_b);
  // for (int i=0 ; i<nb; i++){
  //   cout<<idx_b[i]<<"\n";
  // }
  // Reorder vertex
  cout << "Reordering vertex ..." << endl;
  reorderVertex(nv, nb, nf, idx_b, V, C, F);

  // Construct Laplacian
  cout << "Constructing Laplacian ..." << endl;
  L = new double[nv * nv];
  constructLaplacian(method, nv, nf, V, F, L);

  // Map boundary
  cout << "Maping boundary ..." << endl;
  U = new double[2 * nv];
  mapBoundary(nv, nb, V, U);

  // Solve harmonic
  cout << "Solving harmonic ..." << endl;
  solveHarmonic(nv, nb, L, U);

  // Write object
  cout << "Writing object ..." << endl;
  writeObject(output, nv, nf, U, C, F);

  // Free memory
  delete[] V;
  delete[] C;
  delete[] F;
  delete[] L;
  delete[] U;
  delete[] idx_b;

  return 0;
}
