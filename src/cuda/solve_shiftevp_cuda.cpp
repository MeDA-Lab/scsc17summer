////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    solve_shiftevp_cuda.cpp
/// @brief   The implementation of solving eigenvalueproblem by shift-method by CUDA
///
/// @author  Yuhsiang Mike Tsai
///

void solveShiftEVP(
    int m,
    int nnz,
    const double *A_val,
    const int *A_row,
    const int *A_col,
    const double mu0,
    double *mu,
    double *x
) {
    cusolverSpHandle_t sp_handle;
    double *x0 = nullptr, tol = 1e-8;
    int maxite = 1000;
    cusolverSpCreate(&sp_handle);
    cusparseMatDescr_t descrA;
    descrA.DiagType = CUSPARSE_DIAG_TYPE_NON_UNIT;
    descrA.IndexBase = CUSPARSE_INDEX_BASE_ZERO;
    descrA.MatrixType = CUSPARSE_MATRIX_TYPE_GENERAL;
    x0 = new double[m];
    for (int i = 0; i < m; i++) {
        x0[i] = 0;
    }
    cusolverSpDcsreigvsiHost(sp_handle, m, nnz, descrA, A_val, A_row, A_col,
                         mu0, x0, maxite, tol, mu, x);
    cusolverSpDestroy(sp_handle);
    delete x0;
}
