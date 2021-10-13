#!/bin/bash

args=( ${@} )
for i in $args
do
  if [ ${i} = "-h" -o ${i} = "-?" -o ${i} = "--help" ];  then
    echo "project_new version: project_new/0.0.1
Command for creating blank C/C++ project
    
Usage: project_new <project name> [-d path] [-?h]

Options:
  -?,-h   --help : this help
  -d path        : source path for project files"
  exit 1
  fi
done
if [[ ${args[0]} == *"-"* ]];  then
  echo "WRONG USAGE: try project_new --help"
  exit 1
fi
if [ -d ${args[0]} ];  then
  echo "Provide directory which does NOT exists"
  exit 1
else
  mkdir ${args[0]}
  cd ${args[0]}
  mkdir "src/"
  echo '#include <iostream>

using namespace std;

int main() {
  cout << "Hello World";

  return 0;
}' >> "src/main.c"
  mkdir "include/"
  mkdir "build/"
  mkdir "bin/"
  mkdir "tests/"
  echo -e 'CC = g++
CFLAGS= -Wall -g

main: src/main.c
\t${CC} ${CFLAGS} -o main.x src/main.c' >> "Makefile"
fi
