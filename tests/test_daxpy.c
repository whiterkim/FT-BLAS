#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern	void	xdaxpy_(	const int*n, const double *alpha, double *f_x, const int*incx, double *f_y, const int* incy);

// C
void c_daxpy(const int n, const double alpha, double *x, const int incx, double *y, const int incy)
{
	register int i;
	
	if(incx == 1 && incy == 1)
	{
		for(i = 0; i < n; ++i) 
		{
			y[i] = y[i] + alpha*x[i];
		}
	}

	
}


// Fortran 
void f_daxpy(int n, double alpha, double *x, int incx, double *y, int incy)
{
	xdaxpy_(&n,&alpha,x,&incx,y,&incy);
}

int N, incx, incy;
double alpha;
double *x,*y, *t_y;

struct timespec begin, end;
unsigned long long int acml_time()
{
	memset(x,0,sizeof(double)*N);
	memset(y,0,sizeof(double)*N);
	memcpy(y,t_y,sizeof(double)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	daxpy(N,alpha,x,incx,y,incy);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}

unsigned long long int c_time()
{

	memset(x,0,sizeof(double)*N);
	memset(y,0,sizeof(double)*N);
	memcpy(y,t_y,sizeof(double)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	c_daxpy(N,alpha, x,incx,y,incy);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}


unsigned long long int f_time()
{
	memset(x,0,sizeof(double)*N);
	memset(y,0,sizeof(double)*N);
	memcpy(y,t_y,sizeof(double)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	f_daxpy(N,alpha,x,incx,y,incy);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}

int main(int argc, char *argv[])
{
	init_();    
	srand(time(NULL));
   	
	N = atoi(argv[1]);
    	incx = 1;
	incy = 1;

	alpha = rand()/1.0/RAND_MAX - 0.5;
    	x = (double*)malloc(sizeof(double)*N);
    	y = (double*)malloc(sizeof(double)*N);
    	t_y = (double*)malloc(sizeof(double)*N);
	
	int i;
    	for (i = 0; i < N; i++) {
       		x[i] = rand()/1.0/RAND_MAX - 0.5;
       		t_y[i] = rand()/1.0/RAND_MAX - 0.5;
	}
	
        int c = 8, ic, it = 0;
	
	printf("Running test for DAXPY with N = %d, alpha = %d\n", N, alpha);
        printf("%32s%32s%32s\n","ACML","C", "FORTRAN");
	printf("Trials\n");
	printf("%32s%32s%32s\n", "Time (ns)", "Time (ns)", "Time (ns)");

        unsigned long long int tot1 = 0, tot2 = 0, tot3 = 0;
        for (ic = 0; ic < c; ic++)
        {
               unsigned long long int t1, t2, t3;
                t1 = acml_time();
                t2 = c_time();
		t3 = f_time();

                if (ic >= 2)
                {
                        tot1 += t1;
                        tot2 += t2;
                        tot3 += t3;
                        it ++;
                }
                printf("\n");
        }
        
	printf("Average\n");
        printf("%32llu%32llu%32llu\n",tot1/it,tot2/it,tot3/it);
    
	return 0;
}
