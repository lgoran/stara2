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


void sor_rjesavac(doublereal *A, integer n, doublereal *b, doublereal *x0, doublereal omega, doublereal epsilon) {
  

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
            pom=pom-A[i*n+j]*x0[j];
        for(j=i+1;j<n;j++)
            pom=pom-A[i*n+j]*x0[j];
        x0[i]=x0[i]+pom*omega/A[i*n+i];
        }
        dcopy_(&n, b, &jedan, y, &jedan); //y=b
        dgemv_(&N, &n, &n, &minusjedan, A, &n, x0, &jedan, &alfa, y, &jedan); // -A*xo+y=y
     
        nrm=dnrm2_(&n, y, &jedan);
        
        kriterij = nrm/nrmb;
        
    }
    printf("potreban broj iteracija: %ld\n", k);
    free(y); 
    return;
}

int main(){

    FILE *f;
    doublereal *a, *b, *x, alfa=1, beta=0, omega, epsilon, *x0;
    integer i, n=100, jedan=1;
    char slovo='N';
    
    x0=calloc(n, sizeof(double));   
    omega=1.28;
    epsilon=1e-5;

    a=malloc(n*n*sizeof(doublereal));
    f=fopen("stieltjes_matr.txt", "r");
    
    for(i=0;i<n*n;i++)
        fscanf(f,"%lf", a+i);

    b=malloc(n*sizeof(doublereal));
    x=calloc(n,sizeof(doublereal));

    for(i=0; i<n; i++) 
        x[i]=1;
    
    dgemv_(&slovo, &n, &n, &alfa, a, &n, x, &jedan, &beta, b, &jedan);

    printf("izracunati b: \n");
    for(i=0;i<n;i++) printf("%g ", b[i]);
    printf("\n");

    sor_rjesavac(a, n, b, x0, omega, epsilon);

    printf("sor norma %g\n" , sor_norma(a, n, omega));

    printf("Aproksimirano rješenje sustava je: \n");
    for(i=0; i<n; i++)
        printf("%g ", x0[i]);
    printf("\n");
    fclose(f);

return 0;

}
