#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>

integer sor(doublereal *A, integer n, doublereal *b, doublereal *x0, doublereal omega, doublereal epsilon) {
  
    integer k=0, i, j, l, jedan=1;
    doublereal pom, minusjedan=-1, alfa=1, beta=0, *y, kriterij = epsilon+1, nrmb, nrm;
    char N='n';

    y = (doublereal*)malloc(n*sizeof(doublereal));

    nrmb=dnrm2_(&n, b, &jedan);

    while(kriterij > epsilon) {
        k++;
        for(i=0;i<n;i++) {
        x0[i] = (1-omega)*x0[i];
        pom=b[i];
        for(j=0;j<i;j++)
            pom=pom-A[j*n+i]*x0[j];
        for(j=i+1;j<n;j++)
            pom=pom-A[j*n+i]*x0[j];
        x0[i]=x0[i]+pom*omega/A[i*n+i];       
}
        dgemv_(&N, &n, &n, &alfa, A, &n, x0, &jedan, &beta, y, &jedan); //y=A*x0
        daxpy_(&n, &minusjedan, b, &jedan, y, &jedan); //y=b-A*x0
     
        nrm=dnrm2_(&n, y, &jedan);   
        kriterij = nrm/nrmb;   
             
    }

    free(y); 
    return k;
}
