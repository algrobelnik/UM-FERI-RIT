#!/bin/bash

if [ -f $1 ]; then
  if [ -x $1 ]; then
    echo "$1 ima pravico izvajanja"
  else
    echo "$1 nima pravico izvajanja"
  fi
else
  echo "manjka vnosni parameter - uporaba $0 'ime datoteke'"
fi
