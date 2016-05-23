#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "acml.h"

//Original
void ori(const int n, const float alpha, float *x, const int incx)
{
	int i;
	for (i = 0; i < n; i ++)
		x[i] *= alpha;
}
void asm_sscal(int n, float alpha, float *x);

void ft_asm_sscal(int n, float alpha, float *x);

struct timespec begin, end;

int main(int argc, char *argv[])
{
	srand(time(0));
	int n = atoi(argv[1]);
	int i;
	float *x;
	float *t;
	float alpha;
	int incx = 1;
	alpha = rand()/1.0/RAND_MAX - 0.5;
	x = (float*)malloc(sizeof(float)*n);
	t = (float*)malloc(sizeof(float)*n);
	
	for (i = 0; i < n; i++)
		t[i] = rand()/1.0/RAND_MAX - 0.5;
	
	unsigned long long int t1,t2,t3,t4;
	printf("acm\n");
	memcpy(x,t,sizeof(float)*n);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	sscal(n,alpha,x,incx);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t1 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

	//for (i = 0; i < n; i++) printf("%10.6f", x[i]); printf("\n");

	printf("ori\n");
	clock_gettime(CLOCK_MONOTONIC, &begin);
	memcpy(x,t,sizeof(float)*n);
	ori(n,alpha,x,incx);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t2 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

	//for (i = 0; i < n; i++) printf("%10.6f", x[i]); printf("\n");

	printf("asm\n");
	clock_gettime(CLOCK_MONOTONIC, &begin);
	memcpy(x,t,sizeof(float)*n);
	asm_sscal(n,alpha,x);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t3 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

	//for (i = 0; i < n; i++) printf("%10.6f", x[i]); printf("\n");

	printf("as2\n");
	clock_gettime(CLOCK_MONOTONIC, &begin);
	memcpy(x,t,sizeof(float)*n);
	ft_asm_sscal(n,alpha,x);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t4 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

	//for (i = 0; i < n; i++) printf("%10.6f", x[i]); printf("\n");

	printf("acm%16lld\n",t1);
	printf("ori%16lld\n",t2);
	printf("asm%16lld\n",t3);
	printf("as2%16lld\n",t4);

	return 0;
}
