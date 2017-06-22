////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main.hpp
/// @brief   The main function.
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

  const char *input  = "input.obj";
  const char *output = "output.obj";
  Method method  = Method::SIMPLE;

  int nv, nf, nb, *F = nullptr, *idx_b;
  double *V = nullptr, *C = nullptr, *L, *U;

  double time0, time1;

  // Read arguments
  cout << endl << "========== Reading Arguments ===========" << endl << endl;
  time0 = getTime();
  readArgs(argc, argv, input, output, method);
  time1 = getTime();
  cout << "Used " << time1-time0 << " seconds." << endl;

  // Read object
  cout << endl << "=========== Reading Objects ============" << endl << endl;
  time0 = getTime();
  readObject(input, &nv, &nf, &V, &C, &F);
  time1 = getTime();
  cout << "Used " << time1-time0 << " seconds." << endl;

  // Verify boundary
  cout << endl << "========== Verifying Boundary ==========" << endl << endl;
  time0 = getTime();
  idx_b = new int[nv];
  verifyBoundary(nv, nf, F, &nb, idx_b);
  time1 = getTime();
  cout << "Used " << time1-time0 << " seconds." << endl;

  // Reorder vertices
  cout << endl << "========= Reordering Vertices ==========" << endl << endl;
  time0 = getTime();
  reorderVertex(nv, nb, nf, idx_b, V, C, F);
  time1 = getTime();
  cout << "Used " << time1-time0 << " seconds." << endl;

  // Construct Laplacian
  cout << endl << "======== Constructing Laplacian ========" << endl << endl;
  L = new double[nv * nv];
  time0 = getTime();
  constructLaplacian(method, nv, nf, V, F, L);
  time1 = getTime();
  cout << "Used " << time1-time0 << " seconds." << endl;

  // Map boundary
  cout << endl << "=========== Mapping Boundary ===========" << endl << endl;
  U = new double[2 * nv];
  time0 = getTime();
  mapBoundary(nv, nb, V, U);
  time1 = getTime();
  cout << "Used " << time1-time0 << " seconds." << endl;

  // Solve harmonic
  cout << endl << "=========== Solving Harmonic ===========" << endl << endl;
  time0 = getTime();
  solveHarmonic(nv, nb, L, U);
  time1 = getTime();
  cout << "Used " << time1-time0 << " seconds." << endl;

  // Write object
  cout << endl << "============ Writing Object ============" << endl << endl;
  time0 = getTime();
  writeObject(output, nv, nf, U, C, F);
  time1 = getTime();
  cout << "Used " << time1-time0 << " seconds." << endl;

  // Free memory
  cout << endl << "================= Done =================" << endl << endl;
  delete[] V;
  delete[] C;
  delete[] F;
  delete[] L;
  delete[] U;
  delete[] idx_b;

  return 0;
}
