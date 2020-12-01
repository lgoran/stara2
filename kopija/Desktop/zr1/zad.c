#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>

void ic (integer n, doublereal *a){
    int i,j,k;
    for (i=0; i<n; i++){
        for (k=0; k<i; k++)
            a[i+i*n]-=a[k+i*n]*a[k+i*n];
        a[i+i*n]=sqrt(a[i+i*n]);
        for (j=i+1; j<n; j++){
            if (a[i+j*n]!=0){
                for (k=0; k<i; k++)
                    a[i+j*n]-=a[k+i*n]*a[k+j*n];
                a[i+j*n]/=a[i+i*n];
            }
            
        }
    }
}
void pcg(integer n, doublereal *A, doublereal *b, doublereal *x, doublereal tol) {
    doublereal *p, *r, *s, *e, *d ,*Ad, *R;
    doublereal normab, alfa, beta, beta_novi, rez_trans_p, rez_trans_p_novi;
    doublereal _neg1=-1, _0=0, _1=1, rezidual=tol+1;
    integer inc=1, n2=n*n, i, k=0;
    char _l='L', _n='N', _t='T', _u='U';
    normab=dnrm2_(&n, b, &inc);
       
    p=(doublereal*)malloc(n*sizeof(doublereal));
    r=(doublereal*)malloc(n*sizeof(doublereal));
    s=(doublereal*)malloc(n*sizeof(doublereal));
    e=(doublereal*)malloc(n*sizeof(doublereal));
    d=(doublereal*)malloc(n*sizeof(doublereal));
    Ad=(doublereal*)malloc(n*sizeof(doublereal));
    R=(doublereal*)malloc(n*n*sizeof(doublereal));

    //dcopy desni=lijevi
    dcopy_(&n, b, &inc, r, &inc);
    dgemv_(&_n, &n, &n, &_neg1, A, &n, x, &inc, &_1, r, &inc); //r=r-Ax0 
    dcopy_(&n2, A, &inc, R, &inc);
    dcopy_(&n, r, &inc, s, &inc);
  
    ic(n, R);
    dtrsv_(&_u, &_t, &_n, &n, R, &n, s, &inc);
    dcopy_(&n, s, &inc, p, &inc);
    dtrsv_(&_u, &_n, &_n, &n, R, &n, p, &inc);
    dcopy_(&n, p, &inc, d, &inc); 

    rez_trans_p=ddot_(&n, r, &inc, p, &inc);
    
    while(rezidual>tol) {
        
        dgemv_(&_n, &n, &n, &_1, A, &n, d, &inc, &_0, Ad, &inc);
        alfa=rez_trans_p/(ddot_(&n, d, &inc, Ad, &inc));
        daxpy_(&n, &alfa, d, &inc, x, &inc);
        alfa=-alfa;
        daxpy_(&n, &alfa, Ad, &inc, r, &inc);
        dcopy_(&n, r, &inc, p, &inc);


        dtrsv_(&_u, &_t, &_n, &n, R, &n, p, &inc);
        dtrsv_(&_u, &_n, &_n, &n, R, &n, p, &inc);
        rez_trans_p_novi=ddot_(&n, r, &inc, p, &inc); 
        beta=rez_trans_p_novi/rez_trans_p;
        beta_novi=1/beta;
        daxpy_(&n, &beta_novi, p, &inc, d, &inc);
        dscal_(&n, &beta, d, &inc);
        k++;
        rez_trans_p=rez_trans_p_novi;

        
        dcopy_(&n, b, &inc, e, &inc);
        dgemv_(&_n, &n, &n, &_neg1, A, &n, x, &inc, &_1, e, &inc);
        rezidual=dnrm2_(&n, e, &inc)/normab;
        
    }
    printf("broj iteracija: %ld\n", k);
    free(e); free(d); free(r); free(Ad); free(R); free(p);
}

int main(){

    FILE *f;
    doublereal *a, *b, *x, alfa=1, beta=0, omega, epsilon, *x0, tol=1e-8, *pom;
    integer i, n=100, _1=1, n2=n*n, k;
    char slovo='N';
    
    x0=calloc(n, sizeof(double));   
    omega=1.28;
    epsilon=1e-5;

    a=malloc(n*n*sizeof(doublereal));
    f=fopen("stieltjes_matr.txt", "r");
    
    for(i=0;i<n*n;i++)
        fscanf(f,"%lf", a+i);
    
    pom=malloc(n*n*sizeof(doublereal));

    dcopy_(&n2, a, &_1, pom, &_1);

    b=malloc(n*sizeof(doublereal));
    x=calloc(n,sizeof(doublereal));

    for(i=0; i<n; i++) 
        x[i]=1;
    
    dgemv_(&slovo, &n, &n, &alfa, a, &n, x, &_1, &beta, b, &_1);

    for(i=0; i<n; i++) 
        x0[i]=0;

    pcg(n, a, b, x0, tol);
    printf("Aproksimirano rješenje: \n");
    for(i=0; i<n; i++)
        printf("%g ", x0[i]);
    printf("\n");

    fclose(f);
    return 0;
}