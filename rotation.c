#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "ftblas.h"
//#include "complex.h"

int n, incx, incy, i;
float *x, *y, *tx, *ty;
float c, s;

int main(int argc, char *argv[])
{
	init_();
    n = atoi(argv[1]);
    incx = 1;
    incy = 1;

	//srand(time(NULL));

    x = (float*)malloc(sizeof(float)*n);
    y = (float*)malloc(sizeof(float)*n);

    for (i = 0; i < n; i++)
    {
        x[i] = rand()/1.0/RAND_MAX - 0.5;
        y[i] = rand()/1.0/RAND_MAX - 0.5;
    }
	c = rand()/1.0/RAND_MAX - 0.5;
    s = rand()/1.0/RAND_MAX - 0.5;
    srot(n,x,incx,y,incy,c,s);
    for (i = 0; i < n; i++) printf("%20.10f\n",x[i]); printf("\n");
    for (i = 0; i < n; i++) printf("%20.10f\n",y[i]); printf("\n");

    
	return 0;
}
