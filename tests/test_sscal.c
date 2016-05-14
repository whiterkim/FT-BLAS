#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern	void	xsscal_(	const int*n,	const float*alpha,	float *f_x,			const int*incx);

// Fortran 
void f_sscal(int n, float alpha, float *x, int incx)
{
  xsscal_(&n,&alpha,x,&incx);
}

int N, incx;
float alpha;
float *x,*x_1, *t;

float seps = 0.000001;

struct timespec begin, end;
unsigned long long int acml_time()
{
  memcpy(x,t,sizeof(float)*N);
  clock_gettime(CLOCK_MONOTONIC, &begin);
  sscal(N,alpha,x,incx);
  clock_gettime(CLOCK_MONOTONIC, &end);
  unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
  printf("%32lld",time);
  return time;
}

unsigned long long int f_time()
{
  memcpy(x_1,t,sizeof(float)*N);
  clock_gettime(CLOCK_MONOTONIC, &begin);
  f_sscal(N,alpha,x_1,incx);
  clock_gettime(CLOCK_MONOTONIC, &end);
  unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
  printf("%32lld",time);
  return time;
}

int array_cmp()
{
  int i;
  for(i = 0; i < N; ++i)
  {
    if(fabs(x[i] - x_1[i]) > seps)
      return 0;
  }
  return 1;
}

void run_test()
{

  printf("Running test for SSCAL with N = %d, incx = %d, alpha = %f\n", N, incx, alpha);
  printf("%32s%32s\n","ACML", "FORTRAN");
  printf("Trials\n");
  printf("%32s%32s%32s\n", "Time (ns)", "Time (ns)", "ACML == FT");

  int c = 8, ic, it = 0;
  unsigned long long int tot1 = 0, tot2 = 0;
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
      it ++;
    }
    printf("\n");
  }

  printf("Average (Does not include first two trials)\n");
  printf("%32llu%32llu\n",tot1/it,tot2/it);
  printf("\n"); 
}

int main(int argc, char *argv[])
{
  init_();    
  srand(time(NULL));

  N = atoi(argv[1]);

  alpha = rand()/1.0/RAND_MAX - 0.5;
  x = (float*)malloc(sizeof(float)*N);
  x_1 = (float*)malloc(sizeof(float)*N);
  t = (float*)malloc(sizeof(float)*N);

  int i;
  for (i = 0; i < N; i++)
    t[i] = rand()/1.0/RAND_MAX - 0.5;

  incx = 1;
  run_test();

  incx = 2;
  run_test();

  incx = -2;
  run_test();

  return 0;
}
