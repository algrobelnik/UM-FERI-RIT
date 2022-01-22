#!/bin/bash

function helpInfo {
      echo -e "project_new version: project_new/0.0.1
Command for creating blank C/C++ project
    
Usage: project_new <project name> [-d path] [-?h]

Options:
\t-?,-h   --help : this help
\t-d path        : source path for project files"
}

function echoWrongUsage {
  echo "WRONG USAGE: try project_new --help"
}

function createMainFile {
    echo -e '#include <iostream>

using namespace std;

int main() {
\tcout << "Hello World";
\treturn 0;
}' >> "src/main.cpp"
}

function makeFile { 
  echo -e "CC = g++
FLAGS= -Wall -Iinclude
SRCS := \$(wildcard src/*.cpp *.cpp)
OBJS := \$(SRCS:src/%.cpp=build/%.o)
NAME=${1}.x

all: build/\$(NAME)

debug: FLAGS:= -g -O0 \$(FLAGS)
debug: all

release: FLAGS:= -O3 \$(FLAGS)
release: all

clean:
\trm -rf build/*

build/%.o: src/%.cpp
\t\$(CC) \$(FLAGS) -c -o \$@ $^

build/\$(NAME): \$(OBJS)
\t\$(CC) \$(FLAGS) -o \$@ $^
" >> "Makefile"
}


args=( $@ )
path=""
INDEX=0
for i in $@
do
  let INDEX=${INDEX}+1
  if [ ${i} = "-h" -o ${i} = "-?" -o ${i} = "--help" ];  then
    helpInfo
    exit 1
  elif [ ${i} = "-d" ];  then
    if [[ ${#args[${INDEX}]} -gt 0 ]];  then
      path="${args[$INDEX]}/"
    else
      echoWrongUsage
      exit 1
    fi
  fi
done
if [[ ${1} == *"-"* ]] || [ ${#@} -lt 1 ];  then
  echoWrongUsage
  exit 1
fi
if [ -d "${path}${1}" ];  then
  echo "Provide directory which does NOT exists"
  exit 1
else
  mkdir "${path}${1}"
  cd "${path}${1}"
  mkdir "src/"
  createMainFile
  mkdir "include/"
  mkdir "build/"
  mkdir "bin/"
  mkdir "tests/"
  #echo "echo \"...\"" >> "tests/test_1_pravilen.sh"
  #echo -e "echo \".\n.\n.\"" >> "tests/test_2_pravilen.sh"
  #echo -e "echo \"______\"\nexit 1">> "tests/test_3_nepravilen.sh"
  #echo -e "echo \"OI\"\nexit 1">> "tests/4_nepravilen.sh"
  #chmod +x tests/*.sh
  makeFile ${1}
fi
