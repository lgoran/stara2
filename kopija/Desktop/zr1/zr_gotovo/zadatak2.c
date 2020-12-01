#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include"math.h"

doublereal sor_norma(doublereal *A, integer n, doublereal omega) {
    doublereal *R, *L, alpha=1, *work;
    char l='L', u='U', slovon='n', f='F'; 
    integer i, j;    

    R = (doublereal*)calloc(n*n, sizeof(doublereal));
    L = (doublereal*)calloc(n*n, sizeof(doublereal));
    work=(doublereal*)malloc(n*sizeof(doublereal));

    dlacpy_(&l, &n, &n, A, &n, L, &n);
    dlacpy_(&u, &n, &n, A, &n, R, &n);
    
    
    for(i=0; i<n; i++)
        for(j=i; j<n; j++) {
            if(j==i) R[j*n+i] = (1-omega)*R[j*n+i];
            else  R[j*n+i] = -omega*R[j*n+i];
        }
 
    for(i=0; i<n; i++) 
        for(j=1; j<i; j++) 
            L[j*n+i] = omega*L[j*n+i];
    
    dtrsm_(&l, &l, &slovon, &slovon, &n, &n, &alpha, L, &n, R, &n);
   

    free(L); 
    
    return dlange_(&f, &n, &n, R, &n, work);    
    
}

integer sor_konvergencija (doublereal *A, integer n, doublereal omega) {

    if (sor_norma(A, n, omega) < 1)        
        return 1;
    
    return 0;

}

void sor_rjesavac(doublereal *A, integer n, doublereal *b, doublereal *x0, doublereal omega, doublereal epsilon) {
    if(sor_konvergencija(A, n, omega) == 0) {printf("sor ne konvergira\n");return;}        
   
    int k, i, j, l, jedan=1;
    doublereal pom, *X, snorma, *x1, kr, v;

    X = (doublereal*)malloc(n*sizeof(doublereal));
    x1 = (doublereal*)malloc(n*sizeof(doublereal));

    for(i=0;i<n;i++) {
        x0[i] = (1-omega)*x0[i];
        pom=b[i];
        for(j=0;j<i;j++)
            pom=pom-A[j*n+i]*x0[j];
        for(j=i+1;j<n;j++)
            pom=pom-A[j*n+i]*x0[j];
        x0[i]=x0[i]+pom*omega/A[i*n+i];
    }
    for(i=0; i<n; i++)
        X[i]=x1[i]-x0[i];
    for(l=0; l<n; l++)
        x1[l]=x0[l];
    
    v=dnrm2_(&n, X, &jedan);

    snorma=sor_norma(A, n, omega);


    kr = (log(epsilon*(1-snorma))-log(v))/log(snorma);
    k = ceil(kr);
    printf("potreban broj iteracija: %d\n", k);

    for(l=0; l<k; l++) {
        for(i=0;i<n;i++) {
        x0[i] = (1-omega)*x0[i];
        pom=b[i];
        for(j=0;j<i;j++)
            pom=pom-A[j*n+i]*x0[j];
        for(j=i+1;j<n;j++)
            pom=pom-A[j*n+i]*x0[j];
        x0[i]=x0[i]+pom*omega/A[i*n+i];
        }
    }

    free(X); free(x1);
    return;
}



int main() {

    doublereal omega, epsilon, alfa=1, beta=0, pom, norma=0;
    integer n, i, j, k, l, jedan=1, N, broj;
    char slovo = 'N';
    n=4;
    N=n*n;
  

    doublereal A[16]={101, -4, 8, 12, -4, 20, -7, 3, 8, -7, 78, 32, 12, 3, 32, 113};
    doublereal b[4]={117, 12, 111, 160};
    doublereal x0[4]={0, 0, 0, 0};
    omega=1.05;
    epsilon=1e-5;
    
    sor_rjesavac(A, n, b, x0, omega, epsilon);
    printf("sor norma %g\n" , sor_norma(A, n, omega));
    printf("Aproksimirano rješenje sustava je: \n");
    for(l=0; l<n; l++)
        printf("%g ", x0[l]);
    printf("\n");

return 0;


    

}



















