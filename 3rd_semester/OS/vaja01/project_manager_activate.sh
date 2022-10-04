#!/bin/bash

function helpInfo {
      echo -e "project_manager_activate version: project_manager_activate/0.0.1
Command for setting 

Usage: project_manager_activate <file name> [-?hlv] [name]

Options:
\t-?,-h   --help      : this help"
}

function echoWrongUsage {
  echo "WRONG USAGE: try project_manager_activate --help"
}

for i in "$@"
do
  if [ "${i}" = "-h" -o "${i}" = "-?" -o "${i}" = "--help" ];  then
    helpInfo
    exit 1
  else
    echoWrongUsage
    exit 1
  fi
done
export PATH="$PATH:$HOME/bin"
export PS1="%F{%(#.blue.green)}┌──${debian_chroot:+($debian_chroot)─}${VIRTUAL_ENV:+($(basename $VIRTUAL_ENV))─}(%B%F{%(#.red.blue)}%n$prompt_symbol%m%b%F{%(#.blue.green)})-[%B%F{reset}%(6~.%-1~/…/%4~.%5~)%b%F{%(#.blue.green)}]
└─%B%(#.%F{red}#.%F{blue})ProjectManager ~ "
alias project="project.sh"
alias project_new="project_new.sh"
alias project_add="project_add.sh"
alias project_test="project_test.sh"
alias project_manager_activate="project_manager_activate.sh"
