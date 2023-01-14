#!/bin/bash

mpic++ src/main.cpp -o obj/main.x

for i in {1..250}
do
  echo ${i}
  mpirun -np 2 obj/main.x >> result.txt
done
