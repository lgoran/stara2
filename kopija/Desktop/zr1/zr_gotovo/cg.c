#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"

integer cg(integer n, doublereal *A, doublereal *b, doublereal *x, doublereal tol) {
    doublereal *e, *d, *r, alpha, beta, beta1, rezidual=tol+1, *Ad, *ad, jedan=1, nula=0, minusjedan=-1, rk, rk1, nrmb;
    integer k=0, inc=1, i;
    char slovon='n';

    e=(doublereal*)malloc(n*sizeof(doublereal));
    d=(doublereal*)malloc(n*sizeof(doublereal));
    r=(doublereal*)malloc(n*sizeof(doublereal));
    Ad=(doublereal*)malloc(n*sizeof(doublereal));

    nrmb=dnrm2_(&n, b, &inc);
    dcopy_(&n, b, &inc, e, &inc); //e=b
    dcopy_(&n, b, &inc, r, &inc); //r=b
    dgemv_(&slovon, &n, &n, &minusjedan, A, &n, x, &inc, &jedan, r, &inc); //r=r-Ax
    dcopy_(&n, r, &inc, d, &inc); //d=r
    
    while(rezidual>tol) {
        
        dgemv_(&slovon, &n, &n, &jedan, A, &n, d, &inc, &nula, Ad, &inc); //Ad=A*d
        rk=ddot_(&n, r, &inc, r, &inc); //rk=rkt*rk
        alpha=rk/(ddot_(&n, d, &inc, Ad, &inc)); //alpha=...
        daxpy_(&n, &alpha, d, &inc, x, &inc); //x=x+alpha*d
        alpha=-alpha;
        daxpy_(&n, &alpha, Ad, &inc, r, &inc); //r=r-alpha*Ad
        rk1=ddot_(&n, r, &inc, r, &inc); 
        beta=rk1/rk;
        beta1=1/beta;
        daxpy_(&n, &beta1, r, &inc, d, &inc);//d=d+beta1*r /puta beta
        dscal_(&n, &beta, d, &inc); //d=beta*d+r
        k++;

        dcopy_(&n, b, &inc, e, &inc); //e=b
        dgemv_(&slovon, &n, &n, &minusjedan, A, &n, x, &inc, &jedan, e, &inc); //e=b-Ax
        rezidual=dnrm2_(&n, e, &inc)/nrmb;   
    }
    free(e); free(d); free(r); free(Ad);

return k;
}
