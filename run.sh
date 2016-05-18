#!/bin/sh
#PBS -l nodes=2:nogpu:ppn=2

export LD_LIBRARY_PATH=/opt/acml5.3.0/gfortran64/lib
module purge
module load gcc-4.7.2
module load mpich-3.0.3/gnu-4.7.2

mpiexec ./$1 $2
