#!/bin/sh

set -m
g++ main.cpp -o main
g++ process.cpp -o process

./main
