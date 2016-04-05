#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "acml.h"

struct timespec begin, end;

void ori(char trans, int m, int n, float alpha, float *A, int lda, float *x, int incx, float beta, float *y, int incy)
{
    if ((m == 0) || (n == 0) || (alpha == 0 && beta == 1))
        return;
    int i, j;
    float xj, t;

    //y = beta*y
    if (beta == 0)
        memset(y,0,sizeof(float)*m);
    else if (beta != 1)
        for (i = 0; i < m; i++)
            y[i] *= beta;


    if (alpha == 0) return;

    //y = alpha*A*x + y
    for (j = 0; j < n; j++)
    {
        xj = alpha*x[j];
        for (i = 0; i < m - 3; i+=3)
            y[i] += xj*(A[i + j*lda]+A[i + j*lda + 1] + A[i + j*lda + 2]);
        for (; i < m; i++)
            y[i] += xj*A[i + j*lda];
    }

}

void one(char trans, int m, int n, float alpha, float *A, int lda, float *x, int incx, float beta, float *y, int incy)
{
    if ((m == 0) || (n == 0) || (alpha == 0 && beta == 1))
        return;
    int i, j;
    float yi, cy = 0;

    //y = beta*y
    if (beta == 0)
        memset(y,0,sizeof(float)*m);
    else //if (beta != 1)
        for (i = 0; i < m; i++)
        {
            yi = y[i]*beta;
            y[i] = yi;
            cy += yi;
        }

    if (alpha == 0) return;

    float *c = (float*)malloc(sizeof(float)*n);
    float ai, cj, xj, t;
    //y = alpha*A*x + y
    for (j = 0; j < n; j++)
    {
        xj = alpha*x[j];
        cj = 0;
        for (i = 0; i < m; i++)
        {
            ai = A[i + j*lda];
            y[i] += xj*ai;
            cj += ai;
        }
        c[j] = cj;
    }

    float t1 = 0, t2 = 0;
    for (i = 0; i < m; i++)
        t1 += y[i];

    for (j = 0; j < n; j++)
        t2 += c[j]*x[j]*alpha;
    t2 += cy;

    printf("       %15.10f\n",t1);
    printf("       %15.10f\n",t2);
    printf("abs err%15.10f\n",fabs(t1-t2));
    printf("rel err%15.10f\n",fabs(1-t1/t2));
    printf("    err%15.10f\n",fabs(1-t1/t2)/(n*m*1e-6));




/*  for (i=0;i<m;i++)printf("%10f",y[i]);printf("\n");
    for (i=0;i<n;i++)printf("%10f",x[i]);printf("\n");
    for (i=0;i<n;i++)printf("%10f",c[i]);printf("\n");
    for (i=0;i<m;i++)
    {
        for (j=0;j<n;j++)
            printf("%10f",A[i+j*lda]);
        printf("\n");
    }*/
}

void exx(char trans, int m, int n, float alpha, float *A, int lda, float *x, int incx, float beta, float *y, int incy)
{
    if ((m == 0) || (n == 0) || (alpha == 0 && beta == 1))
        return;
    int i, j;
    float yi, cy = 0;

    //y = beta*y
    if (beta == 0)
        memset(y,0,sizeof(float)*m);
    else //if (beta != 1)
        for (i = 0; i < m; i++)
        {
            yi = y[i]*beta;
            y[i] = yi;
            cy += yi;
        }


    if (alpha == 0) return;

    float *c = (float*)malloc(sizeof(float)*n);
    float ai, cj, xj, t;
    float a0, a1, a2;
    //y = alpha*A*x + y
    for (j = 0; j < n; j++)
    {
        xj = alpha*x[j];
        cj = 0;
        for (i = 0; i < m - 3; i+=3)
        {
            //a0 = A[i + j*lda];
            //a1 = A[i + j*lda + 1];
            //a2 = A[i + j*lda + 2];
            //t = a0 + a1 + a2;
            t = A[i + j*lda] + A[i + j*lda + 1] + A[i + j*lda + 2];
            y[i] += xj*t;
            cj += t;
        }
        for (; i < m; i++)
        {
            ai = A[i + j*lda];
            y[i] += xj*ai;
            cj +=ai;
        }
        c[j] = cj;
    }

    float t1 = 0, t2 = 0;
    for (i = 0; i < m; i++)
        t1 += y[i];

    for (j = 0; j < n; j++)
        t2 += c[j]*x[j]*alpha;
    t2 += cy;

    printf("       %15.10f\n",t1);
    printf("       %15.10f\n",t2);
    printf("abs err%15.10f\n",fabs(t1-t2));
    printf("rel err%15.10f\n",fabs(1-t1/t2));
    printf("    err%15.10f\n",fabs(1-t1/t2)/(n*m*1e-6));
}

void dou(char trans, int m, int n, float alpha, float *A, int lda, float *x, int incx, float beta, float *y, int incy)
{
    if ((m == 0) || (n == 0) || (alpha == 0 && beta == 1))
        return;
    int i, j;
    float xj,y1,y2,ai,yi;
    float a0,a1,a2;

    //y = beta*y
    if (beta == 0)
        memset(y,0,sizeof(float)*m);
    else if (beta != 1)
        for (i = 0; i < m; i++)
        {
            yi = y[i];
            do {
                y1 = yi*beta;
                y2 = yi*beta;
            } while (y1 != y2);
            y[i] = y1;
        }

    if (alpha == 0) return;

    //y = alpha*A*x + y
    for (j = 0; j < n; j++)
    {
        xj = x[j];
        for (i = 0; i < m-3; i+=3)
        {
            yi = y[i];
            a0 = A[i + j*lda];
            a1 = A[i + j*lda + 1];
            a2 = A[i + j*lda + 2];
            Y:
                y1 = yi + (a0+a1+a2)*xj*alpha;
                y2 = yi + (a0+a1+a2)*xj*alpha;
            if (y1 != y2) goto Y;
            y[i] = y1;
        }
        for (; i < m; i++)
        {
            ai = A[i + j*lda];
            yi = y[i];
            X:
                y1 = yi + ai*xj*alpha;
                y2 = yi + ai*xj*alpha;
            if (y1 != y2) goto X;
            y[i] = y1;
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
    float alpha, beta;
    int lda = m;
    alpha = rand()/1.0/RAND_MAX - 0.5;
    beta = rand()/1.0/RAND_MAX - 0.5;
    x = (float*)malloc(sizeof(float)*n);
    y = (float*)malloc(sizeof(float)*m);
    t = (float*)malloc(sizeof(float)*m);
    A = (float*)malloc(sizeof(float)*m*n);

    for (i = 0; i < n; i++)
        x[i] = rand()/1.0/RAND_MAX - 0.5;
    for (i = 0; i < m; i++)
        t[i] = rand()/1.0/RAND_MAX - 0.5;
    for (i = 0; i < m*n; i++)
        A[i] = rand()/1.0/RAND_MAX - 0.5;

    //y = alpha*A*x + beta*y    //m row //n col

    unsigned long long int t1,t2,t3,t4,t5;
    printf("acm\n");
    memcpy(y,t,sizeof(float)*m);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    sgemv('N', m, n, alpha, A, lda, x, incx, beta, y, incy);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t1 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("ori\n");
    memcpy(y,t,sizeof(float)*m);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    ori('N', m, n, alpha, A, lda, x, incx, beta, y, incy);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t2 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("one\n");
    memcpy(y,t,sizeof(float)*m);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    one('N', m, n, alpha, A, lda, x, incx, beta, y, incy);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t3 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("exx\n");
    memcpy(y,t,sizeof(float)*m);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    exx('N', m, n, alpha, A, lda, x, incx, beta, y, incy);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t4 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;


    printf("dou\n");
    memcpy(y,t,sizeof(float)*m);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    dou('N', m, n, alpha, A, lda, x, incx, beta, y, incy);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t5 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    printf("acm%16lld\n",t1);
    printf("ori%16lld\n",t2);
    printf("one%16lld\n",t3);
    printf("exx%16lld\n",t4);
    printf("dou%16lld\n",t5);
    return 0;
}

