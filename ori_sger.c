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
	float a0,a1,a2;//,a3,a4,a5,a6,a7,a8,a9;
//	float a10,a11,a12,a13,a14,a15,a16,a17,a18,a19;
//	float a20,a21,a22,a23,a24,a25,a26,a27,a28,a29;

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
/*				a3 = A[p + 3];
				a4 = A[p + 4];
				a5 = A[p + 5];
				a6 = A[p + 6];
				a7 = A[p + 7];
				a8 = A[p + 8];
				a9 = A[p + 9];
				a10 = A[p + 10];
				a11 = A[p + 11];
				a12 = A[p + 12];
				a13 = A[p + 13];
				a14 = A[p + 14];
				a15 = A[p + 15];
				a16 = A[p + 16];
				a17 = A[p + 17];
				a18 = A[p + 18];
				a19 = A[p + 19];
				a20 = A[p + 20];
				a21 = A[p + 21];
				a22 = A[p + 22];
				a23 = A[p + 23];
				a24 = A[p + 24];
				a25 = A[p + 25];
				a26 = A[p + 26];
				a27 = A[p + 27];
				a28 = A[p + 28];
				a29 = A[p + 29];
*/				
				ca1 += a0 + a1 + a2;// + a3 + a4 + a5 + a6 + a7 + a8 + a9;
//				ca1 += a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19;
//				ca1 += a20 + a21 + a22 + a23 + a24 + a25 + a26 + a27 + a28 + a29;
				
				a0 += x[i]*yj;
				a1 += x[i + 1]*yj;
				a2 += x[i + 2]*yj;
/*				a3 += x[i + 3]*yj;
				a4 += x[i + 4]*yj;
				a5 += x[i + 5]*yj;
				a6 += x[i + 6]*yj;
				a7 += x[i + 7]*yj;
				a8 += x[i + 8]*yj;
				a9 += x[i + 9]*yj;
				a10 += x[i + 10]*yj;
				a11 += x[i + 11]*yj;
				a12 += x[i + 12]*yj;
				a13 += x[i + 13]*yj;
				a14 += x[i + 14]*yj;
				a17 += x[i + 17]*yj;
				a18 += x[i + 18]*yj;
				a19 += x[i + 19]*yj;
				a20 += x[i + 20]*yj;
				a21 += x[i + 21]*yj;
				a22 += x[i + 22]*yj;
				a23 += x[i + 23]*yj;
				a24 += x[i + 24]*yj;
				a25 += x[i + 25]*yj;
				a26 += x[i + 26]*yj;
				a27 += x[i + 27]*yj;
				a28 += x[i + 28]*yj;
				a29 += x[i + 29]*yj;
*/

				A[p] = a0;
				A[p + 1] = a1;
				A[p + 2] = a2;
/*				A[p + 3] = a3;
				A[p + 4] = a4;
				A[p + 5] = a5;
				A[p + 6] = a6;
				A[p + 7] = a7;
				A[p + 8] = a8;
				A[p + 9] = a9;
				A[p + 10] = a10;
				A[p + 11] = a11;
				A[p + 12] = a12;
				A[p + 13] = a13;
				A[p + 14] = a14;
				A[p + 15] = a15;
				A[p + 16] = a16;
				A[p + 17] = a17;
				A[p + 18] = a18;
				A[p + 19] = a19;
				A[p + 20] = a20;
				A[p + 21] = a21;
				A[p + 22] = a22;
				A[p + 23] = a23;
				A[p + 24] = a24;
				A[p + 25] = a25;
				A[p + 26] = a26;
				A[p + 27] = a27;
				A[p + 28] = a28;
				A[p + 29] = a29;
*/

/*				A[p] = a0 + x[i]*yj;
				A[p + 1] = a1 + x[i + 1]*yj;
				A[p + 2] = a2 + x[i + 2]*yj;
				A[p + 3] = a3 + x[i + 3]*yj;
				A[p + 4] = a4 + x[i + 4]*yj;
				A[p + 5] = a5 + x[i + 5]*yj;
				A[p + 6] = a6 + x[i + 6]*yj;
				A[p + 7] = a7 + x[i + 7]*yj;
				A[p + 8] = a8 + x[i + 8]*yj;
				A[p + 9] = a9 + x[i + 9]*yj;
				A[i + j*m + 10] = a1 + x[i + 10]*yj;
				A[i + j*m + 11] = a1 + x[i + 11]*yj;
				A[i + j*m + 12] = a1 + x[i + 12]*yj;
				A[i + j*m + 13] = a1 + x[i + 13]*yj;
				A[i + j*m + 14] = a1 + x[i + 14]*yj;
				A[i + j*m + 15] = a1 + x[i + 15]*yj;
				A[i + j*m + 16] = a1 + x[i + 16]*yj;
				A[i + j*m + 17] = a1 + x[i + 17]*yj;
				A[i + j*m + 18] = a1 + x[i + 18]*yj;
				A[i + j*m + 19] = a1 + x[i + 19]*yj;
*/

/*				a0 += x[i]*yj;		A[i + j*m] = a0;
				a1 += x[i + 1]*yj;	A[i + j*m + 1] = a1;
				a2 += x[i + 2]*yj;	A[i + j*m + 2] = a2;
				a3 += x[i + 3]*yj;	A[i + j*m + 3] = a3;
				a4 += x[i + 4]*yj;	A[i + j*m + 4] = a4;
				a5 += x[i + 5]*yj;	A[i + j*m + 5] = a5;
				a6 += x[i + 6]*yj;	A[i + j*m + 6] = a6;
				a7 += x[i + 7]*yj;	A[i + j*m + 7] = a7;
				a8 += x[i + 8]*yj;	A[i + j*m + 8] = a8;
				a9 += x[i + 9]*yj;	A[i + j*m + 9] = a9;
*/
				ca2 += a0 + a1 + a2;// + a3 + a4 + a5 + a6 + a7 + a8 + a9;
//				ca2 += a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19;
//				ca2 += a20 + a21 + a22 + a23 + a24 + a25 + a26 + a27 + a28 + a29;
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
	register float ai0,ai1,ai2;//,ai3,ai4,ai5;
	register float a01,a02,a11,a12,a21,a22;//,a31,a32,a41,a42,a51,a52;
	register float x0,x1,x2;//,x3,x4,x5;
	for (j = 0; j < n; j++)
	{
		if (y[j] != 0)
		{
			/*X:
				b = 0;
				yj = y[j]*alpha;
				yj2 = y[j]*alpha;
			if (yj != yj2) goto X;
			for (i = 0; i < m; i++)
			{
				xi = x[i];
				ai = A[i + j*m];
				a1 = ai + xi*yj;
				a2 = ai + xi*yj;
				A[i + j*m] = a1;
				if (a1 != a2) goto X;
			}*/
			//if (b) goto X;
			for (i = 0; i < m - 3; i+=3)
			{
				x0 = x[i];
				x1 = x[i + 1];
				x2 = x[i + 2];
				/*x3 = x[i + 3];
				x4 = x[i + 4];
				x5 = x[i + 5];*/
				
				ai0 = A[i + j*m];
				ai1 = A[i + j*m+1];
				ai2 = A[i + j*m+2];
				/*ai3 = A[i + j*m+3];
				ai4 = A[i + j*m+4];
				ai5 = A[i + j*m+5];*/
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
					/*a31 = ai3 + x3*yj;
					a32 = ai3 + x3*yj;
					A[i + j*m + 3] = a31;
					a41 = ai4 + x4*yj;
					a42 = ai4 + x4*yj;
					A[i + j*m + 4] = a41;
					a51 = ai5 + x5*yj;
					a52 = ai5 + x5*yj;
					A[i + j*m + 5] = a51;*/

				if (a01 + a11 + a21 != a02 + a12 + a22) goto Y;
				//if (a01 + a11 + a21 + a31 + a41 + a51 != a02 + a12 + a22 + a32 + a42 + a52) goto Y;
				//if ((a01 != a02) || (a11 != a12) || (a21 != a22)) goto Y;
				//b |= (a01 != a02);
				//b |= (a11 != a12);
				//b |= (a21 != a22);
				//if ((a01 != a02) || (a11 != a12) || (a21 != a22)) goto Y;
				//if (b) goto Y;
			}
			//if (b) goto X;
			/*for (i = 0; i < m; i++)
			{
				ai = A[i + j*m];
				xi = x[i];
				//do {
				X:
					a1 = ai + xi*yj;
					a2 = ai + xi*yj;
				//} while (a1 != a2);
				if (a1 != a2) goto X;
			}*/

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
	printf("acm\n");//ACML version
	memcpy(A,t,sizeof(float)*m*n);
	clock_gettime(CLOCK_MONOTONIC, &begin);
    sger(m, n, alpha, x, incx, y, incy, A, lda);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t1 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

	printf("ori\n");//Native version
	memcpy(A,t,sizeof(float)*m*n);
	clock_gettime(CLOCK_MONOTONIC, &begin);
    ori(m, n, alpha, x, incx, y, incy, A, lda);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t2 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

	printf("one\n");//Native version with checksum
	memcpy(A,t,sizeof(float)*m*n);
	clock_gettime(CLOCK_MONOTONIC, &begin);
    one(m, n, alpha, x, incx, y, incy, A, lda);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t3 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

	printf("exx\n");//Native version with checksum (optimized)
	memcpy(A,t,sizeof(float)*m*n);
	clock_gettime(CLOCK_MONOTONIC, &begin);
    exx(m, n, alpha, x, incx, y, incy, A, lda);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t4 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

	printf("dou\n");//Native version with recalculation
	memcpy(A,t,sizeof(float)*m*n);
	clock_gettime(CLOCK_MONOTONIC, &begin);
    dou(m, n, alpha, x, incx, y, incy, A, lda);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t5 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

	printf("exd\n");//Native version with recalculation (optimized)
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

