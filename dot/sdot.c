#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>


//static float __attribute__((optimize("O0")))  dot(int n, float *x, float *y)__attribute__ ((noinline));
float asm_dot(int n, float *x, float *y)
{
	float *x_ptr;
	float *y_ptr;
	register long i;
	register long n1;
	register float xi, yi;
	float r1;
	float d1[4];
	x_ptr = x;
	y_ptr = y;
	d1[0] = d1[1] = d1[2] = d1[3] = 0;

	n1 = n - n%16;
	
	for (i = n1; i < n; i++)
	{
		r1 += x[i] * y[i];	
	}
	i = 0;

	if (n1 != 0)
	{

	__asm__ __volatile__
	(
		"vbroadcastss		(%4), %%xmm0		\n\t"		//xmm0 = d1
		"1:										\n\t"
		"prefetcht0	 256(%2,%0,4)			    \n\t"
		"vmovups	  (%2,%0,4), %%xmm4         \n\t"		//xmm4 = x[]
		"vmovups	16(%2,%0,4), %%xmm5         \n\t"		//xmm5 = x[]
		"vmovups	32(%2,%0,4), %%xmm6         \n\t"		//xmm6 = x[]
		"vmovups	48(%2,%0,4), %%xmm7         \n\t"		//xmm7 = x[]
		"prefetcht0	 256(%3,%0,4)			    \n\t"
		"vmovups	  (%3,%0,4), %%xmm8         \n\t"		//xmm8 = y[]
		"vmovups	16(%3,%0,4), %%xmm9         \n\t"		//xmm9 = y[]
		"vmovups	32(%3,%0,4), %%xmm10        \n\t"		//xmm10 = y[]
		"vmovups	48(%3,%0,4), %%xmm11        \n\t"		//xmm11 = y[]
		".align 16				            	\n\t"
		"vmulps		%%xmm4, %%xmm8, %%xmm12		\n\t"		//xmm12 = xi * yi
		"vmulps		%%xmm5, %%xmm9, %%xmm13		\n\t"		//xmm13 = xi * yi
		"vmulps		%%xmm6, %%xmm10, %%xmm14	\n\t"		//xmm14 = xi * yi
		"vmulps		%%xmm7, %%xmm11, %%xmm15	\n\t"		//xmm15 = xi * yi
		"vaddps		%%xmm0, %%xmm12, %%xmm0		\n\t"		//d1 += xmm12
		"vaddps		%%xmm0, %%xmm13, %%xmm0		\n\t"		//d1 += xmm13
		"vaddps		%%xmm0, %%xmm14, %%xmm0		\n\t"		//d1 += xmm14
		"vaddps		%%xmm0, %%xmm15, %%xmm0		\n\t"		//d1 += xmm15

		"addq		$16, %0	  	 	            \n\t"		//i += 16
		"subq	    $16, %1			            \n\t"		//n -= 16
		"jnz		1b			                \n\t"		//if (n == 0) goto 2

		"vmovups	%%xmm0, (%4)	            \n\t"		//d1 = xmm0
		"vzeroupper								\n\t"
	:
	:
		"r" (i),	//0
		"r" (n1),	//1
		"r" (x_ptr),	//2
		"r" (y_ptr),	//3
		"r" (d1)	//4
	:
		"cc",
		"%xmm0", "%xmm1", "%xmm2", "%xmm3", 
		"%xmm4", "%xmm5", "%xmm6", "%xmm7",
		"%xmm8", "%xmm9", "%xmm10", "%xmm11",
		"%xmm12", "%xmm13", "%xmm14", "%xmm15",
		"memory"
	);

	}

	/*printf("%f %f %f %f %f\n", d1[0], d1[1], d1[2], d1[3], r1);
	printf("%f %f %f %f %f\n", d2[0], d2[1], d2[2], d2[3], r2);
	printf("%f\n", t1);
	printf("%f\n", t2);*/

	float t1 = d1[0] + d1[1] + d1[2] + d1[3] + r1;
	return t1;
}

