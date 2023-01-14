#!/bin/bash

make clean all || make all
for i in {250,2001,4000}
do
  echo "${i}"
  ./obj/main.x -L=$i -type=PSL -seed=3123123 -nfesLmt=1000000
done
