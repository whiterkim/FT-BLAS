#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern void xsrotmg_(float *d1, float *d2, float *a, float *b, float *param);

void f_srotmg(float *d1, float *d2, float *a, float *b, float *param)
{
  xsrotmg_(d1, d2, a, b, param);
}

float d11, d21, a1, b1;
float d12, d22, a2, b2;
float *param1, *param2;

float seps = 0.000001;
double deps = 0.0000000001;

void acml_test()
{
  srotmg(d11, d21, a1, b1, param1);
}

void f_test()
{
  f_srotmg(&d12, &d22, &a2, &b2, param2);
}

int scalars_cmp()
{
  return (fabs(param1[0] - param2[0]) < seps &&
          fabs(param1[1] - param2[1]) < seps &&
          fabs(param1[2] - param2[2]) < seps &&
          fabs(param1[3] - param2[3]) < seps &&
          fabs(param1[4] - param2[4]) < seps);
}

int run_test()
{
  printf("Running test for SROTMG with d1 = %f, d2 = %f, a = %f and b = %f\n",d11,d21,a1,b1);
  printf("ACML == Fortran\n");
  acml_test();
  f_test();
  int passed = scalars_cmp();
  printf("%d\n",passed);
  return passed;
}

int main(int argc, char** argv) 
{
  srand(time(NULL));
  init_();

  param1 = (float*)malloc(sizeof(float)*5);
  param2 = (float*)malloc(sizeof(float)*5);

  d11 = rand()/1.0/RAND_MAX - 0.5;
  d21 = rand()/1.0/RAND_MAX - 0.5;
  a1 = rand()/1.0/RAND_MAX - 0.5;
  b1 = rand()/1.0/RAND_MAX - 0.5;

  d12 = d11;
  d22 = d21;
  a2 = a1;
  b2 = b1;

  int all_passed = run_test();

  int sz = 5;
  float arr[5] = {-2.0,-1.0,0.0,1.0,2.0};
  int i, j, k, l;
  for (i = 0; i < sz; ++i)
  {
    for (j = 0; j < sz; ++j)
    {
      for (k = 0; k < sz; ++k)
      {
        for (l = 0; l < sz; ++l)
        {
          d11 = arr[i];
          d21 = arr[j];
          a1 = arr[k]; 
          b1 = arr[l];

          d12 = d11;
          d22 = d21;
          a2 = a1;
          b2 = b1;

          all_passed &= run_test();
        }
      }
    }
  }
  printf("All tests passed?: %d\n", all_passed);

  return 0;
}

