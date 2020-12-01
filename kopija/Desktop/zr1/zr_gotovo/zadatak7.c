#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>
#include"GMRES.c"

doublereal *A;
integer n=100;

void matvec(doublereal *alpha, doublereal *x, doublereal *beta, doublereal *y) {
    char slovo_n='N';  
    integer inc=1;
    dgemv_(&slovo_n, &n, &n, alpha, A, &n, x, &inc, beta, y, &inc);
return;
}

void psolve(doublereal *x, doublereal *b) {
    int i;
    for (i=0; i<n; i++) 
        x[i]=b[i];
return;
}

int main(){
    integer i, j, n2=n*n, lwork=n2, info, *ipiv, restrt=n, lwrk=n, ldh=restrt+1, ldh1=ldh*(restrt+2), iter=n, ldv=n;
    doublereal *B, *x, *b, *tau, *work, *P, *g, *V, *wrk, tol=1e-5, *h,  alfa=1, beta=0, *wr, *wi, *vl, *vr; 
    char N='N', T='T', L='L';
    
    A=(doublereal*)malloc(n2*sizeof(doublereal));
    b=(doublereal*)calloc(n, sizeof(doublereal));
    x=(doublereal*)calloc(n, sizeof(doublereal));
    B=(doublereal*)malloc(n2*sizeof(doublereal));
    tau=(doublereal*)malloc(n*sizeof(doublereal));
    work=(doublereal*)malloc(n2*sizeof(doublereal));
    g=(doublereal*)malloc(n*sizeof(doublereal));
    V=(doublereal*)malloc(n2*sizeof(doublereal));
    ipiv=(integer*)malloc(n*sizeof(integer));
    P=(doublereal*)calloc(n2, sizeof(doublereal));
    wrk=(doublereal*)malloc(lwrk*(restrt+4)*sizeof(doublereal));
    h=(doublereal*)malloc(ldh1*sizeof(doublereal));
    
    for (i=0; i<n; i++)
        P[(i-1)*n+i]=1;
    P[n*(n-1)]=1;

    for(i=0;i<n;i++) 
        g[i]=sqrt(201-2*(i+1));
    
    //generiram ortogonalnu matricu V
    dorgqr_(&n, &n, &n, V, &n, tau, work, &n, &info);

    for(j=0; j<n; j++)
        for(i=0; i<n; i++)    
               b[j]+=g[i]*V[j*n+i];

    for(i=0; i<n; i++)
        B[i]=b[i];
    for(j=1;j<n;j++) 
        for(i=0;i<n;i++) 
            B[j*n+i]=V[(j-1)*n+i];

    dgemm_(&N, &N, &n, &n, &n, &alfa, B, &n, P, &n, &beta, V, &n); //V=B*P
    dgetrf_(&n, &n, B, &n, ipiv, &info); 
    dgetri_(&n, B, &n, ipiv, work, &lwork, &info); // B=inv(B)
    dgemm_(&N, &N, &n, &n, &n, &alfa, V, &n, B, &n, &beta, A, &n); //A=V*inv(B)
    
    gmres_(&n, b, x, &restrt, wrk, &lwrk, h, &ldh, &iter, &tol, matvec, psolve, &info);

    printf("\n");
    printf("aproksimirano rjesenje:\n");
        for(i=0; i<n; i++) 
            printf("%g ", x[i]);
    printf("\n");
    
    wr=(doublereal*)malloc(n*sizeof(doublereal));
    wi=(doublereal*)malloc(n*sizeof(doublereal));
    vl=(doublereal*)malloc(ldv*sizeof(doublereal));
    vr=(doublereal*)malloc(ldv*sizeof(doublereal));
    dgeev_(&N, &N, &n, A, &n, wr, wi, vl, &ldv, vr, &ldv, work, &lwork, &info);
    
    doublereal *r, *fi, *Re_z, *Im_z;
    r=(doublereal*)malloc(n*sizeof(doublereal));
    fi=(doublereal*)malloc(n*sizeof(doublereal));
    Re_z=(doublereal*)malloc(n*sizeof(doublereal));
    Im_z=(doublereal*)malloc(n*sizeof(doublereal));

    for(i=0; i<n; i++) {
        r[i]=sqrt(wr[i]*wr[i]+wi[i]*wi[i]); 
        fi[i]=atan(wi[i]/wr[i]); 
        Re_z[i]=pow(r[i],100)*(cos(n*fi[i])); 
        Im_z[i]=pow(r[i],100)*(sin(n*fi[i]));
    }
    printf("\n");

    for(i=0; i<n; i++) {
        if(Im_z[i]>=0) printf("%g\t+\t%g\t*i \n", Re_z[i], Im_z[i]);
        else printf("%g\t-\t%g\t*i \n", Re_z[i], -Im_z[i]);
    }

    free(A); free(b); free(x); free(wrk); free(V); free(g); free(tau); free(work); free(P); free(ipiv); free(h);
    free(wr); free(wi); free(vl); free(vr); free(r); free(fi); free(Re_z); free(Im_z);
    


return 0;
}





