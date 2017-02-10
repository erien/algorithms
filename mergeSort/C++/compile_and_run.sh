#!/bin/bash
rm a.out
g++ main.cpp -std=c++11 -Wall -pedantic -o a.out
time ./a.out
