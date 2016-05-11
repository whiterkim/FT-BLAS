#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"
extern double xddot_(int*, double*, int*, double*, int*);

double f_ddot(int n, double *x, int incx, double *y, int incy)
{
  return xddot_(&n,x,&incx,y,&incy);
}

int N;
double *x;
double *y;
int incx;
int incy;

struct timespec begin, end;

unsigned long long int acml_time()
{
  clock_gettime(CLOCK_MONOTONIC, &begin);
  double ans = ddot(N,x,incx,y,incy);
  clock_gettime(CLOCK_MONOTONIC, &end);
  unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
  printf("%16f%16lld",ans,time);
  return time;
}

unsigned long long int f_time()
{
  clock_gettime(CLOCK_MONOTONIC, &begin);
  double ans = f_ddot(N,x,incx,y,incy);
  clock_gettime(CLOCK_MONOTONIC, &end);
  unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
  printf("%16f%16lld",ans,time);
  return time;
}


int main(int argc, char** argv) 
{
  N = atoi(argv[1]);
  srand(time(NULL));
  init_();

  incx = 1;
  incy = 1;
  x = (double*)malloc(sizeof(double)*N);
  y = (double*)malloc(sizeof(double)*N);
  
  int i;
  for (i = 0; i < N; i++)
  {
    x[i] = rand()/1.0/RAND_MAX - 0.5;
    y[i] = rand()/1.0/RAND_MAX - 0.5;
  }

  int c = 8, ic, it = 0;

  printf("Running test for DDOT with N=%d\n",N);
  printf("%32s%32s\n","ACML","Fortran");
  printf("Trials\n");
  printf("%16s%16s%16s%16s\n","Result","Time (ns)","Result","Time (ns)");
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
  printf("%32llu%32llu\n",tot1/it,tot2/it);

  return 0;
}