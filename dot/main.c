#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "acml.h"

struct timespec begin, end;

extern void init_();
extern float ftsdot_(int*, float*, int*, float*, int*);

//static float dot(int n, float *x, float *y)__attribute__ ((noinline));

float asm_dot(int n, float *x, float *y);
float ft_asm_dot(int n, float *x, float *y);

int main(int argc, char *argv[])
{
    srand(time(0));
    int n = atoi(argv[1]);
    int i;
    float *x;
    float *y;
    int incx = 1;
    int incy = 1;
    x = (float*)malloc(sizeof(float)*n);
    y = (float*)malloc(sizeof(float)*n);
    for (i = 0; i < n; i++)
    {
        x[i] = rand()/1.0/RAND_MAX - 0.5;
        y[i] = rand()/1.0/RAND_MAX - 0.5;
    }

	init_();

    float ans1, ans2, ans3, ans4;
	unsigned long long int t1, t2, t3, t4;

	clock_gettime(CLOCK_MONOTONIC, &begin);
	ans1 = sdot(n, x, incx, y, incy);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t1 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

	clock_gettime(CLOCK_MONOTONIC, &begin);
    ans2 = ftsdot_(&n, x, &incx, y, &incy);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t2 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

   	clock_gettime(CLOCK_MONOTONIC, &begin);
	ans3 = asm_dot(n, x, y);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t3 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

   	clock_gettime(CLOCK_MONOTONIC, &begin);
	ans4 = ft_asm_dot(n, x, y);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t4 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;


	printf("%16f\n", ans1);
    printf("%16f\n", ans2);
    printf("%16f\n", ans3);
    printf("%16f\n", ans4);
	printf("acm%16llu\n",t1);
	printf("for%16llu\n",t2);
	printf("asm%16llu\n",t3);
	printf("as2%16llu\n",t4);
    return 0;
}

