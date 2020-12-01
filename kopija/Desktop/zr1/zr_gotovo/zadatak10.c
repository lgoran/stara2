#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>
#include"sor.c"
#include"cg.c"


int main () {

    doublereal *A, *b, *u, tol=1e-8, omega=1.0;
    integer n, nx, ny, i, j, iter; 
    n=81; nx=9; ny=9;

    A=(doublereal*)calloc(n*n,sizeof(doublereal));
    b=(doublereal*)calloc(n, sizeof(doublereal));
    u=(doublereal*)calloc(n, sizeof(doublereal));

 //matrica A: postavljamo D-ove
    for(i=0; i<n; i++) {
        A[i*n+i]=4;
        if(i%nx) {
            A[i*n + i-1]=-1;
            A[(i-1)*n +i]=-1;
        }
    }
//matrica A: postavljamo -I-ove
    for (i=0; i<n-nx; i++) {
        A[n*(nx+i)+i] = -1;
        A[n*i+nx+i] = -1;
    }
/*
    printf("matrica A:\n");
        for (i=0; i<n*n; i++) {
            if(i%n==0) printf("\n");
            printf("%lg ",A[i]);         
         }
    printf("\n");
*/
    b[40]=10000;
        
    //Gauss-Seidel (SOR sa omega=1)
    iter=sor(A,n,b,u,omega,tol); 
    printf("Gauss-Seidel\naproksimirano rješenje:\t");
    for (i=0; i<n; i++) {
        if(i%nx==0) printf("\n");
        printf("%-10lg ", u[i]);
    }
    printf("\n");
    printf("broj iteracija:\t %ld\n\n", iter);
    

    //SOR sa omega=1.53
    for (i=0;i<n; i++) u[i]=0;
    omega=1.53;
    iter=sor(A,n,b,u,omega,tol); 
    printf("SOR\naproksimirano rješenje:\t");
    for (i=0; i<n; i++) {
        if(i%nx==0) printf("\n");
        printf("%-10lg ", u[i]);
    }
    printf("\n");
    printf("broj iteracija:\t %ld\n\n", iter);
    
     //CG
    for (i=0;i<n; i++) u[i]=0;
    iter=cg(n,A,b,u,tol); 
    printf("CG\naproksimirano rješenje:\t");
    for (i=0; i<n; i++) {
        if(i%nx==0) printf("\n");
        printf("%-10lg ", u[i]);
    }
    printf("\n");
    printf("broj iteracija:\t %ld\n\n", iter);


return 0;
}
