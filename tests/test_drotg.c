#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "/opt/acml5.3.0/gfortran64/include/acml.h"

extern void xdrotg_(double *a, double *b, double *c, double *s);

void f_drotg(double *a, double *b, double *c, double *s)
{
  xdrotg_(a, b, c, s);
}

void acml_test(double a, double b, double c, double s)
{
  drotg(&a, &b, &c, &s);
  printf("ACML\n");
  printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n",a,b,c,s);
}

void f_test(double a, double b, double c, double s)
{
  f_drotg(&a, &b, &c, &s);
  printf("Fortran\n");
  printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n",a,b,c,s);
}

int main(int argc, char** argv) 
{
  srand(time(NULL));
  init_();

  printf("Running test for DROTG\n");
  
  double a, b, c, s;
  a = rand()/1.0/RAND_MAX - 0.5;
  b = rand()/1.0/RAND_MAX - 0.5;
  c = rand()/1.0/RAND_MAX - 0.5;
  s = rand()/1.0/RAND_MAX - 0.5;

  acml_test(a, b, c, s);
  f_test(a, b, c, s);

  return 0;
}
