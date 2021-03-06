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

/* D: Double precision version 
 * Function: dnrm2
 *      This function is the Double precision(D) version of xnrm2. It performs the task of capturing the euclidean 
 *      norm for the values in X.
 * Parameters:
 *      n:    dimensions
 *      x:    matrix containing float values
 *      incx: increment of x
**/
double dnrm2(const int n, double *x, const int incx) {

	double norm1, norm2, scale, sum1 = 0.0, sum2 = 0.0;
	double absx_i;

	if (n < 1 || incx < 1) {
		norm1 = 0.0;
		norm2 = 0.0;
		return norm1;
	} else if (n == 1) {
		norm1 = abs(x[1]);
		norm2 = abs(x[1]);
		return norm1;
	} else {
		int ix;
		for (ix = 0; ix < n; ix += incx) {
			if (x[ix] != 0.0) {
				sum1 = sum1 + pow((x[ix]),2);
				sum2 = sum2 + pow((x[ix]),2);
			}
		}
		norm1 = sqrt(sum1);
		norm2 = sqrt(sum2);
		
		if (norm1 == norm2) 
			return norm1;
	}

	// the norm variable holds the final result.
	//printf("snrm2 result1: %f\n", norm1);
	//printf("snrm2 result2: %f\n", norm2);
	return -1.0;
}

int main(int argc, char* argv[]) {

	int N = (int)pow(10,3);
	double *X = (double *)malloc(sizeof(double *)*N);
	int incx = 1;

	// Generate random numbers for matrices
	srand(time(NULL));
	int i;
	for (i = 0; i < N; i++){
		X[i] = rand()/1.0/RAND_MAX - 0.5;
	}

	unsigned long long int t1;

	// Capture start time
	clock_gettime(CLOCK_MONOTONIC, &begin);

	dnrm2(N,X,incx);
	
	// Capture end time
	clock_gettime(CLOCK_MONOTONIC, &end);
	t1 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
	printf("dnrm2%16lld\n",t1);
}
