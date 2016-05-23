lib=/opt/acml5.3.0/gfortran64/lib/libacml.a
so=/opt/acml5.3.0/gfortran64/lib/libacml.so
h=/opt/acml5.3.0/gfortran64/include/acml.h

#export LD_LIBRARY_PATH=/opt/acml5.3.0/gfortran64/lib

all:
	gcc -O0 -c sscal.c -o sscal.o
	gcc -O0 -c ftsscal.c -o ftsscal.o
	gcc -O3 -o main.out $(lib) $(so) $(h) -lrt sscal.o ftsscal.o main.c
