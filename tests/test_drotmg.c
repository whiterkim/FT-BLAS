#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern void xdrotmg_(double *d1, double *d2, double *a, double *b, double *param);

void f_drotmg(double *d1, double *d2, double *a, double *b, double *param)
{
  xdrotmg_(d1, d2, a, b, param);
}

void acml_test(double d1, double d2, double a, double b, double *param)
{
  drotmg(d1, d2, a, b, param);
  printf("ACML\n");
  //printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n", d1, d2, a, b);
  printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n%20.10f\n", param[0], param[1], param[2], param[3], param[4]);
}

void f_test(double d1, double d2, double a, double b, double *param)
{
  f_drotmg(&d1, &d2, &a, &b, param);
  printf("Fortran\n");
  //printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n", d1, d2, a, b);
  printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n%20.10f\n", param[0], param[1], param[2], param[3], param[4]);
}

int main(int argc, char** argv) 
{
  srand(time(NULL));
  init_();

  printf("Running test for DROTMG\n");

  double d1, d2, a, b;
  double param[5];
  d1 = rand()/1.0/RAND_MAX - 0.5;
  d2 = rand()/1.0/RAND_MAX - 0.5;
  a = rand()/1.0/RAND_MAX - 0.5;
  b = rand()/1.0/RAND_MAX - 0.5;

  acml_test(d1, d2, a, b, param);
  f_test(d1, d2, a, b, param);

  return 0;
}
