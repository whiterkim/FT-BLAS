#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern	void	xcscal_(	const int*n,	const complex*alpha,	complex *f_x,			const int*incx);

// C
// void c_cscal(const int n, const complex alpha, complex *x, const int incx)
// {
// 	register int i;
	
// 	if(incx == 1)
// 	{
// 		for(i = 0; i < n; ++i)
// 			x[i] *= alpha;
// 	}

	
// }

// // Fortran C
// void ftc_cscal(const int n, const complex alpha, complex *x, const int incx)
// {
// 	register int i;
	
// 	if(incx == 1)
// 	{
// 		register complex xi;
// 		for(i = 0; i < n; ++i)
// 		{
// 			xi = x[i];
// 			x[i] = xi * alpha;
// 		}
// 	}
	
// }

// Fortran 
void f_cscal(int n, complex alpha, complex *x, int incx)
{
	xcscal_(&n,&alpha,x,&incx);
}

int N, incx, incy;
complex alpha;
complex *x, *t;

struct timespec begin, end;
unsigned long long int acml_time()
{
	//memset(x,0,sizeof(complex)*N);
	//memcpy(x,t,sizeof(complex)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	cscal(N,&alpha,t,incx);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}

// unsigned long long int c_time()
// {

// 	memset(x,0,sizeof(complex)*N);
// 	memcpy(x,t,sizeof(complex)*N);
// 	clock_gettime(CLOCK_MONOTONIC, &begin);
// 	c_cscal(N,alpha,x,incx);
// 	clock_gettime(CLOCK_MONOTONIC, &end);
//         unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
//         printf("%32lld",time);
//         return time;
// }


unsigned long long int f_time()
{
	memset(x,0,sizeof(complex)*N);
	memcpy(x,t,sizeof(complex)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	f_cscal(N,alpha,x,incx);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}

// unsigned long long int ftc_time()
// {
// 	memset(x,0,sizeof(complex)*N);
// 	memcpy(x,t,sizeof(complex)*N);
// 	clock_gettime(CLOCK_MONOTONIC, &begin);
// 	ftc_cscal(N,alpha,x,incx);
// 	clock_gettime(CLOCK_MONOTONIC, &end);
//         unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
//         printf("%32lld",time);
//         return time;
// }
int main(int argc, char *argv[])
{
	init_();    
	srand(time(NULL));
   	
	N = atoi(argv[1]);
    	incx = 1;

	alpha.real = rand()/1.0/RAND_MAX - 0.5;
	alpha.imag = rand()/1.0/RAND_MAX - 0.5;
    	x = (complex*)malloc(sizeof(complex)*N);
    	t = (complex*)malloc(sizeof(complex)*N);
	
	int i;
    	for (i = 0; i < N; i++) {
       		t[i].real = rand()/1.0/RAND_MAX - 0.5;
		t[i].imag = rand()/1.0/RAND_MAX - 0.5;
	}
	
        int c = 8, ic, it = 0;
	
	printf("Running test for CSCAL with N = %d, alpha.real = %d\n, alpha.imag = %d\n", N, alpha.real, alpha.imag);
        printf("%32s%32s\n","ACML", "FORTRAN");
	printf("Trials\n");
	printf("%32s%32s%32s%32s\n", "Time (ns)", "Time (ns)");

        unsigned long long int tot1 = 0, tot2 = 0;
        for (ic = 0; ic < c; ic++)
        {
                unsigned long long int t1, t2;
                t1 = acml_time();
	//	t2 = f_time();

                if (ic >= 2)
                {
                        tot1 += t1;
                        tot2 += t2;
                        it ++;
                }
                printf("\n");
        }
        
	printf("Average\n");
        printf("%32llu%32llu%32llu%32llu\n",tot1/it,tot2/it);
    
	return 0;
}
