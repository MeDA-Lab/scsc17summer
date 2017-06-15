#include "harmonic.hpp"
void Finduvb( vector<double> &vertex, vector<int> &vertex_b, double *uvb, int ldu){
    assert (ldu >= vertex_b.size());
    double *cvblen = NULL;
    cvblen = new double [ldu];
    double *c_vertex = vertex.date();
    for (int i=0; i < vertex_b.size(); i++){
        int ind_a = 0, ind_b = 0;
        ind_a = vertex_b[i];
        if (i+1==vertex_b.size()) {
            ind_b = vertex_b[0];
        }
        else {
            ind_b = vertex_b[i+1];
        }
        cvblen[i]=distence(c_vertex+ind_a, c_vertex+ind_b, vertex.size()/3);
    }
    double first=cvblen[0], s=cvblen[vertex_b.size()-1]-cvblen[0];
    for (int i=0; i<vertex_b.size(); i++){
        cvblen[i]=(cvblen[i]-first)/s;
        uvb[i]=cos(cvblen[i] * PI / 180.0);
        uvb[i+ldu]=sin(cvblen[i] * PI / 180.0);
    }
    delete [] cvblen;
}
double distence(double *a, double *b, int inc){
    double ans=0;
    for (int i=0; i<3; i++) {
        ans+=(a[i*inc]-b[i*inc])*(a[i*inc]-b[i*inc]);
    }
    return sqrt(ans);
}