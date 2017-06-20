////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    harmonic.hpp
/// @brief   The main header
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef SCSC_HARMONIC_HPP
#define SCSC_HARMONIC_HPP

#include <getopt.h>
#include <def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads the arguments.
///
/// @param[in]   argc      The number of input arguments.
/// @param[in]   argv      The input arguments.
///
/// @param[out]  filename  The filename.
/// @param[out]  method    The method.
///
void read_args( int argc, char** argv, const char *&filename, Method &method );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads the object file.
///
/// @param[in]   filename  the path to the object file.
///
/// @param[out]  ptr_nv    the number of vertices; pointer.
/// @param[out]  ptr_nf    the number of faces;    pointer.
/// @param[out]  V         the coordinate of vertices; nv by 3 matrix.      pointer-to-pointer
/// @param[out]  C         the color of the vertices; nv by 3 matrix; RGB.  pointer-to-pointer
/// @param[out]  F         the faces; nf by 3 matrix.                       pointer-to-pointer
///
/// @note  The arrays are allocated by this routine (using new).
///
void readObject( const char *filename, int *ptr_nv, int *ptr_nf, double **V, double **C, int **F );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Verify the boundary vertices.
///
/// @param[in]   nv      the number of vertices.
/// @param[in]   nf      the number of faces.
/// @param[in]   F       the faces; nf by 3 matrix.
///
/// @param[out]  ptr_nb  the number of boundary vertices; pointer.
/// @param[out]  idx_b   the indices of boundary vertices, nb by 1 vector.
///
///
///
void verifyBoundary( const int nv, const int nf, const int *F, int *ptr_nb, int **idx_b );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reorder the vertices.
///
/// @param[in]   nv     the number of vertices.
/// @param[in]   nb     the number of boundary vertices.
/// @param[in]   idx_b  the indices of boundary vertices, nb by 1 vector.
/// @param[in]   V      the coordinate of vertices; nv by 3 matrix.
/// @param[in]   C      the color of the vertices; nv by 3 matrix; RGB.
///
/// @param[out]  V      replaced by the reordered coordinate of vertices; nv by 3 matrix.
/// @param[out]  C      replaced by the reordered color of the vertices; nv by 3 matrix; RGB.
///
/// @note  the vertices are reordered so that the first nb vertices are the boundary vertices.
///
void reorderVertex( const int nv, const int nb, const int nf, const int *idx_b, double *V, double *C, int *F );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct the Laplacian.
///
/// @param[in]   method  the method of Laplacian construction.
/// @param[in]   nv      the number of vertices.
/// @param[in]   nf      the number of faces.
/// @param[in]   V       the coordinate of vertices; nv by 3 matrix.
/// @param[in]   C       the color of the vertices; nv by 3 matrix; RGB.
/// @param[in]   F       the faces; nf by 3 matrix.
///
/// @param[out]  L       the Laplacian matrix; nv by nv matrix.
///
/// @note  The output arrays should be allocated before calling this routine.
///
void constructLaplacian( const Method method, const int nv, const int nf, const double *V,
                         const int *F, double *L );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Map the boundary vertices.
///
/// @param[in]   nv  the number of vertices.
/// @param[in]   nb  the number of boundary vertices.
/// @param[in]   V   the coordinate of vertices; nv by 3 matrix.
///
/// @param[out]  U   the coordinate of boundary vertices on the disk; nv by 2 matrix.
///
/// @note  The output arrays should be allocated before calling this routine.
///
void mapBoundary( const int nv, const int nb, const double *V, double *U );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Solve the harmonic problem.
///
/// @param[in]   nv  the number of vertices.
/// @param[in]   nb  the number of boundary vertices.
/// @param[in]   L   the Laplacian matrix; nv by nv matrix.
/// @param[in]   U   the coordinate of vertices on the disk; nv by 2 matrix. The first nb vertices are given.
///
/// @param[out]  U   the coordinate of vertices on the disk; nv by 2 matrix. The last (nv-nb) vertices are replaced.
///
/// @note  The output arrays should be allocated before calling this routine.
///
void solveHarmonic( const int nv, const int nb, double *L, double *U );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  write the object file
///
/// @param[in]   filename  the path to the object file.
///
/// @param[in]   nv  the number of vertices.
/// @param[in]   nf  the number of faces.
/// @param[in]   U   the coordinate of vertices on the disk; nv by 2 matrix.
/// @param[in]   C   the color of vertices. RGB.
/// @param[in]   F   the faces; nf by 3 matrix.
///
///
void writeObject( const filename, const int nv, const int nf, double *U, double *C, double *F );


#endif  // SCSC_HARMONIC_HPP
