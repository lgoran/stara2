#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>
#include"sor.c"
#include"cg.c"

int main() {

    integer n=99, info, i, j, iter, n2=n*n;
    doublereal *A, *b, *x,*y0, tol=1e-8, omega=1.0, h, d, h2, *pom;
    char uplo='L';

    h=(double) 1/(n+1);
    h2=h*h;
    
    A=(doublereal*)calloc(n*n,sizeof(doublereal));
    b=(doublereal*)malloc(n*sizeof(doublereal));
    x=(doublereal*)malloc(n*sizeof(doublereal));
    y0=(doublereal*)calloc(n,sizeof(doublereal));
    pom=(doublereal*)calloc(n*n,sizeof(doublereal));

    //vektori x,b
    for(i=0; i<n; i++) {
        x[i]=(i+1)*h;
        b[i]=2*h2*sin(x[i]);
    }
    b[n-1]+=cos(1);

    //for(i=0;i<n;i++) printf("%lg\t %lg\t \n", x[i], b[i]);

    //matrica A
    d=2-h2;
    for(i=1; i<n-1; i++) {
        A[i*n+i]=2-h*h;
        A[i-1 + n*i]=-1;
        A[i+1 + n*i]=-1;
    }
    A[0]=d; A[1]=-1;
    A[n*n-1]=d; A[n*n-2]=-1;

    //pom=A
    i=1;
    dcopy_(&n2, A, &i, pom, &i);
    dpotrf_(&uplo, &n, pom, &n, &info);
    if (!info) printf("Matrica A je pozitivno definitna.\n");
    else printf("Matrica A nije pozitivno definitna.\n");
  
    //Gauss-Seidel (SOR sa omega=1)
    iter=sor(A,n,b,y0,omega,tol); 
    printf("Gauss-Seidel\naproksimirano rješenje:\t");
    for (i=0; i<n; i++)
        printf("%lg ", y0[i]);
    printf("\n");
    printf("broj iteracija:\t %ld\n\n", iter); 

    //SOR s omega=1.95
    omega=1.95;
    for (i=0;i<n; i++) y0[i]=0;
    iter=sor(A,n,b,y0,omega,tol); 
    printf("SOR\naproksimirano rješenje:\t");
    for (i=0; i<n; i++)
        printf("%lg ", y0[i]);
    printf("\n");
    printf("broj iteracija:\t %ld\n\n", iter); 

    //CG
    for (i=0;i<n; i++) y0[i]=0;
    iter=cg(n,A,b,y0,tol); 
    printf("CG\naproksimirano rješenje:\t");
    for (i=0; i<n; i++)
        printf("%lg ", y0[i]);
    printf("\n");
    printf("broj iteracija:\t %ld\n\n", iter);

/*
    printf("matrica A:\n");
        for (i=0; i<n*n; i++) {
            if(i%n==0) printf("\n");
            printf("%lg ",A[i]);         
         }
    printf("\n");
    printf("%lg\n", A[0]);
*/


return 0;
}
