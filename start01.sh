#!/bin/sh

clang tei01.c
./a.out -a 0 > tei01_low0.dat
./a.out -a 1 > tei01_low1.dat

gnuplot -persist < tei01_low.plt
