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

/* SC: Real version that uses Complex 
 * Function: scnrm2
 *      This function is the SC(Complex input Real output) of xnrm2. It performs the task of capturing the euclidean 
 *      norm for the values in X.
 * Parameters:
 *      n:    dimensions
 *      x:    matrix containing float values
 *      incx: increment of x
**/
float scnrm2(const int n, float complex *x, const int incx) {

	float norm1 = 0.0,
		  norm2 = 0.0;
	float sum1 = 0.0,
		  sum2 = 0.0;
	float scale;
	float absx_i;

	if (n < 1 || incx < 1) {
		norm1 = 0.0;
		norm2 = 0.0;
	} else if (n == 1) {
		norm1 = (creal(x[0])*creal(x[0])) + (cimag(x[0])*cimag(x[0]));
		norm2 = (creal(x[0])*creal(x[0])) + (cimag(x[0])*cimag(x[0]));
	} else {
		int ix;
		for (ix = 0; ix < n; ix += incx) {
			if (creal(x[ix]) != 0.0) {
				sum1 = sum1 + (creal(x[ix])*creal(x[ix]));
				sum2 = sum2 + (creal(x[ix])*creal(x[ix]));
			}
			if (cimag(x[ix]) != 0.0) {
				sum1 = sum1 + (cimag(x[ix])*cimag(x[ix]));
				sum2 = sum2 + (cimag(x[ix])*cimag(x[ix]));	
			}
		}
		norm1 = (float)sqrt((double)sum1);
		norm2 = (float)sqrt((double)sum2);
	}

	// the norm variable holds the final result.
	//printf("snrm2 result1: %f\n", norm1);
	//printf("snrm2 result2: %f\n", norm2);
	if (norm1 == norm2) {
		return norm1;
	}
	return 0.0;
}

int main(int argc, char* argv[]) {

	int N = (int)pow(10,3);
	float complex *X = (float complex *)malloc(sizeof(float complex *)*N);
	int incx = 1;

	// Generate random numbers for matrices
	srand(time(NULL));
	int i;
	for (i = 0; i < N; i++){
		X[i] = (rand()/1.0/RAND_MAX - 0.5) + (rand()/1.0/RAND_MAX - 0.5)*I;
	}

	unsigned long long int t1;

	// Capture start time
	clock_gettime(CLOCK_MONOTONIC, &begin);

	scnrm2(N,X,incx);
	
	// Capture end time
	clock_gettime(CLOCK_MONOTONIC, &end);
	t1 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
	printf("scnrm2%16lld\n",t1);
}
