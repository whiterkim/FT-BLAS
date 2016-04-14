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

/* S: Real version 
 * Function: snrm2
 *      This function is the Real(S) version of xnrm2. It performs the task of capturing the euclidean 
 *      norm for the values in X.
 * Parameters:
 *      n:    dimensions
 *      x:    matrix containing float values
 *      incx: increment of x
**/
void snrm2(const int n, float *x, const int incx) {

	float norm1, norm2, scale, sum1 = 0.0, sum2 = 0.0;
	float absx_i;

	if (n < 1 || incx < 1) {
		norm1 = 0.0;
		norm2 = 0.0;
	} else if (n == 1) {
		norm1 = abs(x[1]);
		norm2 = abs(x[1]);
	} else {
		int ix;
		for (ix = 0; ix < n; ix += incx) {
			if (x[ix] != 0.0) {
				sum1 = sum1 + (float)pow((x[ix]),2);
				sum2 = sum2 + (float)pow((x[ix]),2);
			}
		}
		norm1 = (float)sqrt((double)sum1);
		norm2 = (float)sqrt((double)sum2);
	}

	// the norm variable holds the final result.
	//printf("snrm2 result1: %f\n", norm1);
	//printf("snrm2 result2: %f\n", norm2);
}

int main(int argc, char* argv[]) {

	int N = (int)pow(10,3);
	float *X = (float *)malloc(sizeof(float *)*N);
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

	snrm2(N,X,incx);
	
	// Capture end time
	clock_gettime(CLOCK_MONOTONIC, &end);
	t1 =  1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
	printf("snrm2%16lld\n",t1);
}
