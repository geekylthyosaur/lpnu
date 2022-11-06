#!/bin/sh
export LD_LIBRARY_PATH=.

g++ -c main.cpp
g++ -c aSum.cpp
g++ -fPIC -c soSum.cpp
ar rc libSum.a aSum.o
g++ -shared -o libSum.so soSum.o
g++ main.o libSum.a libSum.so -ldl
./a.out

rm *.a *.o *.so *.out
