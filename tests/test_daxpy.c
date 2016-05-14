#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern	void	xdaxpy_(int *n, double *alpha, double *x, int *incx, double *y, int* incy);

void f_daxpy(int n, double alpha, double *x, int incx, double *y, int incy)
{
  xdaxpy_(&n,&alpha,x,&incx,y,&incy);
}

int N, incx, incy;
double alpha;
double *x, *y_1, *y_2,*t_y;

float seps = 0.000001;
double deps = 0.0000000001;

struct timespec begin, end;

unsigned long long int acml_time()
{
  memcpy(y_1,t_y,sizeof(double)*N);

  clock_gettime(CLOCK_MONOTONIC,&begin);
  daxpy(N,alpha,x,incx,y_1,incy);
  clock_gettime(CLOCK_MONOTONIC,&end);

  unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
  printf("%32lld",time);
  return time;
}


unsigned long long int f_time()
{
  memcpy(y_2,t_y,sizeof(double)*N);

  clock_gettime(CLOCK_MONOTONIC,&begin);
  f_daxpy(N,alpha,x,incx,y_2,incy);
  clock_gettime(CLOCK_MONOTONIC,&end);

  unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
  printf("%32lld",time);
  return time;
}

int array_cmp()
{
  int i;
  for (i = 0; i < N; ++i)
  {
    if (abs(y_1[i] - y_2[i]) > seps)
      return 0;
  }
  return 1;
}

void run_test() 
{
  printf("Running test for DAXPY with N = %d, incx = %d, incy = %d, alpha = %f\n", N, incx, incy, alpha);
  printf("%32s%32s\n","ACML","Fortran");
  printf("Trials\n");
  printf("%32s%32s%32s\n", "Time (ns)", "Time (ns)", "ACML == FT");

  int c = 8, it = 0;
  unsigned long long int tot1 = 0, tot2 = 0;

  int ic;
  for (ic = 0; ic < c; ic++)
  {
    unsigned long long int t1, t2;
    t1 = acml_time();
    t2 = f_time();
    printf("%32d", array_cmp());
    if (ic >= 2)
    {
      tot1 += t1;
      tot2 += t2;
      ++it;
    }
    printf("\n");
  }

  printf("Average (Does not include first two trials)\n");
  printf("%32llu%32llu\n",tot1/it,tot2/it);
  printf("\n");
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  init_();

  N = atoi(argv[1]);

  alpha = rand()/1.0/RAND_MAX - 0.5;
  x = (double*)malloc(sizeof(double)*N);
  y_1 = (double*)malloc(sizeof(double)*N);
  y_2 = (double*)malloc(sizeof(double)*N);
  t_y = (double*)malloc(sizeof(double)*N);

  int i;
  for (i = 0; i < N; i++)
  {
    t_y[i] = rand()/1.0/RAND_MAX - 0.5;
    x[i] = rand()/1.0/RAND_MAX - 0.5;
  }

  incx = 1;
  incy = 1;
  run_test();

  incx = 2;
  incy = 2;
  run_test();

  incx = -2;
  incy = -2;
  run_test();

  alpha = 0;
  run_test();

  return 0;
}
