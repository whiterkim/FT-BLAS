#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern	void	xdrot_(	const int*n, double*f_x, const int*incx, double*f_y, const int* incy, const double* c, const double* s);

// Fortran 
void f_drot(int n, double *x, int incx, double* y, int incy, double c, double s)
{
  xdrot_(&n, x, &incx, y, &incy, &c, &s);
}

int N, incx, incy;
double c,s; 
double *x,*x_1,*y, *y_1, *t_x, *t_y;

double deps = 0.0000000001;

struct timespec begin, end;
unsigned long long int acml_time()
{
  memcpy(x,t_x,sizeof(double)*N);
  memcpy(y,t_y,sizeof(double)*N);
  clock_gettime(CLOCK_MONOTONIC, &begin);
  drot(N, x, incx, y, incy, c, s);
  clock_gettime(CLOCK_MONOTONIC, &end);
  unsigned long long int time = 1000000000L*(end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;
  printf("%32lld",time);
  return time;
}

unsigned long long int f_time()
{
  memcpy(x_1,t_x,sizeof(double)*N);
  memcpy(y_1,t_y,sizeof(double)*N);
  clock_gettime(CLOCK_MONOTONIC, &begin);
  f_drot(N, x_1, incx, y_1, incy, c, s);
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
    if(fabs(x[i] - x_1[i]) > deps)
    {
      return 0;
    }
    else if(fabs(y[i] - y_1[i]) > deps)
    {
      return 0;
    }
  }
  return 1;
}

void run_test()
{

  printf("Running test for DROT with N = %d, incx = %d, incy = %d, c = %f, s = %f\n", N, incx, incy, c, s);
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

  c = rand()/1.0/RAND_MAX - 0.5;
  s = rand()/1.0/RAND_MAX - 0.5;
  x = (double*)malloc(sizeof(double)*N);
  x_1 = (double*)malloc(sizeof(double)*N);
  y = (double*)malloc(sizeof(double)*N);
  y_1 = (double*)malloc(sizeof(double)*N);
  t_x = (double*)malloc(sizeof(double)*N);
  t_y = (double*)malloc(sizeof(double)*N);

  int i;
  for (i = 0; i < N; i++)
  {
    t_x[i] = rand()/1.0/RAND_MAX - 0.5;
    t_y[i] = rand()/1.0/RAND_MAX - 0.5;
  }

  incx = 1;
  incy = 1;
  run_test();

  incx = 2;
  x = (double*)malloc(sizeof(double)*2*N);
  x_1 = (double*)malloc(sizeof(double)*2*N);
  incy = -1;
  run_test();

  return 0;
}
