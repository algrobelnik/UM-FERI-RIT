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
args=($@)
if [[ "${1}" = "-h" ]] || [[ "${1}" = "-?" ]] || [[ "${1}" = "--help" ]];  then
  helpInfo
  exit 1
fi
if [[ ${1} = "new" ]] || [[ ${1} = "add" ]] || [[ ${1} = "test" ]];  then
  bash project_${1}.sh ${args[@]:1}
else
  echoWrongUsage
  exit 1
fi
