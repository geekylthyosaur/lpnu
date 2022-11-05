#!/bin/sh
export LD_LIBRARY_PATH=.

g++ -c main.cpp
g++ -c aSum.cpp
ar rc libSum.a aSum.o
ranlib libSum.a
g++ -fPIC -c soSum.cpp
g++ -shared -o libSum.so soSum.o
g++ main.o libSum.a libSum.so
./a.out

rm *.a *.o *.so *.out
