#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "acml.h"


#define BLASLONG long
#define FLOAT float
#define COMPLEX complex


#define NBMAX 4096

/***************************************
 *OpenBLAS version
 **************************************/

//#ifndef HAVE_KERNEL_16x4

static void sgemv_kernel_16x4(BLASLONG n, COMPLEX **ap, COMPLEX *x, COMPLEX *y)
{
    BLASLONG i;
    COMPLEX *a0,*a1,*a2,*a3;
    a0 = ap[0];
    a1 = ap[1];
    a2 = ap[2];
    a3 = ap[3];

    for ( i=0; i< n; i+=4 )
    {
        y[i] += a0[i]*x[0] + a1[i]*x[1] + a2[i]*x[2] + a3[i]*x[3];
        y[i+1] += a0[i+1]*x[0] + a1[i+1]*x[1] + a2[i+1]*x[2] + a3[i+1]*x[3];
        y[i+2] += a0[i+2]*x[0] + a1[i+2]*x[1] + a2[i+2]*x[2] + a3[i+2]*x[3];
        y[i+3] += a0[i+3]*x[0] + a1[i+3]*x[1] + a2[i+3]*x[2] + a3[i+3]*x[3];
    }
}

//#endif

static void sgemv_kernel_16x1(BLASLONG n, COMPLEX *ap, COMPLEX *x, COMPLEX *y)
{
    BLASLONG i;
    COMPLEX *a0;
    a0 = ap;

    for ( i=0; i< n; i+=4 )
    {
        y[i] += a0[i]*x[0];
        y[i+1] += a0[i+1]*x[0];
        y[i+2] += a0[i+2]*x[0];
        y[i+3] += a0[i+3]*x[0];
    }
}


static void zero_y(BLASLONG n, COMPLEX *dest)
{
    BLASLONG i;
    for ( i=0; i<n; i++ )
    {
        *dest = 0.0;
        dest++;
    }
}



static void add_y(BLASLONG n, COMPLEX *src, COMPLEX *dest, BLASLONG inc_dest)
{
    BLASLONG i;
    if ( inc_dest == 1 )
    {
        for ( i=0; i<n; i+=4 )
        {
            dest[i] += src[i];
            dest[i+1] += src[i+1];
            dest[i+2] += src[i+2];
            dest[i+3] += src[i+3];
        }

    }
    else
    {
        for ( i=0; i<n; i++ )
        {
            *dest += *src;
            src++;
            dest += inc_dest;
        }
    }
}

int CNAME(BLASLONG m, BLASLONG n, BLASLONG dummy1, COMPLEX alpha, COMPLEX *a, BLASLONG lda, COMPLEX *x, BLASLONG inc_x, COMPLEX *y, BLASLONG inc_y, COMPLEX *buffer)
{
    BLASLONG i;
    BLASLONG j;
    COMPLEX *a_ptr;
    COMPLEX *x_ptr;
    COMPLEX *y_ptr;
    COMPLEX *ap[4];
    BLASLONG n1;
    BLASLONG m1;
    BLASLONG m2;
    BLASLONG n2;
    COMPLEX xbuffer[4],*ybuffer;

        if ( m < 1 ) return(0);
        if ( n < 1 ) return(0);

    ybuffer = buffer;

    n1 = n / 4 ;
    n2 = n % 4 ;

    m1 = m - ( m % 16 );
    m2 = (m % NBMAX) - (m % 16) ;

    y_ptr = y;

    BLASLONG NB = NBMAX;

    while ( NB == NBMAX )
    {

        m1 -= NB;
        if ( m1 < 0)
        {
            if ( m2 == 0 ) break;
            NB = m2;
        }

        a_ptr = a;
        x_ptr = x;
        zero_y(NB,ybuffer);
        for( i = 0; i < n1 ; i++)
        {
            xbuffer[0] = alpha * x_ptr[0];
            x_ptr += inc_x;
            xbuffer[1] = alpha * x_ptr[0];
            x_ptr += inc_x;
            xbuffer[2] = alpha * x_ptr[0];
            x_ptr += inc_x;
            xbuffer[3] = alpha * x_ptr[0];
            x_ptr += inc_x;
            ap[0] = a_ptr;
            ap[1] = a_ptr + lda;
            ap[2] = ap[1] + lda;
            ap[3] = ap[2] + lda;
            sgemv_kernel_16x4(NB,ap,xbuffer,ybuffer);
            a_ptr += 4 * lda;
        }

        for( i = 0; i < n2 ; i++)
        {
            xbuffer[0] = alpha * x_ptr[0];
            x_ptr += inc_x;
            sgemv_kernel_16x1(NB,a_ptr,xbuffer,ybuffer);
            a_ptr += 1 * lda;

        }
        add_y(NB,ybuffer,y_ptr,inc_y);
        a     += NB;
        y_ptr += NB * inc_y;
    }
    j=0;
    while ( j < (m % 16))
    {
        a_ptr = a;
        x_ptr = x;
        COMPLEX temp = 0.0;
        for( i = 0; i < n; i++ )
        {
            temp += a_ptr[0] * x_ptr[0];
            a_ptr += lda;
            x_ptr += inc_x;
        }
        y_ptr[0] += alpha * temp;
        y_ptr += inc_y;
        a++;
        j++;
    }
    return(0);
}


/***************************************
 *OpenBLAS version with checksum
 **************************************/

//#ifndef HAVE_KERNEL_16x4

static void sgemv_kernel_16x4_2(BLASLONG n, COMPLEX **ap, COMPLEX *x, COMPLEX *y, COMPLEX *c)
{
    BLASLONG i;
    COMPLEX *a0,*a1,*a2,*a3;
    a0 = ap[0];
    a1 = ap[1];
    a2 = ap[2];
    a3 = ap[3];

    /*for ( i=0; i< n; i+=4 )
    {
        y[i] += a0[i]*x[0] + a1[i]*x[1] + a2[i]*x[2] + a3[i]*x[3];
        y[i+1] += a0[i+1]*x[0] + a1[i+1]*x[1] + a2[i+1]*x[2] + a3[i+1]*x[3];
        y[i+2] += a0[i+2]*x[0] + a1[i+2]*x[1] + a2[i+2]*x[2] + a3[i+2]*x[3];
        y[i+3] += a0[i+3]*x[0] + a1[i+3]*x[1] + a2[i+3]*x[2] + a3[i+3]*x[3];
        c[0] += a0[i] + a0[i + 1] + a0[i + 2] + a0[i + 3];
        c[1] += a1[i] + a1[i + 1] + a1[i + 2] + a1[i + 3];
        c[2] += a2[i] + a2[i + 1] + a2[i + 2] + a2[i + 3];
        c[3] += a3[i] + a3[i + 1] + a3[i + 2] + a3[i + 3];
    }*/
	
	COMPLEX t0, t1, t2, t3;
	COMPLEX x0, x1, x2, x3;
	COMPLEX c0, c1, c2, c3;
	c0 = c1 = c2 = c3 = 0;
	x0 = x[0]; x1 = x[1]; x2 = x[2]; x3 = x[3];
    for ( i=0; i< n; i+=4 )
	{
		t0 = a0[i]; t1 = a1[i]; t2 = a2[i]; t3 = a3[i];
		y[i] += t0*x0 + t1*x1 + t2*x2 + t3*x3;
		c0 += t0; c1 += t1; c2 += t2; c3 += t3;

		t0 = a0[i + 1]; t1 = a1[i + 1]; t2 = a2[i + 1]; t3 = a3[i + 1];
		y[i + 1] += t0*x0 + t1*x1 + t2*x2 + t3*x3;
		c0 += t0; c1 += t1; c2 += t2; c3 += t3;

		t0 = a0[i + 2]; t1 = a1[i + 2]; t2 = a2[i + 2]; t3 = a3[i + 2];
		y[i + 2] += t0*x0 + t1*x1 + t2*x2 + t3*x3;
		c0 += t0; c1 += t1; c2 += t2; c3 += t3;

		t0 = a0[i + 3]; t1 = a1[i + 3]; t2 = a2[i + 3]; t3 = a3[i + 3];
		y[i + 3] += t0*x0 + t1*x1 + t2*x2 + t3*x3;
		c0 += t0; c1 += t1; c2 += t2; c3 += t3;
     
	}
	c[0] += c0;
	c[1] += c1;
	c[2] += c2;
	c[3] += c3;
}

//#endif

static void sgemv_kernel_16x1_2(BLASLONG n, COMPLEX *ap, COMPLEX *x, COMPLEX *y, COMPLEX *c)
{
    BLASLONG i;
    COMPLEX *a0;
    a0 = ap;

	COMPLEX t0, t1, t2, t3;
    for ( i=0; i< n; i+=4 )
    {
		t0 = a0[i]; t1 = a0[i + 1]; t2 = a0[i + 2]; t3 = a0[i + 3];
        y[i] += t0*x[0];
        y[i+1] += t1*x[0];
        y[i+2] += t2*x[0];
        y[i+3] += t3*x[0];
        c[0] += t0 + t1 + t2 + t3;
    }
}


static void zero_y_2(BLASLONG n, COMPLEX *dest)
{
    /*BLASLONG i;
    for ( i=0; i<n; i++ )
    {
        *dest = 0.0;
        dest++;
    }*/
	memset(dest, 0, sizeof(COMPLEX)*n);
}



static void add_y_2(BLASLONG n, COMPLEX *src, COMPLEX *dest, BLASLONG inc_dest)
{
    BLASLONG i;
    if ( inc_dest == 1 )
    {
        for ( i=0; i<n; i+=4 )
        {
            dest[i] += src[i];
            dest[i+1] += src[i+1];
            dest[i+2] += src[i+2];
            dest[i+3] += src[i+3];
        }

    }
    else
    {
        for ( i=0; i<n; i++ )
        {
            *dest += *src;
            src++;
            dest += inc_dest;
        }
    }
}

int openCkm(BLASLONG m, BLASLONG n, BLASLONG dummy1, COMPLEX alpha, COMPLEX *a, BLASLONG lda, COMPLEX *x, BLASLONG inc_x, COMPLEX *y, BLASLONG inc_y, COMPLEX *buffer)
{
    BLASLONG i;
    BLASLONG j;
    COMPLEX *a_ptr;
    COMPLEX *x_ptr;
    COMPLEX *y_ptr;
    COMPLEX *ap[4];
    BLASLONG n1;
    BLASLONG m1;
    BLASLONG m2;
    BLASLONG n2;
    COMPLEX xbuffer[4],*ybuffer;

        if ( m < 1 ) return(0);
        if ( n < 1 ) return(0);

    COMPLEX *c = (COMPLEX*)malloc(sizeof(COMPLEX)*n);
    memset(c,0,sizeof(COMPLEX)*n);
    COMPLEX *c_ptr = c;
    COMPLEX cy = 0;
    for (i = 0; i < m; i++)
        cy += y[i];

    ybuffer = buffer;

    n1 = n / 4 ;
    n2 = n % 4 ;

    m1 = m - ( m % 16 );
    m2 = (m % NBMAX) - (m % 16) ;

    y_ptr = y;

    BLASLONG NB = NBMAX;

    while ( NB == NBMAX )
    {

        m1 -= NB;
        if ( m1 < 0)
        {
            if ( m2 == 0 ) break;
            NB = m2;
        }

        a_ptr = a;
        x_ptr = x;
        zero_y_2(NB,ybuffer);
        for( i = 0; i < n1 ; i++)
        {
            xbuffer[0] = alpha * x_ptr[0];
            x_ptr += inc_x;
            xbuffer[1] = alpha * x_ptr[0];
            x_ptr += inc_x;
            xbuffer[2] = alpha * x_ptr[0];
            x_ptr += inc_x;
            xbuffer[3] = alpha * x_ptr[0];
            x_ptr += inc_x;
            ap[0] = a_ptr;
            ap[1] = a_ptr + lda;
            ap[2] = ap[1] + lda;
            ap[3] = ap[2] + lda;
            sgemv_kernel_16x4_2(NB,ap,xbuffer,ybuffer,c_ptr);
            a_ptr += 4 * lda;
            c_ptr += 4;
        }

        for( i = 0; i < n2 ; i++)
        {
            xbuffer[0] = alpha * x_ptr[0];
            x_ptr += inc_x;
            sgemv_kernel_16x1_2(NB,a_ptr,xbuffer,ybuffer,c_ptr);
            a_ptr += 1 * lda;
            c_ptr ++;
        }
        add_y_2(NB,ybuffer,y_ptr,inc_y);
        a     += NB;
        y_ptr += NB * inc_y;
        c_ptr = c;
    }
    j=0;
    while ( j < (m % 16))
    {
        a_ptr = a;
        x_ptr = x;
        c_ptr = c;
        COMPLEX temp = 0.0;
        for( i = 0; i < n; i++ )
        {
            temp += a_ptr[0] * x_ptr[0];
            c_ptr[0] += a_ptr[0];
            a_ptr += lda;
            c_ptr ++;
            x_ptr += inc_x;
        }
        y_ptr[0] += alpha * temp;
        y_ptr += inc_y;
        a++;
        j++;
    }

    COMPLEX t1 = 0, t2 = 0;
    for (i = 0; i < m; i++)
        t1 += y[i];

    for (i = 0; i < n; i++)
        t2 += alpha*c[i]*x[i];
    t2 += cy;
/*
    printf("       %15.10f\n",t1);
    printf("       %15.10f\n",t2);
    printf("abs err%15.10f\n",fabs(t1-t2));
    printf("rel err%15.10f\n",fabs(1-t1/t2));
    printf("    err%15.10f\n",fabs(1-t1/t2)/(n*m*1e-6));
*/
    /*printf("c1\n");
    for (i = 0; i < n; i++)
        printf("%6.1f",c[i]);
    printf("\n");*/
    return(0);
}


void one(char trans, int m, int n, COMPLEX alpha, COMPLEX *A, int lda, COMPLEX *x, int incx, COMPLEX beta, COMPLEX *y, int incy)
{
    if ((m == 0) || (n == 0) || (alpha == 0 && beta == 1))
        return;
    int i, j;
    COMPLEX yi, cy = 0;

    //y = beta*y
    if (beta == 0)
        memset(y,0,sizeof(COMPLEX)*m);
    else //if (beta != 1)
        for (i = 0; i < m; i++)
        {
            yi = y[i]*beta;
            y[i] = yi;
            cy += yi;
        }

    if (alpha == 0) return;

    COMPLEX *c = (COMPLEX*)malloc(sizeof(COMPLEX)*n);
    COMPLEX ai, cj, xj, t;
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

    COMPLEX t1 = 0, t2 = 0;
    for (i = 0; i < m; i++)
        t1 += y[i];

    for (j = 0; j < n; j++)
        t2 += c[j]*x[j]*alpha;
    t2 += cy;
/*
    printf("       %15.10f\n",t1);
    printf("       %15.10f\n",t2);
    printf("abs err%15.10f\n",fabs(t1-t2));
    printf("rel err%15.10f\n",fabs(1-t1/t2));
    printf("    err%15.10f\n",fabs(1-t1/t2)/(n*m*1e-6));
*/
}

struct timespec begin, end;
int main(int argc, char *argv[])
{
    srand(time(0));

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int i, j;
    COMPLEX *x;
    COMPLEX *y;
    COMPLEX *A;
    COMPLEX *t;
	COMPLEX *buffer;
    int incx = 1;
    int incy = 1;
    COMPLEX alpha, beta;
    int lda = m;
    alpha = rand()/1.0/RAND_MAX - 0.5;
    beta = 1;//rand()/1.0/RAND_MAX - 0.5;
    x = (COMPLEX*)malloc(sizeof(COMPLEX)*n);
    y = (COMPLEX*)malloc(sizeof(COMPLEX)*m);
    t = (COMPLEX*)malloc(sizeof(COMPLEX)*m);
    A = (COMPLEX*)malloc(sizeof(COMPLEX)*m*n);
	buffer = (COMPLEX*)malloc(sizeof(COMPLEX)*m*n);

    for (i = 0; i < n; i++)
        x[i] = rand()/1.0/RAND_MAX - 0.5;
    for (i = 0; i < m; i++)
        t[i] = rand()/1.0/RAND_MAX - 0.5;
    for (i = 0; i < m*n; i++)
        A[i] = rand()/1.0/RAND_MAX - 0.5;

    //y = alpha*A*x + beta*y    //m row //n col

    unsigned long long int t1,t2,t3,t4,t5;
    //printf("acm\n");//ACML version
    memcpy(y,t,sizeof(COMPLEX)*m);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    sgemv('N', m, n, alpha, A, lda, x, incx, beta, y, incy);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t1 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    //printf("one\n");//Native version with checksum
    memcpy(y,t,sizeof(COMPLEX)*m);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    one('N', m, n, alpha, A, lda, x, incx, beta, y, incy);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t2 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    //printf("opc\n");//OpenBLAS version with checksum
    memcpy(y,t,sizeof(COMPLEX)*m);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    //CNAME('N', m, n, alpha, A, lda, x, incx, beta, y, incy);
	openCkm(m,n,0,alpha,A,lda,x,incx,y,incy,buffer);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t3 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    //printf("opn\n");//OpenBLAS version
    memcpy(y,t,sizeof(COMPLEX)*m);
    clock_gettime(CLOCK_MONOTONIC, &begin);
	CNAME(m,n,0,alpha,A,lda,x,incx,y,incy,buffer);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t4 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

    /*printf("opo\n");//OpenBLAS version (with new kernel)
    memcpy(y,t,sizeof(COMPLEX)*m);
    clock_gettime(CLOCK_MONOTONIC, &begin);
	CNAME_3(m,n,0,alpha,A,lda,x,incx,y,incy,buffer);
    clock_gettime(CLOCK_MONOTONIC, &end);
    t5 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;*/


    printf("acm%16lld\n",t1);
    printf("one%16lld\n",t2);
    printf("opc%16lld\n",t3);
    printf("opn%16lld\n",t4);
    //printf("opo%16lld\n",t5);
    return 0;
}


