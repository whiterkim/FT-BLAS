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

//One checksum
void one(const int n, const float alpha, float *x, const int incx)
{
    int i;
    float xi;
    float s = 0;
    float c = 0;
    for (i = 0; i < n; i++)
    {
        xi = x[i];
        s += xi;
        if (i == 123456) xi = 10000;
        xi *= alpha;
        x[i] = xi;
        c += xi;
    }
    float t1 = s*alpha;
    float t2 = c;
    printf("       %15.10f\n",t1);
    printf("       %15.10f\n",t2);
    printf("abs err%15.10f\n",fabs(t1-t2));
    printf("rel err%15.10f\n",fabs(1-t1/t2));
    printf("    err%15.10f\n",fabs(1-t1/t2)/(n*1e-6));
    printf("    err%15.10f\n",fabs(t1-t2)/(n*1e-6));
}

//Two checksum
void two(const int n, const float alpha, float *x, const int incx)
{
    int i;
    float xi;
    float s1 = 0;
    float s2 = 0;
    float c1 = 0;
    float c2 = 0;
    for (i = 0; i < n; i++)
    {
        xi = x[i];
        s2 += xi;
        if (s2 > 1) s1++, s2--;
        if (s2 <-1) s1--, s2++;
        if (i == 123456) xi = 10;
        xi *= alpha;
        x[i] = xi;
        c2 += xi;
        if (c2 > 1) c1++, c2--;
        if (c2 <-1) c1--, c2++;
    }
    float t1 = s1*alpha + s2*alpha;
    float t2 = c1 + c2;
    printf("       %15.10f\n",t1);
    printf("       %15.10f\n",t2);
    printf("abs err%15.10f\n",fabs(t1-t2));
    printf("rel err%15.10f\n",fabs(1-t1/t2));
    printf("    err%15.10f\n",fabs(1-t1/t2)/(n*1e-6));
    printf("    err%15.10f\n",fabs(t1-t2)/(n*1e-6));
}

//Calculate twice
void dou(const int n, const float alpha, float *x, const int incx)
{
    int i;
    float t;
    float x1;
    float x2;
    for (i = 0; i < n; i++)
    {
        t = x[i];
        do {
            x1 = t*alpha;
            x2 = t*alpha;
        } while (x1 != x2);
        x[i] = x1;
    }
}

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

    unsigned long long int t1,t2,t3,t4,t5;
    printf("acm\n");
    memcpy(x,t,sizeof(float)*n);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    sscal(n,alpha,x,incx);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t1 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("ori\n");
    clock_gettime(CLOCK_MONOTONIC, &begin);
    memcpy(x,t,sizeof(float)*n);
    ori(n,alpha,x,incx);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t2 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("one\n");
    clock_gettime(CLOCK_MONOTONIC, &begin);
    memcpy(x,t,sizeof(float)*n);
    one(n,alpha,x,incx);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t3 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("two\n");
    clock_gettime(CLOCK_MONOTONIC, &begin);
    memcpy(x,t,sizeof(float)*n);
    two(n,alpha,x,incx);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t4 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("dou\n");
    clock_gettime(CLOCK_MONOTONIC, &begin);
    memcpy(x,t,sizeof(float)*n);
    dou(n,alpha,x,incx);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t5 = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("acm%16lld\n",t1);
    printf("ori%16lld\n",t2);
    printf("one%16lld\n",t3);
    printf("two%16lld\n",t4);
    printf("dou%16lld\n",t5);

    return 0;
}
