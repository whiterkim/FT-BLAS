#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern float xsasum_(int *n, float *x, int *incx);

float f_sasum(int n, float *x, int incx)
{
  return xsasum_(&n,x,&incx);
}

int N, incx;
float *x;
float ans1, ans2;

float seps = 0.000001;
double deps = 0.0000000001;

struct timespec begin, end;

unsigned long long int acml_time()
{
  clock_gettime(CLOCK_MONOTONIC,&begin);
  ans1 = sasum(N,x,incx);
  clock_gettime(CLOCK_MONOTONIC,&end);

  unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
  printf("%32lld",time);
  return time;
}


unsigned long long int f_time()
{
  clock_gettime(CLOCK_MONOTONIC,&begin);
  ans2 = f_sasum(N,x,incx);
  clock_gettime(CLOCK_MONOTONIC,&end);

  unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
  printf("%32lld",time);
  return time;
}

int scalar_cmp()
{
  return fabs(ans1 - ans2) < seps;
}

void run_test() 
{
  printf("Running test for SASUM with N = %d, incx = %d\n", N, incx);
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
    printf("%32d", scalar_cmp());
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

  x = (float*)malloc(sizeof(float)*N);

  int i;
  for (i = 0; i < N; i++)
    x[i] = rand()/1.0/RAND_MAX - 0.5;

  incx = 1;
  run_test();

  x = (float*)malloc(sizeof(float)*2*N);
  for (i = 0; i < 2*N; i++)
    x[i] = rand()/1.0/RAND_MAX - 0.5;
  incx = 2;
  run_test();

  incx = -2;
  run_test();

  return 0;
}
