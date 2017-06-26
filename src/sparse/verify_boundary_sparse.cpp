////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    verify_boundary_sparse.cpp
/// @brief   The implementation of boundary verification.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
/// @author  Yuhsiang Mike Tsai
///

#include <harmonic.hpp>
#include <map>
#include <utility>
#include <iostream>
using namespace std;

using Pair = pair<int, int>;

void verifyBoundarySparse(
    const int nv,
    const int nf,
    const int *F,
    int *ptr_nb,
    int *idx_b
) {
  static_cast<void>(nv);

  int &nb = *ptr_nb;
  int p[3];

  // Generate graph
  map<Pair, int> Gb;
  for ( int i = 0; i < nf; ++i ) {
    p[0] = F[i] - 1;
    p[1] = F[nf+i] - 1;
    p[2] = F[2*nf+i] - 1;

    Gb[Pair(p[1], p[0])]++;
    Gb[Pair(p[2], p[1])]++;
    Gb[Pair(p[0], p[2])]++;

    Gb[Pair(p[0], p[1])]--;
    Gb[Pair(p[1], p[2])]--;
    Gb[Pair(p[2], p[0])]--;
  }

  // Find edges
  map<int, int> Eb;
  for ( auto it = Gb.begin(); it != Gb.end(); ++it ) {
    if ( it->second == -1 ) {
      Eb[it->first.first] = it->first.second;
    }
  }

  // Count boundary size
  nb = Eb.size();

  // List boundary
  int idx = Eb.begin()->first;
  for ( int i = 0; i < nb; ++i ) {
    idx_b[i] = idx;
    idx = Eb[idx];
  }
  return;
}
