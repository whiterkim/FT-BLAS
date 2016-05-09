#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"
extern int xcscal_(int*, complex*, complex*, int*);

int f_cscal(int n, complex* alpha, complex *x, int incx)
{
  xcscal_(&n,alpha,x,&incx);
}

int N;
complex *x;
complex *alpha;
int incx;

struct timespec begin, end;

unsigned long long int acml_time()
{
  clock_gettime(CLOCK_MONOTONIC, &begin);
  cscal(N,alpha,x,incx);
  clock_gettime(CLOCK_MONOTONIC, &end);
  unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
  printf("%16lld",time);
  return time;
}

unsigned long long int f_time()
{
  clock_gettime(CLOCK_MONOTONIC, &begin);
  f_cscal(N,alpha,x,incx);
  clock_gettime(CLOCK_MONOTONIC, &end);
  unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
  printf("%16lld",time);
  return time;
}


int main(int argc, char** argv) 
{
  N = atoi(argv[1]);
  srand(time(NULL));
  init_();

  x = (complex*)malloc(sizeof(complex)*N);
  alpha = (complex*)malloc(sizeof(complex));
  incx = 1;
  alpha[0].real = 2;
  alpha[0].imag = 2;

  int i;
  for (i = 0; i < N; i++)
  {
    x[i].real = rand()/1.0/RAND_MAX - 0.5;
    x[i].imag = rand()/1.0/RAND_MAX - 0.5;
  }

  int c = 8, ic, it = 0;

  printf("Running test for CSCAL with N=%d\n",N);
  printf("%16s%16s\n","ACML","Fortran");
  printf("Trials\n");
  printf("%16s%16s\n","Time (ns)","Time (ns)");
  unsigned long long int tot1 = 0, tot2 = 0;
  for (ic = 0; ic < c; ic++)
  {
    unsigned long long int t1, t2;
    t1 = acml_time();
    t2 = f_time();

    if (ic >= 2)
    {
      tot1 += t1;
      tot2 += t2;
      ++it;
    }

    printf("\n");
  }
  printf("Average (Does not include first 2 trials)\n");
  printf("%16llu%16llu\n",tot1/it,tot2/it);

  return 0;
}
