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
NAME=${1}

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

function createProjectAddScript {
  cat >project_add.sh <<EOF
#!/bin/bash

function helpInfo {
      echo -e "project_add version: project_add/0.0.1
Command for creating blank C/C++ file with header

Usage: project_add <file name> [-?hf]

Options:
\t-?,-h   --help  : this help
\t-f      --force : rewrite already written files"
}

function echoWrongUsage {
  echo "WRONG USAGE: try project_add --help"
}

args=( "\$@" )
for i in "\$@"
do
  if [ "\${i}" = "-h" -o "\${i}" = "-?" -o "\${i}" = "--help" ];  then
    helpInfo
    exit 1
  fi
done
if [[ "\${1}" == *"-"* ]] || [ "\${#@}" -lt 1 ];  then
  echoWrongUsage
  exit 1
fi
if [ -f "src/"\${1}".cpp" ] || [ -f "include/"\${1}".h" ];  then
  if [[ "\${2}" = "-f" ]] || [[ "\${2}" = "--force" ]];  then
    echo "forced rewrite" 
  else 
    echo "Atleast one of provided files already exists.
Try project_add --help for more informations"
    exit 1
  fi
fi
echo "#include \""\${1}".h\"" > "src/"\${1}".cpp"
echo "#ifndef "\${1}"_H_
#define "\${1}"_H_

// tukaj implementirate funkcionalnosti objekta "\${1}"

#endif // "\${1}"_H_" > "include/"\${1}".h"
EOF
chmod +x project_add.sh
}

function createProjectTestScript {
  cat >project_test.sh <<EOF
#!/bin/bash

function helpInfo {
      echo -e "project_test version: project_test/0.0.1
Command for testing all or specific test in tests folder

Usage: project_test <file name> [-?hlv] [name]

Options:
\t-?,-h   --help      : this help
\t-l      --list      : outputs all test in tests/ folder
\t-v      --valgrind  : run test with valgrind"
}

function echoWrongUsage {
  echo "WRONG USAGE: try project_test --help"
}

TOTAL=0
FCOUNT=0
SCRIPTS=tests/test_*.sh
DBG=bash
for i in "\$@"
do
  if [ "\${i}" = "-h" -o "\${i}" = "-?" -o "\${i}" = "--help" ];  then
    helpInfo
    exit 1
  elif [ "\${i}" = "-l" -o "\${i}" = "--list" ];  then
    if [ ! -d "tests" ];  then
      echo "Directory does not exists"
      exit 1
    else
      echo "Tests:"
    fi
    for j in tests/test_*.sh
    do
      echo "\$j" | cut -c 12- | rev | cut -c 4- | rev
    done
    exit 1
  elif [ "\${i}" = "-v" -o "\${i}" = "--valgrind" ];  then
    DBG=valgrind
  fi
done
if ([[ ! "\${1}" == *"-"* ]] && [ \${#@} -gt 0 ]) || [ "\${#@}" -gt 2 ];  then
  if [[ -f "tests/test_\${1}.sh" ]];  then
    SCRIPTS=tests/test_\${1}.sh
  elif [[ -f "tests/test_\${1}" ]];  then
    SCRIPTS=tests/test_\${1}
  elif [[ -f "tests/\${1}.sh" ]];  then
    SCRIPTS=tests/\${1}.sh
  elif [[ -f "tests/\${1}" ]];  then
    SCRIPTS=tests/\${1}
  elif [[ -f "\${1}.sh" ]];  then
    SCRIPTS=\${1}.sh
  elif [[ -f "\${1}" ]];  then
    SCRIPTS=\${1}
  else
    echoWrongUsage
    exit 1
  fi
fi
for f in \${SCRIPTS}; do
  echo "\$f" | cut -c 7-
  \${DBG} "\$f"
  if [ "\$?" -eq 0 ];  then
    echo -e "sucess"
  else
    echo -e "fail"
    let FCOUNT="\${FCOUNT}"+1
  fi
  let TOTAL="\${TOTAL}"+1
done
echo -e "\n"\${FCOUNT}" of "\${TOTAL}" tests failed"
EOF
chmod +x project_test.sh
}

function createProjectScript {
  cat >project.sh <<EOF
#!/bin/bash

function helpInfo {
      echo -e "project version: project/0.0.1
Command for executing add, new or test project command.

Usage: project <type> [-?h]

Options:
\t-?,-h   --help      : this help"
}

function echoWrongUsage {
  echo "WRONG USAGE: try project --help"
}
INDEX=0
DIR="\$(dirname "\${BASH_SOURCE}")"
for i in "\$@"
do
  args[\$INDEX]=\$i
  let INDEX=\${INDEX}+1
done
if [ \${args[0]} = "new" ] || [ \${args[0]} = "add" ] || [ \${args[0]} = "test" ] || [ "\${args[0]}" = "-h" -o "\${args[0]}" = "-?" -o "\${args[0]}" = "--help" ];  then
  if [ "\${args[0]}" = "-h" -o "\${args[0]}" = "-?" -o "\${args[0]}" = "--help" ];  then
    helpInfo
    exit 1
  fi
  if [ \${args[0]} = "new" ];  then
    cd \$DIR
    cd ../
  fi
  a=2
  params=\${args[1]}
  while [[ \$a -lt \${#args}+1 ]]
  do
    params=\${params}" \${args[\$a]}"
    let a=\$a+1
  done
  bash project_\${args[0]}.sh \$params
  if [ "\$?" -eq 0 ];  then
    echo -e "sucess"
  else
    echo -e "fail"
    let FCOUNT="\${FCOUNT}"+1
  fi
else
  echoWrongUsage
  exit 1
fi
EOF
chmod +x project.sh
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
if [ -d "${path}project_${1}" ];  then
  echo "Provide directory which does NOT exists"
  exit 1
else
  mkdir "${path}project_${1}"
  cd "${path}project_${1}"
  mkdir "src/"
  createMainFile
  mkdir "include/"
  mkdir "build/"
  mkdir "bin/"
  mkdir "tests/"
  echo "echo \"...\"" >> "tests/test_1_pravilen.sh"
  echo -e "echo \".\n.\n.\"" >> "tests/test_2_pravilen.sh"
  echo -e "echo \"______\"\nexit 1">> "tests/test_3_nepravilen.sh"
  echo -e "echo \"OI\"\nexit 1">> "tests/4_nepravilen.sh"
  chmod +x tests/*.sh
  makeFile ${1}
  createProjectAddScript
  createProjectTestScript
  #createProjectScript
fi
