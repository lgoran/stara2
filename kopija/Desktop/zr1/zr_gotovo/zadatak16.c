#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "f2c.h"
#include "fblaswr.h"
#include "clapack.h"

int main(){

    doublereal A[]={1, 0, 0, 0, 1, 1, 1, 1}, B[]={1, -1, 1, -1, 0, 1, 0, 1};
    integer m=4, p=2, lwork=4, info, i, j;
    doublereal *tau_a, *tau_b, *work, *C;
    doublereal alpha=1, beta=0;
    char slovo_t='T', slovo_n='N';

    tau_a=(doublereal*)calloc(p, sizeof(doublereal));
    tau_b=(doublereal*)calloc(p, sizeof(doublereal));
    work=(doublereal*)calloc(lwork, sizeof(doublereal));
    C=(doublereal*)calloc(p*p, sizeof(doublereal));
    
//racunam Q iz QR-fakt. za A i B
    dgeqrf_(&m, &p, A, &m, tau_a, work, &lwork, &info);
    dgeqrf_(&m, &p, B, &m, tau_b, work, &lwork, &info);

    dorgqr_(&m, &p, &p, A, &m, tau_a, work, &lwork, &info); 
    dorgqr_(&m, &p, &p, B, &m, tau_b, work, &lwork, &info);     

//racunam C
    dgemm_(&slovo_t, &slovo_n, &p, &p, &m, &alpha, A, &m, B, &m, &beta, C, &p);

//racunam SVD od C
    char jobu='A', jobvt='A';
    doublereal *s, *u, *vt, *work_;
    integer lwork_=5*p;
    s=(doublereal*)calloc(p, sizeof(doublereal));
    u=(doublereal*)calloc(p*p, sizeof(doublereal));
    vt=(doublereal*)calloc(p*p, sizeof(doublereal));
    work_=(doublereal*)calloc(lwork_, sizeof(doublereal));

    dgesvd_(&jobu, &jobvt, &p, &p, C, &p, s, u, &p, vt, &p, work_, &lwork_, &info);

    printf("kosinusi glavnih kuteva: %g , %g.\n\n", s[0], s[1]);

    //glavni vektori
    doublereal *x, *y;
    x=(doublereal*)calloc(p*m, sizeof(doublereal));
    y=(doublereal*)calloc(p*m, sizeof(doublereal));

    dgemm_(&slovo_n, &slovo_n, &m, &p, &p, &alpha, A, &m, u, &p, &beta, x, &m);
    dgemm_(&slovo_n, &slovo_t, &m, &p, &p, &alpha, B, &m, vt, &p, &beta, y, &m);

    for(i=0; i<m; i++) {
        for(j=0; j<p; j++)
            printf("%g ", x[j*m+i]);
        printf("\n");
    }
    printf("\n\n");

    for(i=0; i<m; i++) {
        for(j=0; j<p; j++)
            printf("%g ", y[j*m+i]);
        printf("\n");
    }
    printf("\n\n");


return 0;
}
