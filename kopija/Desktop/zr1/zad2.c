#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>


int main () {
    integer n=4,i,j, n2=n*n, inc=1;   
    doublereal *M, *M_na_minus_pola, *A, K[16]={24,-9,-5,0,-9,22,-8,-5,-5,-8,25,-7,0,-5,-7,18};
    doublereal *w,*work,*X,*U;

    M=(doublereal*)calloc(n*n, sizeof(doublereal));
    M_na_minus_pola=(doublereal*)calloc(n*n, sizeof(doublereal));
    A=(doublereal*)calloc(n*n, sizeof(doublereal));
    w=(doublereal*)malloc(n * sizeof(doublereal));
    work=(doublereal*)malloc(n*8* sizeof(doublereal));
    X=(doublereal*)malloc(n*n* sizeof(doublereal));
    U=(doublereal*)malloc(n*n* sizeof(doublereal));

    M[0]=2; 
    M[1*n+1]=5; 
    M[2*n+2]=3; 
    M[3*n+3]=6;

    M_na_minus_pola[0]=1./sqrt(2); 
    M_na_minus_pola[1*n+1]=1./sqrt(5); 
    M_na_minus_pola[2*n+2]=1./sqrt(3); 
    M_na_minus_pola[3*n+3]=1./sqrt(6);

    char jobz='V', uplo='U';
    integer ldw=8*n, info;

    //racunam A iz M i K
    for(i=0; i<n; i++)
        for(j=0; j<n; j++) {
            A[j*n+i]=K[j*n+i]*M_na_minus_pola[i*n+i];
        }
    for(j=0; j<n; j++)
        for(i=0; i<n; i++) {
            A[j*n+i]=A[j*n+i]*M_na_minus_pola[j*n+j];
        }

    dcopy_(&n2, A, &inc, U, &inc);

    dsyev_(&jobz, &uplo, &n, U, &n, w, work, &ldw, &info);

    printf("Matrica A\n");
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) 
            printf("%g ", A[i+j*n]);
        printf("\n");}
    printf("\n\n");
    
    printf("svojstvene vrijednosti:\n");
    for(i=0; i<n; i++)
        printf("%g ", w[i]);
    printf("\n\n");

    printf("Matrica U\n");
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) 
            printf("%g ", U[i+j*n]);
        printf("\n");}
    printf("\n\n");
    
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            X[i*n+j] = M_na_minus_pola[j*n+j]*U[i*n+j];
    
    
    for(i=0; i<n; i++) {
        printf("%ld. slobodna oscilacija ",i+1);
        printf(" * e^(%git)", sqrt(w[i]));
        printf("\n");
        for(j=0; j<n; j++) {
            printf("%g", X[i*n+j]);
            printf("\n");
        }
        printf("\n");
    }


    

return 0;
}
