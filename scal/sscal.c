#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void asm_sscal(int n, float alpha, float *x)
{
	float *x_ptr;
	register long i;
	register long n1;
	register float *a;

	x_ptr = x;
	n1 = n - n%16;
	a = &alpha;

	for (i = n1; i < n; i++)
	{
		x[i] *= alpha;
	}

	i = 0;
	
	if (n1 != 0)
	{
	
	__asm__ __volatile__
	(
		"vbroadcastss		(%3), %%xmm3		\n\t"		//xmm3 = alpha
		"1:										\n\t"
		"prefetcht0	 256(%2,%0,4)			    \n\t"
		"vmovups	  (%2,%0,4), %%xmm4         \n\t"		//xmm4 = x[]
		"vmovups	16(%2,%0,4), %%xmm5         \n\t"		//xmm5 = x[]
		"vmovups	32(%2,%0,4), %%xmm6         \n\t"		//xmm6 = x[]
		"vmovups	48(%2,%0,4), %%xmm7         \n\t"		//xmm7 = x[]
		".align 16				            	\n\t"
		"vmulps		%%xmm4, %%xmm3, %%xmm8		\n\t"		//xmm8 = xi * alpha
		"vmulps		%%xmm5, %%xmm3, %%xmm9		\n\t"		//xmm9 = xi * alpha
		"vmulps		%%xmm6, %%xmm3, %%xmm10		\n\t"		//xmm10 = xi * alpha
		"vmulps		%%xmm7, %%xmm3, %%xmm11		\n\t"		//xmm11 = xi * alpha
		"vmovups	%%xmm8,     (%2,%0,4)		\n\t"
		"vmovups	%%xmm9,   16(%2,%0,4)		\n\t"
		"vmovups	%%xmm10,  32(%2,%0,4)		\n\t"
		"vmovups	%%xmm11,  48(%2,%0,4)		\n\t"
		"addq		$16, %0	  	 	            \n\t"		//i += 16
		"subq	    $16, %1			            \n\t"		//n -= 16
		"jnz		1b			                \n\t"		//if (n == 0) goto 1
	:
	:
		"r" (i),		//0
		"r" (n1),		//1
		"r" (x_ptr),	//2
		"r" (a)			//3
	:
		"cc",
		"%xmm0", "%xmm1", "%xmm2", "%xmm3", 
		"%xmm4", "%xmm5", "%xmm6", "%xmm7",
		"%xmm8", "%xmm9", "%xmm10", "%xmm11",
		"%xmm12", "%xmm13", "%xmm14", "%xmm15",
		"memory"
	);

	}
}


