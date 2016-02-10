#!/bin/bash

for N in 5 10 15 20
do
    echo eseguo $1"$N"V.txt con bump come CI
    ./main $1"$N"V bump
done
