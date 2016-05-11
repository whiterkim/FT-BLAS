#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>      /* Standard Library of Input and Output */
#include <complex.h>    /* Standard Library of Complex Numbers */
//#include "acml.h"

// Author: Aaron Peery

struct timespec begin, end;


/* C: Complex version 
 * Function: cdotc
 * 		This function is the complex(C) version of xDotc. It performs the task of doing a dot product of 
 * 		the values from matrix X(conjugate) to the Y.
 * Parameters:
 * 		n:    dimensions
 *		x:    matrix containing float values
 *		incx: increment of x
 *		y:    matrix containing float values 
 *		incy: increment of y
**/
float complex cdotc(const int n, float complex *x, const int incx, float complex *y, const int incy) { 

	if (n <= 0) {
		return 0 + 0*I;
	}

	int ix, iy;
	float complex ctemp1 = 0 + 0*I;
	float complex ctemp2 = 0 + 0*I;
	if (incx == 1 && incy == 1) {
		int i;
		for (i = 0; i < n; i++) {
			ctemp1 = crealf(ctemp1) + crealf(conjf(x[i])*y[i]) + (cimagf(ctemp1) + cimagf(conjf(x[i])*y[i]))*I;
			ctemp2 = crealf(ctemp2) + crealf(conjf(x[i])*y[i]) + (cimagf(ctemp2) + cimagf(conjf(x[i])*y[i]))*I;
		}
	} else {
		ix = 1;
		iy = 1;

		if (ix < 0) { ix = (-n+1)*incx + 1; }
		if (iy < 0) { iy = (-n+1)*incy + 1; }

		int i;
		for (i = 0; i < n; i++) {
			ctemp1 = crealf(ctemp1) + crealf(conjf(x[ix])*y[iy]) + (cimagf(ctemp1) + cimagf(conjf(x[ix])*y[iy]))*I;
			ctemp2 = crealf(ctemp2) + crealf(conjf(x[ix])*y[iy]) + (cimagf(ctemp2) + cimagf(conjf(x[ix])*y[iy]))*I;
			ix += incx;
			iy += incy;
		}
	}
	// Final result assigned to ctemp
	//printf("cdotc Result: %i + %i*i\n",crealf(ctemp),cimagf(ctemp));
	if (ctemp1 == ctemp2) {
		return ctemp1;
	}
	return 0 + 0*I;
}

int main(int argc, char* argv[]) {

	int N = (int)pow(10,7);
	float complex *X = (float complex *)malloc(sizeof(float complex *)*N);
	float complex *Y = (float complex *)malloc(sizeof(float complex *)*N);
	int incx = 1;
	int incy = 1;

	// Generate random numbers for matrices
	srand(time(NULL));
	int i;
	for (i = 0; i < N; i++){
	    X[i] = rand()/1.0/RAND_MAX - 0.5 + (rand()/1.0/RAND_MAX - 0.5)*I;
	    Y[i] = rand()/1.0/RAND_MAX - 0.5 + (rand()/1.0/RAND_MAX - 0.5)*I;;
	}

	unsigned long long int t1;

	// Capture start time
	clock_gettime(CLOCK_MONOTONIC, &begin);

	cdotc(N,X,incx,Y,incy);

	// Capture end time
	clock_gettime(CLOCK_MONOTONIC, &end);
	t1 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
	printf("cdotc%16lld\n",t1);
}
