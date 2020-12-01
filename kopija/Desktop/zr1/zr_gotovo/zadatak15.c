#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>


int main(){

    doublereal A[]={1.2,2.9,5.2,6.8,2.1,4.3,6.1,8.1}, B[]={1,3,5,7,2,4,6,8}, *C, *Q;
    char slovo_n='N', slovo_t='T', slovo_f='F', job='A';
    integer m=4, n=2, i, j;
    doublereal alpha=1, beta=0;
    C=(doublereal*)calloc(m, sizeof(doublereal));
    Q=(doublereal*)calloc(m, sizeof(doublereal));

//racunam C
    dgemm_(&slovo_t, &slovo_n, &n, &m, &m, &alpha, A, &m, B, &m, &beta, C, &n);

//racunam SVD (U')*C*V=Sigma
    doublereal *s, *U, *vt, *work, norma;
    integer lwork=5*n, info;
    s=(doublereal*)calloc(n, sizeof(doublereal));
    U=(doublereal*)calloc(n*n, sizeof(doublereal));
    vt=(doublereal*)calloc(n*n, sizeof(doublereal));
    work=(doublereal*)calloc(lwork, sizeof(doublereal));
    
    dgesvd_(&job, &job, &n, &n, C, &n, s, U, &n, vt, &n, work, &lwork, &info);
    
//racunam Q
    dgemm_(&slovo_n, &slovo_n, &n, &n, &n, &alpha, U, &n, vt, &n, &beta,Q, &n);
    printf("matrica Q:\n");
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++)
            printf("%4g ", Q[j*n+i]);
        printf("\n");
    }
    printf("\n\n");

//racunam B=AQ-B
    beta=-1;
    dgemm_(&slovo_n, &slovo_n, &m, &n, &n, &alpha, A, &m, Q, &n, &beta, B, &m);

    norma=dlange_(&slovo_f, &m, &n, B, &m, work);

    printf("norma(AQ-B):\n%4g\n\n", norma);

return 0;
}
