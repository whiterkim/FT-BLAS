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

void acml_test(float d1, float d2, float a, float b, float *param)
{
  srotmg(d1, d2, a, b, param);
  printf("ACML\n");
  //printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n", d1, d2, a, b);
  printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n%20.10f\n", param[0], param[1], param[2], param[3], param[4]);
}

void f_test(float d1, float d2, float a, float b, float *param)
{
  f_srotmg(&d1, &d2, &a, &b, param);
  printf("Fortran\n");
  //printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n", d1, d2, a, b);
  printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n%20.10f\n", param[0], param[1], param[2], param[3], param[4]);
}

int main(int argc, char** argv) 
{
  srand(time(NULL));
  init_();

  printf("Running test for SROTMG\n");
  
  float d1, d2, a, b;
  float param[5];
  d1 = rand()/1.0/RAND_MAX - 0.5;
  d2 = rand()/1.0/RAND_MAX - 0.5;
  a = rand()/1.0/RAND_MAX - 0.5;
  b = rand()/1.0/RAND_MAX - 0.5;

  printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n", d1, d2, a, b);
  acml_test(d1, d2, a, b, param);
  f_test(d1, d2, a, b, param);

  return 0;
}
