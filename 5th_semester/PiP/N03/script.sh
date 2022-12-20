#!/bin/bash

make clean all || make all
for i in {1..1000}
do
  echo "${i}"
  ./obj/main.x -L=250 -type=PSL -seed=${i} -nfesLmt=1000000 >> file.txt
done
