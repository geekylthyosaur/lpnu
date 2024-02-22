#!/bin/sh
export LD_LIBRARY_PATH=.

g++ -c main.cpp                     # main.o
g++ -c aSum.cpp                     # aSum.o
g++ -fPIC -c soSum.cpp              # soSum.o
ar rc libSum.a aSum.o               # libSum.a
g++ -shared -o libSum.so soSum.o    # libSum.so
g++ main.o libSum.a libSum.so -ldl  # a.out
./a.out

rm *.a *.o *.so *.out
