lib=/opt/acml5.3.0/gfortran64/lib/libacml.a
so=/opt/acml5.3.0/gfortran64/lib/libacml.so
h=/opt/acml5.3.0/gfortran64/include/acml.h
#export LD_LIBRARY_PATH=/opt/acml5.3.0/gfortran64/lib
all:
    #init
    gfortran -O3 -c init.f
    #level 1
    gfortran -O3 -c rotg.f
    gfortran -O3 -c rotmg.f
    #out
    gcc $(lib) $(so) $(h) -lrt -o a.out init.o rotg.o rotmg.o const.c
