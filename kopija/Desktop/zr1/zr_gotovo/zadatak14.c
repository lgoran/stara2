#include<stdio.h>
#include<stdlib.h>
#include"f2c.h"
#include"fblaswr.h"
#include"clapack.h"
#include<math.h>


int main() {
    doublereal *W, *L, *D, *Ln, sum , alpha=-1, beta=0;
    integer n=7, i, j, n2=n*n, inc=1;
    char slovo_n='n';

    W=(doublereal*)calloc(n*n, sizeof(doublereal)); 
    D=(doublereal*)calloc(n*n, sizeof(doublereal));
    L=(doublereal*)calloc(n*n, sizeof(doublereal));
    Ln=(doublereal*)calloc(n*n, sizeof(doublereal));

//kreiram W
    W[0*n+1]=W[1*n]=2;
    W[0*n+2]=W[2*n]=3;
    W[0*n+3]=W[3*n]=4;

    W[1*n+3]=W[3*n+1]=7;
    W[1*n+4]=W[4*n+1]=1;

    W[2*n+3]=W[3*n+2]=3;
    W[2*n+5]=W[5*n+2]=2;
    W[2*n+6]=W[6*n+2]=1;

    W[4*n+5]=W[5*n+4]=7;
    W[4*n+6]=W[6*n+4]=3;

    W[5*n+6]=W[6*n+5]=5;

    printf("W:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            printf("%g\t", W[j*n+i]);
        printf("\n");}
    printf("\n");printf("\n");printf("\n");


//kreiram D
    for(i=0; i<n; i++) {
        sum=0;
        for(j=0; j<n; j++)
            sum+=W[j*n+i];
        D[i*n+i] = sum; L[i*n+i] = sum;
    }
    printf("D:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            printf("%g\t", D[j*n+i]);
        printf("\n");}

    printf("\n");printf("\n");printf("\n");

//kreiram L=D-W
    daxpy_(&n2, &alpha, W, &inc, L, &inc);
    printf("L:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            printf("%g\t", L[j*n+i]);
        printf("\n");}

    printf("\n");printf("\n");printf("\n");

//kreiram Ln
    dcopy_(&n2, L, &inc, Ln, &inc);

//Ln=D^-0.5 * L
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            Ln[i+j*n]=Ln[i+j*n]/sqrt(D[i*n+i]);
//Ln=Ln*D^-0.5
    for(i=0; i<n; i++) 
        for(j=0; j<n; j++)
            Ln[i*n+j]=Ln[i*n+j]/sqrt(D[i*n+i]);

    printf("Ln:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            printf("%g\t", Ln[j*n+i]);
        printf("\n");}

    printf("\n");printf("\n");printf("\n");


//racunanje Fielderovog vektora za L
    char jobz='V', range='I', uplo='U';
    doublereal vl, vu, abstol, *w, *z, *work;
    integer il=2, iu=2, lwork=(n*n+3)*n, *iwork, *ifail, info, m, *V1, *V2, v1=0, v2=0, br=0;
    abstol=1e-10;

    w=(doublereal*)calloc(n, sizeof(doublereal)); 
    z=(doublereal*)calloc(n*n, sizeof(doublereal));
    work=(doublereal*)calloc(lwork, sizeof(doublereal)); 
    iwork=(integer*)calloc(5*n, sizeof(integer));
    ifail=(integer*)calloc(n, sizeof(integer)); 
    V1=(integer*)calloc(n, sizeof(integer));
    V2=(integer*)calloc(n, sizeof(integer));

    dsyevx_(&jobz, &range, &uplo, &n, L, &n, &vl, &vu, &il, &iu, &abstol, &m, w, z, &n, work, &lwork, iwork, ifail, &info);

    printf("vektor u_2:\n");
    for(i=0; i<n; i++)
        printf("%g\n", z[i]);
    printf("\n");
    printf("lambda_2 = %g\n\n", w[0]);

    for(i=0; i<n; i++) {
        if(z[i]>=0) {V1[i]=1; v1++;}
        else {V2[i]=1; v2++;}
    }

    printf("V1={"); 
    for(i=0; i<n; i++) 
        if(V1[i]==1) {
            printf("%ld", i);
            br++;
            if(br!=v1) printf(", ");
        }
    printf("}\n");
    br=0;
    printf("V2={"); 
    for(i=0; i<n; i++) 
        if(V2[i]==1) {
            printf("%ld", i);
            br++;
            if(br!=v2) printf(", ");
        }
    printf("}\n\n\n"); 



//racunanje Fielderovog vektora za Ln
    
    dsyevx_(&jobz, &range, &uplo, &n, Ln, &n, &vl, &vu, &il, &iu, &abstol, &m, w, z, &n, work, &lwork, iwork, ifail, &info);

    printf("vektor u_N,2:\n");
    for(i=0; i<n; i++)
        printf("%g\n", z[i]);
    printf("\n");
    printf("lambda_N,2 = %g\n\n", w[0]);

    for(i=0; i<n; i++) {
        V1[i]=0; V2[i]=0;
    }
    br=0; v1=0; v2=0;

    for(i=0; i<n; i++) {
        if(z[i]>=0) {V1[i]=1; v1++;}
        else {V2[i]=1; v2++;}
    }

    printf("V1={"); 
    for(i=0; i<n; i++) 
        if(V1[i]==1) {
            printf("%ld", i);
            br++;
            if(br!=v1) printf(", ");
        }
    printf("}\n"); 
    br=0;
    printf("V2={"); 
    for(i=0; i<n; i++) 
        if(V2[i]==1) {
            printf("%ld", i);
            br++;
            if(br!=v2) printf(", ");
        }
    printf("}\n\n");


return 0;
}
