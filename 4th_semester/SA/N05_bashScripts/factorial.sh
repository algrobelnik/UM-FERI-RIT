#!/bin/bash

factorial() 
{
  num=$1
  ((num++))
  echo "korak $num: $2"
  if (( $2 <= 1 )); then
    echo 1
    return 1
  else
    factorial $num $(( $2 - 1 ))
    last=$?
    echo $(( $2 * last ))
    return $(( $2 * last ))
  fi
}

factorial 0 $1
res=$?
echo "Fakulteta števila $1 je $res"
