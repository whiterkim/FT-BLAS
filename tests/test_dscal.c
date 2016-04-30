#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern	void	xdscal_(	const int*n,	const double*alpha,	double *f_x,			const int*incx);

// C
void c_dscal(const int n, const double alpha, double *x, const int incx)
{
	register int i;
	
	if(incx == 1)
	{
		for(i = 0; i < n; ++i)
			x[i] *= alpha;
	}

	
}

// Fortran C
void ftc_dscal(const int n, const double alpha, double *x, const int incx)
{
	register int i;
	
	if(incx == 1)
	{
		register double xi;
		for(i = 0; i < n; ++i)
		{
			xi = x[i];
			x[i] = xi * alpha;
		}
	}
	
}

// Fortran 
void f_dscal(int n, double alpha, double *x, int incx)
{
	xdscal_(&n,&alpha,x,&incx);
}

int N, incx, incy;
double alpha;
double *x, *t;

struct timespec begin, end;
unsigned long long int acml_time()
{
	memset(x,0,sizeof(double)*N);
	memcpy(x,t,sizeof(double)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	dscal(N,alpha,x,incx);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}

unsigned long long int c_time()
{

	memset(x,0,sizeof(double)*N);
	memcpy(x,t,sizeof(double)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	c_dscal(N,alpha,x,incx);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}


unsigned long long int f_time()
{
	memset(x,0,sizeof(double)*N);
	memcpy(x,t,sizeof(double)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	f_dscal(N,alpha,x,incx);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}

unsigned long long int ftc_time()
{
	memset(x,0,sizeof(double)*N);
	memcpy(x,t,sizeof(double)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	ftc_dscal(N,alpha,x,incx);
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

	alpha = rand()/1.0/RAND_MAX - 0.5;
    	x = (double*)malloc(sizeof(double)*N);
    	t = (double*)malloc(sizeof(double)*N);
	
	int i;
    	for (i = 0; i < N; i++)
       		t[i] = rand()/1.0/RAND_MAX - 0.5;
	
        int c = 8, ic, it = 0;
	
	printf("Running test for DSCAL with N = %d, alpha = %d\n", N, alpha);
        printf("%32s%32s%32s%32s\n","ACML","C","FORTRAN C", "FORTRAN");
	printf("Trials\n");
	printf("%32s%32s%32s%32s\n", "Time (ns)", "Time (ns)", "Time (ns)", "Time (ns)");

        unsigned long long int tot1 = 0, tot2 = 0, tot3 = 0, tot4 = 0;
        for (ic = 0; ic < c; ic++)
        {
                unsigned long long int t1, t2, t3, t4;
                t1 = acml_time();
                t2 = c_time();


                if (ic >= 2)
                {
                        tot1 += t1;
                        tot2 += t2;
                        tot3 += t3;
			tot4 += t4;
                        it ++;
                }
                printf("\n");
        }
        
	printf("Average\n");
        printf("%32llu%32llu%32llu%32llu\n",tot1/it,tot2/it,tot3/it,tot4/it);
    
	return 0;
}
