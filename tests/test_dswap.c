#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern	void	xdswap_(	const int*n,						double *x,			const int*incx,		double *y,			const int*incy);

// C
void c_dswap(const int n, double *x, const int incx, double *y, const int incy)
{
	register int i;
	register double temp;

	if(incx == 1 && incy == 1)
	{
		for(i = 0; i < n; ++i)
		{
			temp = x[i];
			x[i] = y[i];
			y[i] = temp;
		}
	}

}

        
// Fortran C
void ftc_dswap(const int n, double *x, const int incx, double *y, const int incy)
{
	register int i;
	register double temp_x;
	register double temp_y;

	if(incx == 1 && incy == 1)
	{
		for(i = 0; i < n; ++i)
		{
			temp_x = x[i];
			temp_y = y[i];
			x[i] = temp_y;
			y[i] = temp_x;
		}
	}

}       

 
// Fortran
void f_dswap(const int n, double *x, const int incx, double *y, const int incy)
{
	xdswap_(&n,x,&incx,y,&incy);
}       
 
int N, incx, incy;
double *x, *y,*t_x, *t_y;

struct timespec begin, end;
unsigned long long int acml_time()
{
	memset(x,0,sizeof(double)*N);
	memcpy(x,t_x,sizeof(double)*N);
	memset(y,0,sizeof(double)*N);
	memcpy(y,t_y,sizeof(double)*N);

	clock_gettime(CLOCK_MONOTONIC, &begin);
	dswap(N,x,incx, y, incy);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}

unsigned long long int c_time()
{

	memset(x,0,sizeof(double)*N);
	memcpy(x,t_x,sizeof(double)*N);
	memset(y,0,sizeof(double)*N);
	memcpy(y,t_y,sizeof(double)*N);
	
	clock_gettime(CLOCK_MONOTONIC, &begin);
	c_dswap(N,x,incx,y,incy);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}


unsigned long long int f_time()
{
	memset(x,0,sizeof(double)*N);
	memcpy(x,t_x,sizeof(double)*N);
	memset(y,0,sizeof(double)*N);
	memcpy(y,t_y,sizeof(double)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	f_dswap(N,x,incx,y,incy);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}

unsigned long long int ftc_time()
{
	memset(x,0,sizeof(double)*N);
	memcpy(x,t_x,sizeof(double)*N);
	memset(y,0,sizeof(double)*N);
	memcpy(y,t_y,sizeof(double)*N);
	
	clock_gettime(CLOCK_MONOTONIC, &begin);
	ftc_dswap(N,x,incx,y,incy);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}
int main(int argc, char *argv[])
{
    
	srand(time(NULL));
   	
	N = atoi(argv[1]);
    	incx = 1;
	incy = 1;

    	x = (double*)malloc(sizeof(double)*N);
    	y = (double*)malloc(sizeof(double)*N);
    	t_x = (double*)malloc(sizeof(double)*N);
    	t_y = (double*)malloc(sizeof(double)*N);
	
	int i;
    	for (i = 0; i < N; i++)
	{
       		t_x[i] = rand()/1.0/RAND_MAX - 0.5;
       		t_y[i] = rand()/1.0/RAND_MAX - 0.5;
	}
	
        int c = 8, ic, it = 0;
	
	printf("Running test for DSWAP with N = %d\n", N);
        printf("%32s%32s%32s%32s\n","ACML","C","FORTRAN C", "FORTRAN");
	printf("Trials\n");
	printf("%32s%32s%32s%32s\n", "Time (ns)", "Time (ns)", "Time (ns)", "Time (ns)");

        unsigned long long int tot1 = 0, tot2 = 0, tot3 = 0, tot4 = 0;
        for (ic = 0; ic < c; ic++)
        {
                unsigned long long int t1, t2, t3, t4;
                t1 = acml_time();
                t2 = c_time();
                t3 = ftc_time();
		t4 = f_time();

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
