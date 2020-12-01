#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "f2c.h"
#include "fblaswr.h"
#include "clapack.h"

integer cg ( integer n, doublereal* A, doublereal* b, doublereal* x0, doublereal tol ) {
 }

int main () {
char side='',trans='';
integer n=100,n2=10000, i,jedan=1,iseed[4]={55,631,3574,33}, info;
doublereal *A, *b, *x0, *D, *pom1, *work, *tau;
//printf("n=\n"); scanf("%ld", &n);
A=(doublereal*)malloc(n*n*sizeof(doublereal));
D=(doublereal*)malloc(n*n*sizeof(doublereal));
pom1=(doublereal*)malloc(n*n*sizeof(doublereal));
work=(doublereal*)malloc(n*n*sizeof(doublereal));
tau=(doublereal*)malloc(n*sizeof(doublereal));
b=(doublereal*)malloc(n*sizeof(doublereal));
x0=(doublereal*)malloc(n*sizeof(doublereal));
for(i=0;i<n;i++) x0[i]=0;
for(i=0;i<n;i++) D[n*i+i]=(i+1)*(i+1);
dlarnv_(&jedan, iseed, &n2, pom1);
dgeqrf_(&n, &n, pom1, &n, tau, work, &n2, &info);
dormqr_(&side, &trans, &n, &n, &n, pom1, &n, tau, c, &n, work, &n2, &info); //neznam sto je side trans c!!!
}
