CC = gcc
CFLAGS = -O3 -g
LDFLAGS = -lrt
FC = gfortran -g
FCFLAGS = -O3

lib=/opt/acml5.3.0/gfortran64/lib/libacml.a
so=/opt/acml5.3.0/gfortran64/lib/libacml.so
h=/opt/acml5.3.0/gfortran64/include/acml.h
#export LD_LIBRARY_PATH=/opt/acml5.3.0/gfortran64/lib

FSRCS = $(wildcard *.f)
CTESTS = $(wildcard tests/*.c)
FOBJS = $(patsubst %.f,%.o,$(FSRCS))
COBJS = $(patsubst tests/%.c,%.o,$(CTESTS))
PROGS = $(patsubst tests/%.c,%,$(CTESTS))

all: $(PROGS)

$(PROGS): %: $(FOBJS) %.o
	$(CC) $(CFLAGS) $(lib) $(so) $(h) $(LDFLAGS) -o $@ $^

$(FOBJS): $(FSRCS)
	$(FC) $(FCFLAGS) -c $^

$(COBJS): $(CTESTS) 
	$(CC) $(CFLAGS) -c $^

.PHONY: clean

clean:
	rm -r $(PROGS) $(FOBJS) $(COBJS)


