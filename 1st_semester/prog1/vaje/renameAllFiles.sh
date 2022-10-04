#!/usr/bin/bash

for f in *.x.x; do 
    mv -- "$f" "${f%.x.x}"
done