#!/bin/sh

clang -DCONTINUE tei02.c 
./a.out | awk '{sum += $1}END{print sum/NR;}' > tei02_continue_average.dat

clang tei02.c 
./a.out > tei02_whole.dat

