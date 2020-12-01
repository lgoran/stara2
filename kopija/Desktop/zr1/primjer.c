#include <stdio.h>
#include <stdlib.h>
#include "f2c.h"
#include "fblaswr.h"
#include "clapack.h"
#include "math.h"
#include <time.h>
#include <complex.h>

int main()
{
FILE *f;

integer i,j;
integer n=100;
doublecomplex *A;
A=malloc(n*n*sizeof(doublecomplex));

f=fopen("stieltjes_matr.txt","r");
for (i=0;i<n*n;i++)
{
fscanf(f,"%g",A+i);
}

char JOBVL='V';
doublecomplex *W;
W=malloc(n*sizeof(doublecomplex));
doublecomplex *vl, *vr;
vl=malloc(n*n*sizeof(doublecomplex));
vr=malloc(n*n*sizeof(doublecomplex));
integer lwork=2*n;
doublecomplex *work;
work=malloc(n*sizeof(doublecomplex));
doublereal *rwork;
rwork=malloc(2*n*sizeof(doublereal));
integer info;

clock_t start,end,total;
start=clock();
zgeev_(&JOBVL,&JOBVL,&n,A,&n,W,vl,&n,vr,&n,work,&lwork,rwork,&info);
end=clock();
total = (double)(end - start) / CLOCKS_PER_SEC;
printf("Total time = %ld",total);


return 0;
}
