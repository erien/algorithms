#!/bin/bash
rm a.out
gcc main.c --std=c99 -Wall -pedantic -o a.out
time ./a.out
