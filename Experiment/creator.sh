#!/bin/bash

echo creo i file

for N in 5 10 15 20
do
    echo salto"$N"V.txt
    echo "#" >> salto"$N"V.txt
    echo S >> salto"$N"V.txt
    echo "#" >> salto"$N"V.txt
    echo $N 30 0 >> salto"$N"V.txt
done
