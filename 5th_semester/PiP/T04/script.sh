#!/bin/bash

make clean all || make all
for i in {1..1000}
do
  echo "${i}"
  ./main.x -L=2001 -type=PSL -seed=${i} -nfesLmt=1000000 >> file.txt
done
