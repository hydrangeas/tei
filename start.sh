#!/bin/sh

clang tei01.c
./a.out -a 0 > low0.dat
./a.out -a 1 > low1.dat

gnuplot -persist < low.plt
