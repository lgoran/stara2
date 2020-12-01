#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"


void cg(integer n, doublereal *A, doublereal *b, doublereal *x, doublereal tol) {
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

        for(i=0;i<n;i++) printf("%g ", x[i]);
        printf("\n\n");
        dcopy_(&n, b, &inc, e, &inc); //e=b
        dgemv_(&slovon, &n, &n, &minusjedan, A, &n, x, &inc, &jedan, e, &inc); //e=b-Ax
        rezidual=dnrm2_(&n, e, &inc)/nrmb;
        
    }
    printf("potreban broj iteracija %ld\n", k);
    free(e); free(d); free(r); free(Ad);

return;
}

int main() {

    doublereal *A, *b, *x0, tol=1e-8, *D, *tau, *work, *x, alfa=1, beta=0;
    integer n=100, n2, i, lwork=n*n, info, dist=2, sjeme[4]={12, 1021, 457, 1875}, jedan=1;
    n2=n*n;
    char L='L', N='N', T='T', R='R';

    D=(doublereal*)calloc(n*n, sizeof(doublereal));
    A=(doublereal*)malloc(n*n*sizeof(doublereal));
    work=(doublereal*)calloc(n*n, sizeof(doublereal));
    tau=(doublereal*)malloc(n*sizeof(doublereal));
    x0=(doublereal*)calloc(n, sizeof(doublereal));
    x=(doublereal*)malloc(n*sizeof(doublereal));
    b=(doublereal*)malloc(n*sizeof(doublereal));

    for(i=0;i<n;i++) x[i]=1;

    dlarnv_(&dist, sjeme, &n2, A);
    //for(i=0;i<n2;i++) { printf("%g ", A[i]); if((i+1)%n==0) printf("\n"); }
    for(i=1;i<=n;i++) D[(i-1)*n+(i-1)]=i*i;
    
    dgeqrf_(&n, &n, A, &n, tau, work, &lwork, &info);
    dorgqr_(&n, &n, &n, A, &n, tau, work, &lwork, &info);
    dormqr_(&L, &N, &n, &n, &n, A, &n, tau, D, &n, work, &lwork, &info);    
    dormqr_(&R, &T, &n, &n, &n, A, &n, tau, D, &n, work, &lwork, &info);

    for(i=0;i<n2;i++) { printf("%g ", D[i]); if((i+1)%n==0) printf("\n"); }
   //D je simetrična pozitivno definitna matrica

    dgemv_(&N, &n, &n, &alfa, D, &n, x, &jedan, &beta, b, &jedan);
    printf("izračunati b: \n");
    for(i=0;i<n;i++)
        printf("%g ", b[i]);
    printf("\n\n");
    printf("cg...\n");
    cg(n, D, b, x0, tol);

    printf("aproksimirano rješenje sustava: \n");
    for(i=0;i<n;i++)
        printf("%g ", x0[i]);
    printf("\n");
    
    free(A); free(b); free(D); free(work); free(tau); free(x0); free(x); 
return 0;

}
