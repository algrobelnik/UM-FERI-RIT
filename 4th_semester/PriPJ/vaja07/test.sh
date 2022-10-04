#!/bin/bash
pwd

newline() {
    echo -e "\n"
}

declare -r path=$(dirname $(realpath "$0"))

declare -i err=0

  for file in "$path"/positive/example{0..1000..10}.txt
  do
     echo "$file"
     #cat "$file"
     declare output=$(./run.sh "$file")
     #echo $output

      if [[ "$output" == "accept" ]]
     then
         echo -e "\n[OK]"
     else
         echo -e "\n[FAIL]"
         ((err++))
     fi
  done

  for file in "$path"/negative/example{0..1000..10}.txt
  do
      echo "$file"
      #cat "$file"
      declare output=$(./run.sh "$file")
      #echo $output

      if [[ "$output" == "reject" ]]
      then
          echo -e "\n[OK]"
      else
          echo -e "\n[FAIL]"
          ((err++))
      fi
  done

exit $err
