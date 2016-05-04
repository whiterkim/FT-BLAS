#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern	void	xcswap_(	const int*n,						complex *x,			const int*incx,		complex *y,			const int*incy);

 
// Fortran
void f_cswap(const int n, complex *x, const int incx, complex *y, const int incy)
{
	xcswap_(&n,x,&incx,y,&incy);
}       
 
int N, incx, incy;
complex *x, *y,*t_x, *t_y;

struct timespec begin, end;
unsigned long long int acml_time()
{
	//memset(x,0,sizeof(complex)*N);
	//memcpy(x,t_x,sizeof(complex)*N);
	//memset(y,0,sizeof(complex)*N);
	//memcpy(y,t_y,sizeof(complex)*N);

	clock_gettime(CLOCK_MONOTONIC, &begin);
	cswap(N,x,incx, y, incy);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}


unsigned long long int f_time()
{
	//memset(x,0,sizeof(complex)*N);
	//memcpy(x,t_x,sizeof(complex)*N);
	//memset(y,0,sizeof(complex)*N);
	//memcpy(y,t_y,sizeof(complex)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	f_cswap(N,x,incx,y,incy);
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

    	x = (complex*)malloc(sizeof(complex)*N);
    	y = (complex*)malloc(sizeof(complex)*N);
    	t_x = (complex*)malloc(sizeof(complex)*N);
    	t_y = (complex*)malloc(sizeof(complex)*N);
	
	int i;
    	for (i = 0; i < N; i++)
	{
       		x[i].real = rand()/1.0/RAND_MAX - 0.5;
		x[i].imag = rand()/1.0/RAND_MAX - 0.5;
       		y[i].real = rand()/1.0/RAND_MAX - 0.5;
		y[i].imag = rand()/1.0/RAND_MAX - 0.5;
	}
	
        int c = 8, ic, it = 0;
	
	printf("Running test for CSWAP with N = %d\n", N);
        printf("%32s%32s\n","ACML", "FORTRAN");
	printf("Trials\n");
	printf("%32s%32s\n", "Time (ns)", "Time (ns)");

        unsigned long long int tot1 = 0, tot2 = 0;
        for (ic = 0; ic < c; ic++)
        {
                unsigned long long int t1, t2;
                t1 = acml_time();
		t2 = f_time();

                if (ic >= 2)
                {
                        tot1 += t1;
                        tot2 += t2;
                        it ++;
                }
                printf("\n");
        }
        
	printf("Average\n");
        printf("%32llu%32llu\n",tot1/it,tot2/it);
    
	return 0;
}