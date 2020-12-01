#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>


//nekompletna faktorizacija Choleskog
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

integer cg(integer n, doublereal *A, doublereal *b, doublereal *x, doublereal tol) {
    doublereal *e, *d, *r, alpha, beta, beta1, rezidual=tol+1, *Ad, *ad, jedan=1, nula=0, minusjedan=-1, rk, rk1, nrmb;
    integer k=0, inc=1, i;
    char slovon='n';

    e=(doublereal*)malloc(n*sizeof(doublereal));
    d=(doublereal*)malloc(n*sizeof(doublereal));
    r=(doublereal*)malloc(n*sizeof(doublereal));
    Ad=(doublereal*)malloc(n*sizeof(doublereal));

    nrmb=dnrm2_(&n, b, &inc);
    dcopy_(&n, b, &inc, e, &inc); //e=b
    dcopy_(&n, b, &inc, r, &inc); //r=b
    dgemv_(&slovon, &n, &n, &minusjedan, A, &n, x, &inc, &jedan, r, &inc); //r=r-Ax
    dcopy_(&n, r, &inc, d, &inc); //d=r
    
    while(rezidual>tol) {
        
        dgemv_(&slovon, &n, &n, &jedan, A, &n, d, &inc, &nula, Ad, &inc); //Ad=A*d
        rk=ddot_(&n, r, &inc, r, &inc); //rk=rkt*rk
        alpha=rk/(ddot_(&n, d, &inc, Ad, &inc)); //alpha=...
        daxpy_(&n, &alpha, d, &inc, x, &inc); //x=x+alpha*d
        alpha=-alpha;
        daxpy_(&n, &alpha, Ad, &inc, r, &inc); //r=r-alpha*Ad
        rk1=ddot_(&n, r, &inc, r, &inc); 
        beta=rk1/rk;
        beta1=1/beta;
        daxpy_(&n, &beta1, r, &inc, d, &inc);//d=d+beta1*r /puta beta
        dscal_(&n, &beta, d, &inc); //d=beta*d+r
        k++;

        dcopy_(&n, b, &inc, e, &inc); //e=b
        dgemv_(&slovon, &n, &n, &minusjedan, A, &n, x, &inc, &jedan, e, &inc); //e=b-Ax
        rezidual=dnrm2_(&n, e, &inc)/nrmb;
        
    }
    
    free(e); free(d); free(r); free(Ad);
    return k;
}

integer pcg(integer n, doublereal *A, doublereal *b, doublereal *x, doublereal tol) {
    doublereal *r, *p, *e, *d, alpha, beta, rp, rp1, nrmb, *Ad, *R, minusjedan=-1, nula=0, jedan=1, beta1, rezidual=tol+1;
    integer inc=1, k, i, n2=n*n;
    char slovoN='N', slovoT='T', slovoL='L', slovoU='U';
  
    R=(doublereal*)malloc(n*n*sizeof(doublereal));
    r=(doublereal*)malloc(n*sizeof(doublereal));
    Ad=(doublereal*)malloc(n*sizeof(doublereal));
    p=(doublereal*)malloc(n*sizeof(doublereal));
    d=(doublereal*)malloc(n*sizeof(doublereal));
    e=(doublereal*)malloc(n*sizeof(doublereal));

    nrmb=dnrm2_(&n, b, &inc);

    dcopy_(&n, b, &inc, r, &inc); //r=b
    dgemv_(&slovoN, &n, &n, &minusjedan, A, &n, x, &inc, &jedan, r, &inc); //r=-Ax0+r    
    dcopy_(&n2, A, &inc, R, &inc); //R=A
    dcopy_(&n, r, &inc, p, &inc); //p=r
  
    //rješavanje sustava Mp=r    
        ic(n, R); //R je iz faktorizacije Choleskog
        dtrsv_(&slovoU, &slovoT, &slovoN, &n, R, &n, p, &inc); //(R^t)*p=r, našli smo p
        dtrsv_(&slovoU, &slovoN, &slovoN, &n, R, &n, p, &inc); // Rs=p, našli smo s i to spremili u p
    dcopy_(&n, p, &inc, d, &inc); //d=p
    k=0;
   
   /* printf("OVO JE R: \n");
    for(i=0;i<n*n;i++) { printf("%g ", R[i]); if((i+1)%n==0) printf("\n"); }
    printf("\n");*/

    rp=ddot_(&n, r, &inc, p, &inc);//rp=r*p
    
    while(rezidual>tol) {
        
        dgemv_(&slovoN, &n, &n, &jedan, A, &n, d, &inc, &nula, Ad, &inc); //Ad=A*d
        alpha=rp/(ddot_(&n, d, &inc, Ad, &inc)); //alpha=...
        daxpy_(&n, &alpha, d, &inc, x, &inc); //x=x+alpha*d
        alpha=-alpha;
        daxpy_(&n, &alpha, Ad, &inc, r, &inc); //r=r-alpha*Ad
        dcopy_(&n, r, &inc, p, &inc); //p=r
        //RJEŠAVANJE SUSTAVA Mp=r:   
            dtrsv_(&slovoU, &slovoT, &slovoN, &n, R, &n, p, &inc); //(R^t)*p=r, našli smo p
            dtrsv_(&slovoU, &slovoN, &slovoN, &n, R, &n, p, &inc); // Rs=p, našli smo s i to spremili u p
        rp1=ddot_(&n, r, &inc, p, &inc); 
        beta=rp1/rp;
        beta1=1/beta;
        daxpy_(&n, &beta1, p, &inc, d, &inc);//d=d+beta1*p /puta beta
        dscal_(&n, &beta, d, &inc); //d=beta*d+p
        k++;
        rp=rp1;
        
        dcopy_(&n, b, &inc, e, &inc); //e=b
        dgemv_(&slovoN, &n, &n, &minusjedan, A, &n, x, &inc, &jedan, e, &inc); //e=b-Ax
        rezidual=dnrm2_(&n, e, &inc)/nrmb;
        
    }
   
    free(e); free(d); free(r); free(Ad); free(R); free(p);
   return k; 
}

integer dcg(integer n, doublereal *A, doublereal *b, doublereal *x, doublereal tol) {
    doublereal *r, *p, *e, *d, alpha, beta, rp, rp1, nrmb, *Ad, *M, minusjedan=-1, nula=0, jedan=1, beta1, rezidual=tol+1;
    integer inc=1, k, i, n2=n*n;
    char slovoN='N', slovoT='T', slovoL='L', slovoU='U';
  
    M=(doublereal*)calloc(n*n,sizeof(doublereal));
    r=(doublereal*)malloc(n*sizeof(doublereal));
    Ad=(doublereal*)malloc(n*sizeof(doublereal));
    p=(doublereal*)malloc(n*sizeof(doublereal));
    d=(doublereal*)malloc(n*sizeof(doublereal));
    e=(doublereal*)malloc(n*sizeof(doublereal));

    nrmb=dnrm2_(&n, b, &inc);

    dcopy_(&n, b, &inc, r, &inc); //r=b
    dgemv_(&slovoN, &n, &n, &minusjedan, A, &n, x, &inc, &jedan, r, &inc); //r=-Ax0+r    
     //rješavanje sustava Mp=r       
    for(i=0;i<n;i++) p[i]=r[i]/A[i*n+i]; //M=diag(A) pa je pi=ri/aii
    dcopy_(&n, p, &inc, d, &inc); //d=p
    k=0;
   
   /* printf("OVO JE R: \n");
    for(i=0;i<n*n;i++) { printf("%g ", R[i]); if((i+1)%n==0) printf("\n"); }
    printf("\n");*/

    rp=ddot_(&n, r, &inc, p, &inc);//rp=r*p
    
    while(rezidual>tol) {
        
        dgemv_(&slovoN, &n, &n, &jedan, A, &n, d, &inc, &nula, Ad, &inc); //Ad=A*d
        alpha=rp/(ddot_(&n, d, &inc, Ad, &inc)); //alpha=...
        daxpy_(&n, &alpha, d, &inc, x, &inc); //x=x+alpha*d
        alpha=-alpha;
        daxpy_(&n, &alpha, Ad, &inc, r, &inc); //r=r-alpha*Ad
        //RJEŠAVANJE SUSTAVA Mp=r:   
        for(i=0;i<n;i++) p[i]=r[i]/A[i*n+i];
        rp1=ddot_(&n, r, &inc, p, &inc); 
        beta=rp1/rp;
        beta1=1/beta;
        daxpy_(&n, &beta1, p, &inc, d, &inc);//d=d+beta1*p /puta beta
        dscal_(&n, &beta, d, &inc); //d=beta*d+p
        k++;
        rp=rp1;
        
        dcopy_(&n, b, &inc, e, &inc); //e=b
        dgemv_(&slovoN, &n, &n, &minusjedan, A, &n, x, &inc, &jedan, e, &inc); //e=b-Ax
        rezidual=dnrm2_(&n, e, &inc)/nrmb;
        
    }
   
    free(e); free(d); free(r); free(Ad); free(M); free(p);
   return k; 
}

int main(){

    FILE *f;
    doublereal *a, *b, *x, alfa=1, beta=0, omega, epsilon, *x0, tol=1e-8, *pom;
    integer i, n=100, jedan=1, n2=n*n, k;
    char slovo='N';
    
    x0=calloc(n, sizeof(double));   
    omega=1.28;
    epsilon=1e-5;

    a=malloc(n*n*sizeof(doublereal));
    f=fopen("stieltjes_matr.txt", "r");
    
    for(i=0;i<n*n;i++)
        fscanf(f,"%lf", a+i);
    
    pom=malloc(n*n*sizeof(doublereal));

    dcopy_(&n2, a, &jedan, pom, &jedan);

    b=malloc(n*sizeof(doublereal));
    x=calloc(n,sizeof(doublereal));

    for(i=0; i<n; i++) 
        x[i]=1;
    
    dgemv_(&slovo, &n, &n, &alfa, a, &n, x, &jedan, &beta, b, &jedan);

    /*printf("izracunati b: \n");
    for(i=0;i<n;i++) printf("%g ", b[i]);
    printf("\n");*/

    k=cg(n, a, b, x0, tol);
    printf("neprekondicionirani sustav\n");
    printf("potreban broj iteracija: %ld\n", k);
    printf("Aproksimirano rješenje: \n");
    for(i=0; i<n; i++)
        printf("%g ", x0[i]);
    printf("\n");
    
    dcopy_(&n2, pom, &jedan, a, &jedan);
    for(i=0; i<n; i++) 
        x0[i]=0;

    k=dcg(n, a, b, x0, tol);
    printf("dijagonalno prekondicionirani sustav\n");
    printf("potreban broj iteracija: %ld\n", k);
    printf("Aproksimirano rješenje: \n");
    for(i=0; i<n; i++)
        printf("%g ", x0[i]);
    printf("\n");

    dcopy_(&n2, pom, &jedan, a, &jedan);
    for(i=0; i<n; i++) 
        x0[i]=0;

    k=pcg(n, a, b, x0, tol);
    printf("IC prekondicionirani sustav\n");
    printf("potreban broj iteracija: %ld\n", k);
    printf("Aproksimirano rješenje: \n");
    for(i=0; i<n; i++)
        printf("%g ", x0[i]);
    printf("\n");


fclose(f);

return 0;

}

/*napomene: 
    -inverzM dobro aproksimira inverzA (ako pise A(-1)Ax imamo IAx tj Ax i nismo puno promijenili
    -slajd 55: imamo M^-1 = R^-1 * R^-t --> M^-1 * A = R^-1 * R^-t * A
        pomnozimo s R s lijeva, i s R#-1 s desna (transformacija slicnosti, ne mijenja svojstvene vrijednosti)
        dobili smo matricu sličnu polaznoj koja je simetricna (?)
        Ax=b pomnozimo s lijeva s R^-t , oznacimo y=Rx, imamo sustav .... ne znam
        

*/
