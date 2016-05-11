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

/* SDS: Real with double calculation version 
 * Function: cdotu
 * 		This function is the Real(SDS) version of xxDot. It performs the task of doing a dot product of 
 * 		the values from matrix X(transpose) to the Y and adds an alpha.
 * Parameters:
 * 		n:    dimensions
 *		alpha:scalar value to be added with the values
 *		x:    matrix containing float values
 *		incx: increment of x
 *		y:    matrix containing float values 
 *		incy: increment of y
**/
float sdsdot(const int n, float alpha, float *x, const int incx, float *y, const int incy) { 
	
	double dsdot1 = (double)alpha;
	double dsdot2 = (double)alpha;
	if (n <= 0) {
		// return alpha
		return dsdot1;
	}

	int ix, iy;
	if (incx == incy && incx > 0) {
		int i;
		int incn = n*incx;
		for (i = 0; i < incn; i += incx) {
			dsdot1 = dsdot1 + ((double)x[i])*((double)y[i]);
			dsdot2 = dsdot2 + ((double)x[i])*((double)y[i]);
		}
	} else {
		ix = 1;
		iy = 1;

		if (ix < 0) { ix = (-n+1)*incx + 1; }
		if (iy < 0) { iy = (-n+1)*incy + 1; }

		int i;
		for (i = 0; i < n; i++) {
			dsdot1 = dsdot1 + ((double)x[ix])*((double)y[iy]);
			dsdot2 = dsdot2 + ((double)x[ix])*((double)y[iy]);
			ix += incx;
			iy += incy;
		}
	}
	// Final result assigned to ctemp
	//printf("sdsdot Result: %f\n", dsdot);
	if (dsdot1 == dsdot2) {
		return (float)dsdot1;
	}
	// error: Not equal
	return 0;
}

int main(int argc, char* argv[]) {

	int N = (int)pow(10,7);
	float *X = (float *)malloc(sizeof(float *)*N);
	float *Y = (float *)malloc(sizeof(float *)*N);
	float alpha = 0.0;
	int incx = 1;
	int incy = 1;

	// Generate random numbers for matrices
	srand(time(NULL));
	int i;
	for (i = 0; i < N; i++){
	    X[i] = rand()/1.0/RAND_MAX - 0.5;
	    Y[i] = rand()/1.0/RAND_MAX - 0.5;
	}
	alpha = rand()/1.0/RAND_MAX - 0.5;

	unsigned long long int t1;

	// Capture start time
	clock_gettime(CLOCK_MONOTONIC, &begin);
	
	sdsdot(N,alpha,X,incx,Y,incy);

	// Capture end time
	clock_gettime(CLOCK_MONOTONIC, &end);
	t1 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
	printf("sdsdot%16lld\n",t1);
}
