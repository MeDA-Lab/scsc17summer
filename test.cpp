#include <mkl.h>
#include <iostream>
using namespace std;
int main(){
    int row[3]={0, 1 , 0};
    int col[3]={0, 1 , 0};
    double val[3]={1, 2, 3};
    int job[6]={2, 0, 0, 0, 3, 0};
    int n=2, nnz=3, rowind[n+1], colind[nnz], info = 0;
    double acsr[nnz];
    mkl_dcsrcoo(job, &n, acsr, colind, rowind, &nnz, val, row, col, &info);
    cout<<info<<"\n";
    for (int i=0; i<n; i++){
        for (int j=rowind[i]; j<rowind[i+1]; j++){
            cout<<i<<" "<<colind[j]<<" "<<acsr[j]<<"\n";
        }
    }
}