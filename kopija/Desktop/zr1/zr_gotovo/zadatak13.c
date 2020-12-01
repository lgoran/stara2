#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>


int main () {
    integer n=4,i,j, n2=n*n, inc=1;
    doublereal M[16]={0};
    doublereal A[16]={0};
    doublereal K[16]={24,-9,-5,0,-9,22,-8,-5,-5,-8,25,-7,0,-5,-7,18};

    M[0]=2; M[1*n+1]=5; M[2*n+2]=3; M[3*n+3]=6; //kreiram M

    char jobz='V', uplo='U';
    doublereal w[n], work[3*n], X[16], U[16]={0}, V[16]={0};
    integer ldw=3*n, info;

    //racunam A iz M i K
    for(i=0; i<n; i++)
        for(j=0; j<n; j++) {
            A[j*n+i]=K[j*n+i]/sqrt(M[i*n+i]);
        }
    for(j=0; j<n; j++)
        for(i=0; i<n; i++) {
            A[j*n+i]=A[j*n+i]/sqrt(M[j*n+j]);
        }

    //prepisujem matricu A u matricu U
    dcopy_(&n2, A, &inc, U, &inc);

    dsyev_(&jobz, &uplo, &n, U, &n, w, work, &ldw, &info);

    for(i=0;i<n;i++)
        V[i*n+i]=w[i];

printf("Matrica A:\n");
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) 
            printf("%g\t", A[i+j*n]);
        printf("\n");}
printf("\n");printf("\n");printf("\n");
    
printf("Matrica V (matrica svojstvenih vrijednosti):\n");
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) 
            printf("%g\t", V[i+j*n]);
        printf("\n");}
printf("\n");printf("\n");printf("\n");

printf("Matrica U (matrica svojstvenih vektora):\n");
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) 
            printf("%g\t", U[i+j*n]);
        printf("\n");}
    
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            X[i*n+j] = pow(M[j*n+j], -0.5)*U[i*n+j];
    
    printf("\n");printf("\n");printf("4 slobodne oscilacije:\n\n");
    
    for(i=0; i<n; i++) {
        printf("x%ld:\n" ,i);
        for(j=0; j<n; j++) {
            printf("%g", X[i*n+j]);
            if(j==1) printf(" * e^%g * it", sqrt(w[i]));
            printf("\n");
        }
        printf("\n");
    }


    

return 0;
}
