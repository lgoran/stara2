#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "f2c.h"
#include "fblaswr.h"
#include "clapack.h"

int main() {
    int i, j, n, n2;
    scanf("%d", &n);
    double *A, *X;
    int iseed[4]={2, 1357, 125, 27};
    n2=n*n;
    
    X=malloc(n*sizeof(double));
    A=malloc(n2*sizeof(double));

    dlarnv_(1, iseed, &n, X); 
    dlarnv_(1, iseed, &n2, A);
  
        


return 0;
  

}
