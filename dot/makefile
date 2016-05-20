lib=/opt/acml5.3.0/gfortran64/lib/libacml.a
so=/opt/acml5.3.0/gfortran64/lib/libacml.so
h=/opt/acml5.3.0/gfortran64/include/acml.h

#export LD_LIBRARY_PATH=/opt/acml5.3.0/gfortran64/lib

all:
	gfortran -O3 -c init.f -o init.o
	gfortran -O3 -g -c dot.f -o dot.o
	gcc -O0 -g -c sdot.c -o sdot.o
	gcc -O0 -g -c ftsdot.c -o ftsdot.o
	gcc -O3 -g -o main.out $(lib) $(so) $(h) -lrt init.o dot.o sdot.o ftsdot.o main.c -lgfortran
