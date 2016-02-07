#!/bin/bash

echo creo i file

for N in 5 10 15 20
do
    echo saltom"$N"V.txt
    echo "#" >> saltom"$N"V.txt
    echo S >> saltom"$N"V.txt
    echo "#" >> saltom"$N"V.txt
    echo "-"$N 30 0 >> saltom"$N"V.txt
done
