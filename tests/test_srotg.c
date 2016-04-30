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


void acml_test(float a, float b, float c, float s)
{
  srotg(&a, &b, &c, &s);
  printf("ACML\n");
  printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n",a,b,c,s);
}

void f_test(float a, float b, float c, float s)
{
  f_srotg(&a, &b, &c, &s);
  printf("Fortran\n");
  printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n",a,b,c,s);
}

int main(int argc, char** argv) 
{
  srand(time(NULL));
  init_();

  printf("Running test for SROTG\n");

  float a, b, c, s;
  a = rand()/1.0/RAND_MAX - 0.5;
  b = rand()/1.0/RAND_MAX - 0.5;
  c = rand()/1.0/RAND_MAX - 0.5;
  s = rand()/1.0/RAND_MAX - 0.5;

  acml_test(a, b, c, s);
  f_test(a, b, c, s);

  return 0;
}
