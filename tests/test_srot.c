#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern	void	xsrot_(	const int*n, float *f_x, const int*incx, float *f_y, const int* incy, const float *c, const float *s);

// C
void c_srot(const int n, float *x, const int incx, float *y, const int incy, const float c, const float s)
{
	register int i;
	
	if(incx == 1 && incy == 1)
	{
		for(i = 0; i < n; ++i) 
		{
			x[i] = c*x[i] + s*y[i];
			y[i] = c*y[i] - s*x[i];
		}
	}

	
}


// Fortran 
void f_srot(int n, float *x, int incx, float *y, int incy, float c, float s)
{
	xsrot_(&n,x,&incx,y,&incy,&c,&s);
}

int N, incx, incy;
float c,s;
float *x,*y, *t_x, *t_y;

struct timespec begin, end;
unsigned long long int acml_time()
{
	memset(x,0,sizeof(float)*N);
	memcpy(x,t_x,sizeof(float)*N);
	memset(y,0,sizeof(float)*N);
	memcpy(y,t_y,sizeof(float)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	srot(N,x,incx,y,incy, c,s);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}

unsigned long long int c_time()
{

	memset(x,0,sizeof(float)*N);
	memcpy(x,t_x,sizeof(float)*N);
	memset(y,0,sizeof(float)*N);
	memcpy(y,t_y,sizeof(float)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	c_srot(N,x,incx,y,incy,c,s);
	clock_gettime(CLOCK_MONOTONIC, &end);
        unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
        printf("%32lld",time);
        return time;
}


unsigned long long int f_time()
{
	memset(x,0,sizeof(float)*N);
	memcpy(x,t_x,sizeof(float)*N);
	memset(y,0,sizeof(float)*N);
	memcpy(y,t_y,sizeof(float)*N);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	f_srot(N,x,incx,y,incy,c,s);
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

	c = rand()/1.0/RAND_MAX - 0.5;
	s = rand()/1.0/RAND_MAX - 0.5;
    	x = (float*)malloc(sizeof(float)*N);
    	y = (float*)malloc(sizeof(float)*N);
    	t_x = (float*)malloc(sizeof(float)*N);
    	t_y = (float*)malloc(sizeof(float)*N);
	
	int i;
    	for (i = 0; i < N; i++) {
       		t_x[i] = rand()/1.0/RAND_MAX - 0.5;
       		t_y[i] = rand()/1.0/RAND_MAX - 0.5;
	}
	
        int c = 8, ic, it = 0;
	
	printf("Running test for SROT with N = %d, c = %d, s = %d\n", N, c, s);
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
