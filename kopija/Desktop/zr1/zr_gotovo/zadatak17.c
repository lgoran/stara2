#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "f2c.h"
#include "fblaswr.h"
#include "clapack.h"

int main() {
    integer m=10, n=2;
    doublereal A[]={1,1,1,1,1,1,1,1,1,1,1,2,3,4,5,6,7,8,9,10}, 
               B[]={3.5,4.9,6.8,9.3,10.9,13.4,15.1,16.7,19,21.2}, c[10], d[10];
    char job='A', slovo_t='T', slovo_n='N';
    doublereal *s, *u, *U, *vt, *work, alpha=1, beta=0;
    integer lwork=16, info, i, j, inc=1;

    s=(doublereal*)calloc(n, sizeof(doublereal));
    u=(doublereal*)calloc(m*m, sizeof(doublereal));
    U=(doublereal*)calloc(m*n, sizeof(doublereal));
    vt=(doublereal*)calloc(n*n, sizeof(doublereal));
    work=(doublereal*)calloc(lwork, sizeof(doublereal));

//racunam SVD dekompoziciju matrice A
    dgesvd_(&job, &job, &m, &n, A, &m, s, u, &m, vt, &n, work, &lwork, &info);
    
    for(i=0;i<m;i++) 
        for(j=0;j<n;j++) 
            U[j*m+i]=u[j*m+i];
//c = U' * B
    dgemv_(&slovo_t, &m, &n, &alpha, U, &m, B, &inc, &beta, c, &inc);

//d = sigma(inverz) * U' * b
    c[0]=c[0]/s[0]; 
    c[1]=c[1]/s[1];

//d = V * sigma(inverz) * U' * b
    dgemv_(&slovo_n, &n, &n, &alpha, vt, &n, c, &inc, &beta, d, &inc);

    for(i=0;i<n;i++) 
        printf("%g ",d[i]); 
    printf("\n");

return 0;
}
