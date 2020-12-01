#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>

doublereal S(doublereal *A, integer n){
    int i,j;
    doublereal s=0;

    for (i=0; i<n; i++)
        for(j=0; j<n; j++)
            if(i!=j)
                s += pow(A[j*n+i],2);
    s=sqrt(s);
    return s;
}

doublereal* jacobi_sd(integer n, doublereal *A, doublereal tol) {
    integer p,q,k,i;
    doublereal tau, t, c, s, app, apq, aqq, f, pom;
    doublereal *svojstvene_vrijednosti, *work;
    char _f='F';

    svojstvene_vrijednosti=(doublereal*)malloc(n*sizeof(doublereal)); 
    work=(doublereal*)malloc(n*sizeof(doublereal));


    f=dlange_(&_f, &n, &n, A, &n, work); //f=frob.norm(A)

    while(S(A,n) > tol*f) 
        for(p=0; p<n-1; p++) {
            for(q=p+1; q<n; q++){
                if(A[q*n+p] != 0) {
                    tau=(A[q*n+q]-A[p*n+p])/(2*A[q*n+p]);
                    t=(tau/abs(tau)) / (fabs(tau)+sqrt(1+pow(tau,2)));
                    c=1/(sqrt(1+pow(t,2)));
                    s=t*c;
                    app=A[p*n+p]; apq=A[q*n+p]; aqq=A[q*n+q];
                    app=app-t*apq;
                    aqq=aqq+t*apq;
                    for(k=0; k<n; k++) {
                        pom=A[p*n+k];
                        A[p*n+k]=c*pom-s*A[q*n+k];
                        A[q*n+k]=s*pom+c*A[q*n+k];
                        A[k*n+p]=A[p*n+k]; A[k*n+q]=A[q*n+k];
                    }
                    A[q*n+p]=0; A[p*n+q]=0;
                    A[p*n+p]=app; A[q*n+q]=aqq;
                }
            }
            for (int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    if(i!=j)
                        s += A[j*n+i] * A[j*n+i];
            s=sqrt(s);
            if(s<=tol*f)
                break;
        }


    for(i=0; i<n; i++)
        svojstvene_vrijednosti[i]=A[i*n+i];

    return svojstvene_vrijednosti;

}

int main() {
    doublereal *A, *B, *U, *tau, *work, *D, *pom, *svojstvene_vrijednosti;
    doublereal alpha=1, beta=0,  tol=4e-16;
    integer n=4,pet=5, n2=(n+1)*(n+1), lwork=n, info, i, j, idist=1, iseed[4]={10,20,30,77};
    char _n='n', _t='t', _L='L';

    A=(doublereal*)calloc(n*n,sizeof(doublereal));
    B=(doublereal*)calloc((n+1)*(n+1),sizeof(doublereal));
    U=(doublereal*)calloc(n*n,sizeof(doublereal));
    tau=(doublereal*)malloc(n*sizeof(doublereal));
    work=(doublereal*)malloc(lwork*sizeof(doublereal));
    D=(doublereal*)calloc(n*n,sizeof(doublereal));
    pom=(doublereal*)calloc(n*n,sizeof(doublereal));
    svojstvene_vrijednosti=(doublereal*)malloc(n*sizeof(doublereal));
    
    dlarnv_(&idist,iseed,&n2,B);
    dgeqrf_(&pet,&pet,B,&pet,tau,work,&pet,&info);
    dlacpy_(&_L,&n,&n,B,&n,U,&n);
    //U[0]=1; 
    //U[1*n+1]=1; 
    //U[2*n+2]=1; 
    //U[3*n+3]=1;
    //dorgqr_(&n, &n, &n, U, &n, tau, work, &lwork, &info);

    D[0]=-10; 
    D[1*n+1]=-5; 
    D[2*n+2]=0.1; 
    D[3*n+3]=0.2;

    //A=U*D*U'
    dgemm_(&_n, &_n, &n, &n, &n, &alpha, U, &n, D, &n, &beta, pom, &n);
    dgemm_(&_n, &_t, &n, &n, &n, &alpha, pom, &n, U, &n, &beta, A, &n);
    

    svojstvene_vrijednosti=jacobi_sd(n,A,tol);
    
    for (i=0; i<n; i++)
        printf("%g\t", svojstvene_vrijednosti[i]);
    printf("\n\n");

    //druga matrica
    printf("druga matrica\n");
    free(A);
    free(svojstvene_vrijednosti);
    n=10;
    A=(doublereal*)calloc(n*n, sizeof(doublereal));
    svojstvene_vrijednosti=(doublereal*)calloc(n, sizeof(doublereal));

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            A[j*n+i]=1./(19-2*i-2*j);

    tol=1e-15;
    svojstvene_vrijednosti=jacobi_sd(n,A,tol);
    
    for(i=0; i<n; i++)
        printf("%g\n", svojstvene_vrijednosti[i]);
    printf("\n");
    

    
    return 0;
}
