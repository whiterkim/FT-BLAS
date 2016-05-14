#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern void xsrotg_(float *a, float *b, float *c, float *s);

void f_srotg(float *a, float *b, float *c, float *s)
{
  xsrotg_(a, b, c, s);
}

float a1, b1, c1, s1;
float a2, b2, c2, s2;

float seps = 0.000001;
double deps = 0.0000000001;

void acml_test()
{
  srotg(&a1, &b1, &c1, &s1);
}

void f_test()
{
  f_srotg(&a2, &b2, &c2, &s2);
}

int scalars_cmp()
{
  return (fabs(a1 - a2) < seps &&
          fabs(b1 - b2) < seps &&
          fabs(c1 - c2) < seps &&
          fabs(s1 - s2) < seps);
}

void run_test()
{
  printf("Running test for SROTG with a = %f, b = %f, c = %f and s = %f\n",a1,b1,c1,s1);
  printf("ACML == Fortran\n");
  acml_test();
  f_test();
  printf("%d\n",scalars_cmp());
}

int main(int argc, char** argv) 
{
  srand(time(NULL));
  init_();


  a1 = rand()/1.0/RAND_MAX - 0.5;
  b1 = rand()/1.0/RAND_MAX - 0.5;
  c1 = rand()/1.0/RAND_MAX - 0.5;
  s1 = rand()/1.0/RAND_MAX - 0.5;
  a2 = a1;
  b2 = b1;
  c2 = c1;
  s2 = s1;
  run_test();

  a1 = 5.5;
  b1 = 4.5;
  c1 = rand()/1.0/RAND_MAX - 0.5;
  s1 = rand()/1.0/RAND_MAX - 0.5;
  a2 = a1;
  b2 = b1;
  c2 = c1;
  s2 = s1;
  run_test();

  a1 = 4.5;
  b1 = 5.5;
  c1 = rand()/1.0/RAND_MAX - 0.5;
  s1 = rand()/1.0/RAND_MAX - 0.5;
  a2 = a1;
  b2 = b1;
  c2 = c1;
  s2 = s1;
  run_test();

  a1 = 4.5;
  b1 = 5.5;
  c1 = 0;
  s1 = rand()/1.0/RAND_MAX - 0.5;
  a2 = a1;
  b2 = b1;
  c2 = c1;
  s2 = s1;
  run_test();

  a1 = 0.0;
  b1 = 0.0;
  c1 = rand()/1.0/RAND_MAX - 0.5;
  s1 = rand()/1.0/RAND_MAX - 0.5;
  a2 = a1;
  b2 = b1;
  c2 = c1;
  s2 = s1;
  run_test();

  return 0;
}
