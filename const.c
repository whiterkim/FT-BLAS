#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "ftblas.h"
//#include "complex.h"

float sa,sb,c,s;
double sad,sbd,cd,sd;
float d1,d2,a,b;
float param[5];
double d1d,d2d,ad,bd;
double paramd[5];

int main(int argc, char *argv[])
{
	init_();

	//srand(time(NULL));
	sa = rand()/1.0/RAND_MAX - 0.5;
    sb = rand()/1.0/RAND_MAX - 0.5;
    c = rand()/1.0/RAND_MAX - 0.5;
    s = rand()/1.0/RAND_MAX - 0.5;
	srotg(&sa,&sb,&c,&s);
    printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n",sa,sb,c,s);

	sad = rand()/1.0/RAND_MAX - 0.5;
    sbd = rand()/1.0/RAND_MAX - 0.5;
    cd = rand()/1.0/RAND_MAX - 0.5;
    sd = rand()/1.0/RAND_MAX - 0.5;
    drotg(&sad,&sbd,&cd,&sd);
    printf("%40.20f\n%40.20f\n%40.20f\n%40.20f\n",sad,sbd,cd,sd);

    d1 = rand()/1.0/RAND_MAX - 0.5;
    d2 = rand()/1.0/RAND_MAX - 0.5;
    a = rand()/1.0/RAND_MAX - 0.5;
    b = rand()/1.0/RAND_MAX - 0.5;
    srotmg(d1,d2,a,b,param);
    printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n",d1,d2,a,b);
    printf("%20.10f\n%20.10f\n%20.10f\n%20.10f\n%20.10f\n",param[0],param[1],param[2],param[3],param[4]);

    d1d = rand()/1.0/RAND_MAX - 0.5;
    d2d = rand()/1.0/RAND_MAX - 0.5;
    ad = rand()/1.0/RAND_MAX - 0.5;
    bd = rand()/1.0/RAND_MAX - 0.5;
    drotmg(d1d,d2d,ad,bd,paramd);
    printf("%40.20f\n%40.20f\n%40.20f\n%40.20f\n",d1d,d2d,ad,bd);
    printf("%40.20f\n%40.20f\n%40.20f\n%40.20f\n%40.20f\n",paramd[0],paramd[1],paramd[2],paramd[3],paramd[4]);
    
    
	return 0;
}
