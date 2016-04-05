#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "acml.h"

struct timespec begin, end;

void ori(int m, int n, float alpha, float *x, int incx, float *y, int incy, float *A, int lda)
{
    if ((m == 0) || (n == 0) || (alpha == 0))
        return;
    int i, j;
    float yj;

    for (j = 0; j < n; j++)
    {
        if (y[j] != 0)
        {
            yj = alpha*y[j];
            for (i = 0; i < m; i++)
                A[i + j*m] += x[i]*yj;
        }
    }
}

void one(int m, int n, float alpha, float *x, int incx, float *y, int incy, float *A, int lda)
{
    if ((m == 0) || (n == 0) || (alpha == 0))
        return;
    int i, j;
    float ai, yj, cx = 0, cy = 0, ca1 = 0, ca2 = 0;

    for (i = 0; i < m; i++)
        cx += x[i];
    for (j = 0; j < n; j++)
        cy += y[j];

    for (j = 0; j < n; j++)
    {
        if (y[j] != 0)
        {
            yj = alpha*y[j];
            for (i = 0; i < m; i++)
            {
                ai = A[i + j*m];
                ca1 += ai;
                ai += x[i]*yj;
                A[i + j*m] = ai;
                ca2 += ai;
            }
        }
    }

    float t1 = cx*cy*alpha + ca1;
    float t2 = ca2;


    printf("       %15.10f\n",t1);
    printf("       %15.10f\n",t2);
    printf("abs err%15.10f\n",fabs(t1-t2));
    printf("rel err%15.10f\n",fabs(1-t1/t2));
    printf("    err%15.10f\n",fabs(1-t1/t2)/(n*m*1e-6));
}

void exx(int m, int n, float alpha, float *x, int incx, float *y, int incy, float *A, int lda)
{
    if ((m == 0) || (n == 0) || (alpha == 0))
        return;
    int i, j, p;
    float ai, yj, cx = 0, cy = 0, ca1 = 0, ca2 = 0;
    float a0,a1,a2;

    for (i = 0; i < m; i++)
        cx += x[i];
    for (j = 0; j < n; j++)
        cy += y[j];

    for (j = 0; j < n; j++)
    {
        if (y[j] != 0)
        {
            yj = alpha*y[j];
            for (i = 0; i < m - 7; i+=7)
            {
                p = i + j*m;
                a0 = A[p];
                a1 = A[p + 1];
                a2 = A[p + 2];

                ca1 += a0 + a1 + a2;
                a0 += x[i]*yj;
                a1 += x[i + 1]*yj;
                a2 += x[i + 2]*yj;

                A[p] = a0;
                A[p + 1] = a1;
                A[p + 2] = a2;
                ca2 += a0 + a1 + a2;
            }
            for (; i < m; i++)
            {
                ai = A[i + j*m];
                ca1 += ai;
                ai += x[i]*yj;
                A[i + j*m] = ai;
                ca2 += ai;
            }

        }
    }

    float t1 = cx*cy*alpha + ca1;
    float t2 = ca2;

    printf("       %15.10f\n",t1);
    printf("       %15.10f\n",t2);
    printf("abs err%15.10f\n",fabs(t1-t2));
    printf("rel err%15.10f\n",fabs(1-t1/t2));
    printf("    err%15.10f\n",fabs(1-t1/t2)/(n*m*1e-6));
}


void dou(int m, int n, float alpha, float *x, int incx, float *y, int incy, float *A, int lda)
{
    if ((m == 0) || (n == 0) || (alpha == 0))
        return;
    int i, j;
    float xi, yj, ai, a1, a2;
    for (j = 0; j < n; j++)
    {
        if (y[j] != 0)
        {
            yj = y[j];
            for (i = 0; i < m; i++)
            {
                ai = A[i + j*m];
                xi = x[i];
                Z:
                    a1 = ai + xi*yj*alpha;
                    a2 = ai + xi*yj*alpha;
                if (a1 != a2) goto Z;
                A[i + j*m] = a1;
            }
        }
    }
}

void exd(int m, int n, float alpha, float *x, int incx, float *y, int incy, float *A, int lda)
{
    if ((m == 0) || (n == 0) || (alpha == 0))
        return;
    register int i, j, k;
    register bool b;
    register float xi, yj, ai, a1, a2, yj2;
    register float ai0,ai1,ai2;
    register float a01,a02,a11,a12,a21,a22;
    register float x0,x1,x2;
    for (j = 0; j < n; j++)
    {
        if (y[j] != 0)
        {
           
            for (i = 0; i < m - 3; i+=3)
            {
                x0 = x[i];
                x1 = x[i + 1];
                x2 = x[i + 2];

                ai0 = A[i + j*m];
                ai1 = A[i + j*m+1];
                ai2 = A[i + j*m+2];
                Y:
                    a01 = ai0 + x0*yj;
                    a02 = ai0 + x0*yj;
                    A[i + j*m] = a01;
                    a11 = ai1 + x1*yj;
                    a12 = ai1 + x1*yj;
                    A[i + j*m + 1] = a11;
                    a21 = ai2 + x2*yj;
                    a22 = ai2 + x2*yj;
                    A[i + j*m + 2] = a21;

                if (a01 + a11 + a21 != a02 + a12 + a22) goto Y;
            }

            for (; i < m; i++)
            {
                xi = x[i];
                ai = A[i + j*m];
                Z:
                    a1 = ai + xi*yj;
                    a2 = ai + xi*yj;
                if (a1 != a2) goto Z;
                A[i + j*m] = a1;
            }
        }
    }
}

struct timespec begin,end;

int main(int argc, char *argv[])
{
    srand(time(0));

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int i, j;
    float *x;
    float *y;
    float *A;
    float *t;
    int incx = 1;
    int incy = 1;
    float alpha;
    int lda = m;

    alpha = rand()/1.0/RAND_MAX - 0.5;
    x = (float*)malloc(sizeof(float)*m);
    y = (float*)malloc(sizeof(float)*n);
    t = (float*)malloc(sizeof(float)*m*n);
    A = (float*)malloc(sizeof(float)*m*n);

    for (i = 0; i < m; i++)
        x[i] = rand()/1.0/RAND_MAX - 0.5;
    for (i = 0; i < n; i++)
        y[i] = rand()/1.0/RAND_MAX - 0.5;
    for (i = 0; i < m*n; i++)
        t[i] = rand()/1.0/RAND_MAX - 0.5;


    unsigned long long int t1,t2,t3,t4,t5,t6;
    printf("acm\n");
    memcpy(A,t,sizeof(float)*m*n);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    sger(m, n, alpha, x, incx, y, incy, A, lda);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t1 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("ori\n");
    memcpy(A,t,sizeof(float)*m*n);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    ori(m, n, alpha, x, incx, y, incy, A, lda);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t2 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("one\n");
    memcpy(A,t,sizeof(float)*m*n);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    one(m, n, alpha, x, incx, y, incy, A, lda);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t3 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("exx\n");
    memcpy(A,t,sizeof(float)*m*n);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    exx(m, n, alpha, x, incx, y, incy, A, lda);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t4 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("dou\n");
    memcpy(A,t,sizeof(float)*m*n);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    dou(m, n, alpha, x, incx, y, incy, A, lda);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t5 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("exd\n");
    memcpy(A,t,sizeof(float)*m*n);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    exd(m, n, alpha, x, incx, y, incy, A, lda);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t6 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;


    printf("acm%16lld\n",t1);
    printf("ori%16lld\n",t2);
    printf("one%16lld\n",t3);
    printf("exx%16lld\n",t4);
    printf("dou%16lld\n",t5);
    printf("exd%16lld\n",t6);
    return 0;
}

