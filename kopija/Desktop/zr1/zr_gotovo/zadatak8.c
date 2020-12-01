#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>
#include"GMRES.c"
#include"sor.c"

doublereal *A;
integer n=6;

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


int main() {
    doublereal 
        A[36]={11,-20,0,0,0,-2,-5,41,-3,0,-3,0,0,-15,7,-1,0,0,0,0,-4,2,-10,0,0,-6,0,-1,28,-15,-1,0,0,0,-15,47},
        b[6]={500,0,0,0,0,0}, *work, *h, *v0;
    integer i, iter, info; 

    v0=(doublereal*)calloc(n,sizeof(doublereal));

    integer restrt=n, ldw=n, ldh=restrt+1;

    work=(doublereal*)malloc(ldw*(restrt+4)*sizeof(doublereal));
    h=(doublereal*)malloc(ldh*(restrt+2)*sizeof(doublereal));
    
   
    doublereal omega=1.0, epsilon=1e-8;
    
    //Gauss-Seidel (SOR sa omega=1)
    iter=sor(A,n,b,v0,omega,epsilon); 
    printf("Gauss-Seidel\naproksimirano rješenje:\t");
    for (i=0; i<n; i++)
        printf("%lg ", v0[i]);
    printf("\n");
    printf("broj iteracija:\t %ld\n\n", iter);
    

    //SOR sa omega=1.35
    for (i=0;i<n; i++) v0[i]=0;
    omega=1.35;
    iter=sor(A,n,b,v0,omega,epsilon); 
    printf("SOR\naproksimirano rješenje:\t");
    for (i=0; i<n; i++)
        printf("%lg ", v0[i]);
    printf("\n");
    printf("broj iteracija:\t %ld\n\n", iter);
    
    //segmentation fault , linija 238 GMRES-a, nešto sa work i ldw
    //GMRES 
    iter=6;
    for (i=0;i<n; i++) v0[i]=0;
    gmres_(&n, b, v0, &restrt, work, &ldw, h, &ldh, &iter, &epsilon, matvec, psolve, &info);
    printf("GMRES\naproksimirano rješenje:\t");
    for (i=0; i<n; i++)
        printf("%lg ", v0[i]);
    printf("\n");
    printf("broj iteracija:\t %ld\n\n", iter);

    
    
return 0;
}
