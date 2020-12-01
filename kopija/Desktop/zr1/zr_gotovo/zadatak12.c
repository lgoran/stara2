#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>

doublereal S(doublereal *A, integer n){
    int i,j;
    doublereal s=0;

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            if(i!=j)
                s += pow(A[j*n+i],2);
    s=sqrt(s);
    return s;
}

doublereal* jacobi_sd(integer n, doublereal *A, doublereal tol) {
    integer p,q,k,i;
    doublereal tau, t, c, s, app, apq, aqq, *sv, f, *work, pom;
    char norma='F';

    sv=(doublereal*)malloc(n*sizeof(doublereal)); 
    work=(doublereal*)malloc(n*sizeof(doublereal));


    f=dlange_(&norma, &n, &n, A, &n, work); //f=frob.norm(A)

    while(S(A,n) > tol*f) {
        for(p=0; p<n-1; p++) {
            for(q=p+1; q<n; q++){
                if(A[q*n+p] != 0) {
                    tau=(A[q*n+q]-A[p*n+p])/(2*A[q*n+p]);
                    t=(tau/abs(tau)) / (fabs(tau)+sqrt(1+pow(tau,2)));
                    c=1/(sqrt(1+pow(t,2)));
                    s=t*c;
                    app=A[p*n+p]; apq=A[q*n+p]; aqq=A[q*n+q];
                    app=app-t*apq;
                    aqq=aqq+t*apq;
                    for(k=0; k<n; k++) {
                        pom=A[p*n+k];
                        A[p*n+k]=c*pom-s*A[q*n+k];
                        A[q*n+k]=s*pom+c*A[q*n+k];
                        A[k*n+p]=A[p*n+k]; A[k*n+q]=A[q*n+k];
                    }
                    A[q*n+p]=0; A[p*n+q]=0;
                    A[p*n+p]=app; A[q*n+q]=aqq;
                }
            }
        }
    }

    for(i=0; i<n; i++)
        sv[i]=A[i*n+i];

    return sv;

}



int main() {
    doublereal *A, *sv, tol=1e-15;
    integer i, j, n=10;

    A=(doublereal*)calloc(n*n, sizeof(doublereal));
    sv=(doublereal*)calloc(n, sizeof(doublereal));

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            A[j*n+i]=0.5/(9.5-i-j);

    sv=jacobi_sd(n,A,tol);
    
    for(i=0; i<n; i++)
        printf("%g\n", sv[i]);
    printf("\n");
/*
    for(i=0; i<n; i++){
        for(j=0; j<n; j++)
            printf("%5.4g    ", A[j*n+i]);
        printf("\n");}
    */

return 0;
}

