#!/bin/bash
types=("read" "fread" "mmap")
buffer=(1 256 512 1024 2048 4096 8192 16384)
for t in "${types[@]}"; do
  echo $t
  for f in bin/*; do
    echo $f
      for b in "${buffer[@]}"; do
        echo $b
        time ./histChar.x -t $t $f >> output.txt
      done
  done
done
