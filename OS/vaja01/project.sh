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
DIR="$(dirname "${BASH_SOURCE}")"
for i in "$@"
do
  args[$INDEX]=$i
  let INDEX=${INDEX}+1
done
if [ ${args[0]} = "new" ] || [ ${args[0]} = "add" ] || [ ${args[0]} = "test" ] || [ "${args[0]}" = "-h" -o "${args[0]}" = "-?" -o "${args[0]}" = "--help" ];  then
  if [ "${args[0]}" = "-h" -o "${args[0]}" = "-?" -o "${args[0]}" = "--help" ];  then
    helpInfo
    exit 1
  fi
  a=2
  params=${args[1]}
  while [[ $a -lt ${#args}+1 ]]
  do
    params=${params}" ${args[$a]}"
    let a=$a+1
  done
  bash project_${args[0]}.sh $params
  if [ "$?" -eq 0 ];  then
    echo -e "sucess"
  else
    echo -e "fail"
    let FCOUNT="${FCOUNT}"+1
  fi
else
  echoWrongUsage
  exit 1
fi
