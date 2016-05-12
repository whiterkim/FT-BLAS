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

#define BLASLONG long
#define FLOAT float


/***************************************
 *OpenBLAS version
 **************************************/

//#if defined(SANDYBRIDGE)
#define HAVE_KERNEL_16 1
static void sger_kernel_16( BLASLONG n, FLOAT *x, FLOAT *y , FLOAT *alpha) __attribute__ ((noinline));

static void sger_kernel_16( BLASLONG n, FLOAT *x, FLOAT *y, FLOAT *alpha)
{


	BLASLONG register i = 0;

	__asm__  __volatile__
	(
	"vbroadcastss		(%4), %%xmm0		    \n\t"  // alpha	
	"prefetcht0	256(%3,%0,4)			    \n\t"
	"vmovups	  (%3,%0,4), %%xmm8         \n\t"
	"vmovups	16(%3,%0,4), %%xmm9         \n\t"
	"vmovups	32(%3,%0,4), %%xmm10        \n\t"
	"vmovups	48(%3,%0,4), %%xmm11        \n\t"

	"prefetcht0	256(%2,%0,4)			    \n\t"
	"vmovups	  (%2,%0,4), %%xmm4         \n\t"
	"vmovups	16(%2,%0,4), %%xmm5         \n\t"
	"vmovups	32(%2,%0,4), %%xmm6         \n\t"
	"vmovups	48(%2,%0,4), %%xmm7        \n\t"

	"addq		$16, %0	  	 	             \n\t"
	"subq	        $16, %1			             \n\t"		
	"jz		2f		             \n\t"

	".align 16				            \n\t"
	"1:				            \n\t"

	"vmulps		%%xmm4, %%xmm0, %%xmm4		\n\t"
	"vaddps		%%xmm8 , %%xmm4, %%xmm12	     \n\t"
	"vmulps		%%xmm5, %%xmm0, %%xmm5		\n\t"
	"vaddps		%%xmm9 , %%xmm5, %%xmm13	     \n\t"
	"vmulps		%%xmm6, %%xmm0, %%xmm6		\n\t"
	"vaddps		%%xmm10, %%xmm6, %%xmm14	     \n\t"
	"vmulps		%%xmm7, %%xmm0, %%xmm7		\n\t"
	"vaddps		%%xmm11, %%xmm7, %%xmm15	     \n\t"

	"prefetcht0	256(%3,%0,4)			    \n\t"
	"vmovups	  (%3,%0,4), %%xmm8         \n\t"
	"vmovups	16(%3,%0,4), %%xmm9         \n\t"
	"vmovups	32(%3,%0,4), %%xmm10        \n\t"
	"vmovups	48(%3,%0,4), %%xmm11        \n\t"

	"prefetcht0	256(%2,%0,4)			    \n\t"
	"vmovups	  (%2,%0,4), %%xmm4         \n\t"
	"vmovups	16(%2,%0,4), %%xmm5         \n\t"
	"vmovups	32(%2,%0,4), %%xmm6         \n\t"
	"vmovups	48(%2,%0,4), %%xmm7        \n\t"

	"vmovups	%%xmm12,  -64(%3,%0,4)		     \n\t"
	"vmovups	%%xmm13,  -48(%3,%0,4)		     \n\t"
	"vmovups	%%xmm14,  -32(%3,%0,4)		     \n\t"
	"vmovups	%%xmm15,  -16(%3,%0,4)		     \n\t"

	"addq		$16, %0	  	 	             \n\t"
	"subq	        $16, %1			             \n\t"		
	"jnz		1b		             \n\t"

	"2:				            \n\t"
	"vmulps		%%xmm4, %%xmm0, %%xmm4		\n\t"
	"vmulps		%%xmm5, %%xmm0, %%xmm5		\n\t"
	"vmulps		%%xmm6, %%xmm0, %%xmm6		\n\t"
	"vmulps		%%xmm7, %%xmm0, %%xmm7		\n\t"

	"vaddps		%%xmm8 , %%xmm4, %%xmm12	     \n\t"
	"vaddps		%%xmm9 , %%xmm5, %%xmm13	     \n\t"
	"vaddps		%%xmm10, %%xmm6, %%xmm14	     \n\t"
	"vaddps		%%xmm11, %%xmm7, %%xmm15	     \n\t"

	"vmovups	%%xmm12,  -64(%3,%0,4)		     \n\t"
	"vmovups	%%xmm13,  -48(%3,%0,4)		     \n\t"
	"vmovups	%%xmm14,  -32(%3,%0,4)		     \n\t"
	"vmovups	%%xmm15,  -16(%3,%0,4)		     \n\t"

	"vzeroupper					     \n\t"

	:
        : 
          "r" (i),	// 0	
	  "r" (n),  	// 1
          "r" (x),      // 2
          "r" (y),      // 3
          "r" (alpha)   // 4
	: "cc", 
	  "%xmm0", "%xmm1", "%xmm2", "%xmm3", 
	  "%xmm4", "%xmm5", "%xmm6", "%xmm7", 
	  "%xmm8", "%xmm9", "%xmm10", "%xmm11",
	  "%xmm12", "%xmm13", "%xmm14", "%xmm15",
	  "memory"
	);

} 


//#endif

int CNAME(BLASLONG m, BLASLONG n, BLASLONG dummy1, FLOAT alpha,
	 FLOAT *x, BLASLONG incx,
	 FLOAT *y, BLASLONG incy,
	 FLOAT *a, BLASLONG lda, FLOAT *buffer){

	FLOAT *X    = x;

	if (incx != 1) {
    		X = buffer;
    		//COPY_K(m, x, incx, X, 1);
			scopy(m, x, incx, X, 1);
	}

	BLASLONG m1 = m & -16;

	while (n > 0) 
	{
   		FLOAT y0 = alpha * *y;
		if ( m1 > 0 )
		{
			//#ifdef HAVE_KERNEL_16
				sger_kernel_16(m1, X, a, &y0);
			//#else
    				//AXPYU_K(m1, 0, 0, y0, X, 1, a, 1, NULL, 0);
			//#endif
		}
	
		if ( m > m1 )
		{
    			//AXPYU_K(m-m1, 0, 0, y0, X+m1 , 1, a+m1, 1, NULL, 0);
				saxpy(m-m1, y0, X+m1, 1, a+m1, 1);
		}
	
    		a += lda;
    		y += incy;
    		n --;
	}

	return 0;
}

/***************************************
 *OpenBLAS version with checksum
 **************************************/

//#if defined(SANDYBRIDGE)
#define HAVE_KERNEL_16 1
static void sger_kernel_16_2( BLASLONG n, FLOAT *x, FLOAT *y , FLOAT *alpha, FLOAT *c1, FLOAT *c2) __attribute__ ((noinline));

static void sger_kernel_16_2( BLASLONG n, FLOAT *x, FLOAT *y, FLOAT *alpha, FLOAT *c1, FLOAT *c2)
{


	BLASLONG register i = 0;
	*c1 = 0;//xmm1
	*c2 = 0;//xmm2

	__asm__  __volatile__
	(
	"vbroadcastss		(%4), %%xmm0		\n\t"		//xmm0 = alpha	
	"vbroadcastss		(%5), %%xmm1		\n\t"		//xmm1 = c1
	"vbroadcastss		(%6), %%xmm2		\n\t"		//xmm2 = c2

	"prefetcht0	256(%3,%0,4)			    \n\t"
	"vmovups	  (%3,%0,4), %%xmm8         \n\t"		//xmm8 = y[i + 0~3]
	"vmovups	16(%3,%0,4), %%xmm9         \n\t"		//xmm9 = y[i + 4~7]
	"vmovups	32(%3,%0,4), %%xmm10        \n\t"		//xmm10 = y[i + 8~11]
	"vmovups	48(%3,%0,4), %%xmm11        \n\t"		//xmm11 = y[i + 12~15]

	"vaddps		%%xmm1, %%xmm8, %%xmm1		\n\t"		//c1 += y[]
	"vaddps		%%xmm1, %%xmm9, %%xmm1		\n\t"		//c1 += y[]
	"vaddps		%%xmm1, %%xmm10, %%xmm1		\n\t"		//c1 += y[]
	"vaddps		%%xmm1, %%xmm11, %%xmm1		\n\t"		//c1 += y[]

	"prefetcht0	256(%2,%0,4)			    \n\t"
	"vmovups	  (%2,%0,4), %%xmm4         \n\t"		//xmm4 = x[i + 0~3]
	"vmovups	16(%2,%0,4), %%xmm5         \n\t"		//xmm5 = x[i + 4~7]
	"vmovups	32(%2,%0,4), %%xmm6         \n\t"		//xmm6 = x[i + 8~11]
	"vmovups	48(%2,%0,4), %%xmm7         \n\t"		//xmm7 = x[i + 12~15]

	"addq		$16, %0	  	 	            \n\t"		//i += 16
	"subq	    $16, %1			            \n\t"		//n -= 16
	"jz			2f			                \n\t"		//if (n == 0) goto 2

	".align 16				            	\n\t"
	"1:				            			\n\t"

	"vmulps		%%xmm4, %%xmm0, %%xmm4		\n\t"		//x[0~3] *= alpha
	"vaddps		%%xmm8 , %%xmm4, %%xmm12	\n\t"		//xmm12 = y[i + 0~3] + x[i + 0~3] 
	"vmulps		%%xmm5, %%xmm0, %%xmm5		\n\t"		//x[4~7] *= alpha
	"vaddps		%%xmm9 , %%xmm5, %%xmm13	\n\t"		//xmm13 = y[i + 4~7] + x[i + 4~7] 
	"vmulps		%%xmm6, %%xmm0, %%xmm6		\n\t"		//x[8~11] *= alpha
	"vaddps		%%xmm10, %%xmm6, %%xmm14	\n\t"		//xmm14 = y[i + 8~11] + x[i + 8~11] 
	"vmulps		%%xmm7, %%xmm0, %%xmm7		\n\t"		//x[12~15] *= alpha
	"vaddps		%%xmm11, %%xmm7, %%xmm15	\n\t"		//xmm15 = y[i + 12~15] + x[i + 12~15] 
	
	"vaddps		%%xmm2, %%xmm12, %%xmm2		\n\t"		//c2 += y[]
	"vaddps		%%xmm2, %%xmm13, %%xmm2		\n\t"		//c2 += y[]
	"vaddps		%%xmm2, %%xmm14, %%xmm2		\n\t"		//c2 += y[]
	"vaddps		%%xmm2, %%xmm15, %%xmm2		\n\t"		//c2 += y[]

	"prefetcht0	256(%3,%0,4)			    \n\t"
	"vmovups	  (%3,%0,4), %%xmm8         \n\t"		//xmm8 = y[i + 0~3]
	"vmovups	16(%3,%0,4), %%xmm9         \n\t"		//xmm9 = y[i + 4~7]
	"vmovups	32(%3,%0,4), %%xmm10        \n\t"		//xmm10 = y[i + 8~11]
	"vmovups	48(%3,%0,4), %%xmm11        \n\t"		//xmm11 = y[i + 12~15]

	"vaddps		%%xmm1, %%xmm8, %%xmm1		\n\t"		//c1 += y[]
	"vaddps		%%xmm1, %%xmm9, %%xmm1		\n\t"		//c1 += y[]
	"vaddps		%%xmm1, %%xmm10, %%xmm1		\n\t"		//c1 += y[]
	"vaddps		%%xmm1, %%xmm11, %%xmm1		\n\t"		//c1 += y[]

	"prefetcht0	256(%2,%0,4)			    \n\t"
	"vmovups	  (%2,%0,4), %%xmm4         \n\t"		//xmm4 = x[i + 0~3]
	"vmovups	16(%2,%0,4), %%xmm5         \n\t"		//xmm5 = x[i + 4~7]
	"vmovups	32(%2,%0,4), %%xmm6         \n\t"		//xmm6 = x[i + 8~11]
	"vmovups	48(%2,%0,4), %%xmm7         \n\t"		//xmm7 = x[i + 11~15]

	"vmovups	%%xmm12,  -64(%3,%0,4)		\n\t"		//y[i + 0~3] = xmm12
	"vmovups	%%xmm13,  -48(%3,%0,4)		\n\t"		//y[i + 4~7] = xmm13
	"vmovups	%%xmm14,  -32(%3,%0,4)		\n\t"		//y[i + 8~11] = xmm14
	"vmovups	%%xmm15,  -16(%3,%0,4)		\n\t"		//y[i + 12~15] = xmm15

	"addq		$16, %0	  	 	            \n\t"		//i += 16
	"subq	    $16, %1			            \n\t"		//n -= 16
	"jnz		1b		                    \n\t"		//if (n != 0) goto 0x1b

	"2:				            			\n\t"
	"vmulps		%%xmm4, %%xmm0, %%xmm4		\n\t"		//x[i + 0~3] *= alpha
	"vmulps		%%xmm5, %%xmm0, %%xmm5		\n\t"		//x[i + 4~7] *= alpha
	"vmulps		%%xmm6, %%xmm0, %%xmm6		\n\t"		//x[i + 8~11] *= alpha
	"vmulps		%%xmm7, %%xmm0, %%xmm7		\n\t"		//x[i + 12~15] *= alpha

	"vaddps		%%xmm8 , %%xmm4, %%xmm12	\n\t"		//xmm12 = y[i + 0~3] + x[i + 0~3]
	"vaddps		%%xmm9 , %%xmm5, %%xmm13	\n\t"		//xmm13 = y[i + 4~7] + x[i + 4~7]
	"vaddps		%%xmm10, %%xmm6, %%xmm14	\n\t"		//xmm14 = y[i + 8~11] + x[i + 8~11]
	"vaddps		%%xmm11, %%xmm7, %%xmm15	\n\t"		//xmm15 = y[i + 12~15] + x[i + 12~15]

	"vaddps		%%xmm2, %%xmm12, %%xmm2		\n\t"		//c2 += y[]
	"vaddps		%%xmm2, %%xmm13, %%xmm2		\n\t"		//c2 += y[]
	"vaddps		%%xmm2, %%xmm14, %%xmm2		\n\t"		//c2 += y[]
	"vaddps		%%xmm2, %%xmm15, %%xmm2		\n\t"		//c2 += y[]

	"vmovups	%%xmm12,  -64(%3,%0,4)		\n\t"		//y[i + 0~3] = xmm12
	"vmovups	%%xmm13,  -48(%3,%0,4)		\n\t"		//y[i + 4~7] = xmm13
	"vmovups	%%xmm14,  -32(%3,%0,4)		\n\t"		//y[i + 8~11] = xmm14
	"vmovups	%%xmm15,  -16(%3,%0,4)		\n\t"		//y[i + 12~15] = xmm15

	"vmovups	%%xmm1, (%5)            \n\t"		//c1 = xmm1
	"vmovups	%%xmm2, (%6)            \n\t"		//c2 = xmm2

	"vzeroupper								\n\t"

	:
        : 
          "r" (i),		// 0	
	  	  "r" (n),  	// 1
          "r" (x),      // 2
          "r" (y),      // 3
          "r" (alpha),  // 4
		  "r" (c1),		// 5
		  "r" (c2)		// 6
	: "cc", 
	  "%xmm0", "%xmm1", "%xmm2", "%xmm3", 
	  "%xmm4", "%xmm5", "%xmm6", "%xmm7", 
	  "%xmm8", "%xmm9", "%xmm10", "%xmm11",
	  "%xmm12", "%xmm13", "%xmm14", "%xmm15",
	  "memory"
	);

} 


//#endif

int openCkm(BLASLONG m, BLASLONG n, BLASLONG dummy1, FLOAT alpha,
	 FLOAT *x, BLASLONG incx,
	 FLOAT *y, BLASLONG incy,
	 FLOAT *a, BLASLONG lda, FLOAT *buffer){

	FLOAT *X    = x;

	if (incx != 1) {
    		X = buffer;
    		//COPY_K(m, x, incx, X, 1);
			scopy(m, x, incx, X, 1);
	}

	BLASLONG m1 = m & -16;

	FLOAT cx = 0, cy = 0, ca1 = 0, ca2 = 0, c1[4], c2[4];
	int i;
	for (i = 0; i < m; i++) cx += x[i];
	for (i = 0; i < n; i++) cy += y[i*incy];

	while (n > 0) 
	{
   		FLOAT y0 = alpha * *y;
		if ( m1 > 0 )
		{
			//#ifdef HAVE_KERNEL_16
				sger_kernel_16_2(m1, X, a, &y0, c1, c2);
				ca1 += c1[0] + c1[1] + c1[2] + c1[3];
				ca2 += c2[0] + c2[1] + c2[2] + c2[3];
			//#else
    			//AXPYU_K(m1, 0, 0, y0, X, 1, a, 1, NULL, 0);
				//saxpy(m1, y0, X, 1, a, 1);
			//#endif
		}
	
		if ( m > m1 )
		{
				int i;
				for (i = m1; i < m; i++)
					ca1 += *(a+i);
    			//AXPYU_K(m-m1, 0, 0, y0, X+m1 , 1, a+m1, 1, NULL, 0);
				saxpy(m-m1, y0, X+m1, 1, a+m1, 1);
				for (i = m1; i < m; i++)
					ca2 += *(a+i);
		}
	
    		a += lda;
    		y += incy;
    		n --;
	}
	float t1 = cx*cy*alpha + ca1;
	float t2 = ca2;
/*
    printf("       %15.10f\n",t1);
    printf("       %15.10f\n",t2);
    printf("abs err%15.10f\n",fabs(t1-t2));
    printf("rel err%15.10f\n",fabs(1-t1/t2));
	printf("    err%15.10f\n",fabs(1-t1/t2)/(1e3));//////////////
*/
	return 0;
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
			for (i = 0; i < m - 3; i+=3)
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
/*
    printf("       %15.10f\n",t1);
    printf("       %15.10f\n",t2);
    printf("abs err%15.10f\n",fabs(t1-t2));
    printf("rel err%15.10f\n",fabs(1-t1/t2));
	printf("    err%15.10f\n",fabs(1-t1/t2)/(n*m*1e-6));*/
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
	float *buffer;
	int incx = 1;
	int incy = 1;
	float alpha;
	int lda = m;

    alpha = rand()/1.0/RAND_MAX - 0.5;
    x = (float*)malloc(sizeof(float)*m);
    y = (float*)malloc(sizeof(float)*n);
    t = (float*)malloc(sizeof(float)*m*n);
    A = (float*)malloc(sizeof(float)*m*n);
	buffer = (float*)malloc(sizeof(float)*m*n);
    
	for (i = 0; i < m; i++)
		x[i] = rand()/1.0/RAND_MAX - 0.5; 
	for (i = 0; i < n; i++)
		y[i] = rand()/1.0/RAND_MAX - 0.5; 
	for (i = 0; i < m*n; i++)
		t[i] = rand()/1.0/RAND_MAX - 0.5; 

 
 	unsigned long long int t1,t2,t3,t4,t5,t6,t7;
	//printf("acm\n");//ACML version
	memcpy(A,t,sizeof(float)*m*n);
	clock_gettime(CLOCK_MONOTONIC, &begin);
    sger(m, n, alpha, x, incx, y, incy, A, lda);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t1 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
	//for (i = 0; i < m; i++){for (j = 0; j < n; j++) printf("%6.1f ", A[i + lda*j]);	printf("\n");}

	//printf("exx\n");//Native version with checksum (optimized)
	memcpy(A,t,sizeof(float)*m*n);
	clock_gettime(CLOCK_MONOTONIC, &begin);
    exx(m, n, alpha, x, incx, y, incy, A, lda);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t2 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
	//for (i = 0; i < m; i++){for (j = 0; j < n; j++) printf("%6.1f ", A[i + lda*j]);	printf("\n");}

	//printf("opn\n");//OpenBLAS
	memcpy(A,t,sizeof(float)*m*n);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	CNAME(m, n, 0, alpha, x, incx, y, incy, A, lda, buffer);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t3 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
	//for (i = 0; i < m; i++){for (j = 0; j < n; j++) printf("%6.1f ", A[i + lda*j]);	printf("\n");}

	//printf("opc\n");//OpenBLAS
	memcpy(A,t,sizeof(float)*m*n);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	openCkm(m, n, 0, alpha, x, incx, y, incy, A, lda, buffer);
	clock_gettime(CLOCK_MONOTONIC, &end);
	t4 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
	//for (i = 0; i < m; i++){for (j = 0; j < n; j++) printf("%6.1f ", A[i + lda*j]);	printf("\n");}
	
	//float xxx = 0;	for (i = 0; i < m*n; i++) xxx += A[i];	printf("Sum %f\n", xxx);


	printf("acm%16lld\n",t1);
	printf("exx%16lld\n",t2);
	printf("opc%16lld\n",t4);
	printf("opn%16lld\n",t3);
    return 0;
}

