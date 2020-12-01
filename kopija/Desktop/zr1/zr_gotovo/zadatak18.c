#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>


int main () {

    integer n=21, n2=n*n, i, j, *jpvt, lwork=2*n+(n+1)*n, info, r, inc=1;
    doublereal *A, *x, *b, *tau, *work, tol=21e-16, *Z, *A1, *L1, *L, *R, *R11, *R12;
    
    A=(doublereal*)calloc(n*n, sizeof(doublereal));
    x=(doublereal*)calloc(n, sizeof(doublereal));
    b=(doublereal*)calloc(n, sizeof(doublereal));
    jpvt=(integer*)malloc(n*sizeof(integer));
    tau=(doublereal*)malloc(n*sizeof(doublereal));
    work=(doublereal*)malloc(lwork*sizeof(doublereal));
    Z=(doublereal*)calloc(n*n, sizeof(doublereal));
    A1=(doublereal*)calloc(n*n, sizeof(doublereal));
    L=(doublereal*)calloc(n*n, sizeof(doublereal));


    for(i=0; i<n; i++) 
        x[i]=-5+0.5*i;
    
    for(i=0; i<n; i++)
        for(j=0; j<n; j++) 
            A[j*n+i] = (1/250) * (x[i]*x[i]*x[j] - x[i]*x[i] - x[j]*x[j] + 175);

    b[0]=10;
    for(i=1; i<n; i++)
        b[i]=1;
//A1=A  
    dcopy_(&n2, A, &inc, A1, &inc);

//QR faktorizacija matrice A1
    dgeqp3_(&n, &n, A1, &n, jpvt, tau, work, &lwork, &info);

//tražim rang matrice A1 (r)
    for(i=0; i<n; i++) 
        if(A1[i*n+i]<tol)
            break;
    r=i;

    L1=(doublereal*)calloc(r*r,sizeof(doublereal));
    R11=(doublereal*)calloc(r*r,sizeof(doublereal));
    R12=(doublereal*)calloc((n-r)*r, sizeof(doublereal));
    R=(doublereal*)calloc(n*r, sizeof(doublereal));//R je nxr matrica

//treba mi prvi rxr blok matrice R -> R1
    for(i=0; i<r; i++)
        for(j=i; j<r; j++)
            R11[i*n+j]=A1[i*n+j];
//trazim R12
    for(i=0; i<r; i++)
        for(j=i; j<r; j++)
            R12[i+n*j]=A1[i+n*(j+r)];

//racunam R

//L=A  
    dcopy_(&n2, A, &inc, L, &inc);

//LQ faktorizacija matrice A(L)
    dgelqf_(&n, &n, A, &n, tau, work, &lwork, &info);

//prebacujem elemente ispod dijagonale iznad dijagonale u L i brišem one ispod
    for(i=0; i<n; i++)
        for(j=i+1; j<n; j++) {
            L[j*n+i]=L[i*n+j];
            L[i*n+j]=0;
        }
//L je sada gornjetrokutasta matrica, treba mi njezin prvi rxr blok
    for(i=0; i<r; i++)
        for(j=0; j<r; j++)
            L1[i*n+j]=L[i*n+j];
//L1 je sada prvi rxr blok matrice L




return 0;
}

















