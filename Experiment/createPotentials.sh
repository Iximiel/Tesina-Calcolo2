#!/bin/bash

if [ "$#" -ne 4 ]; then
    echo devi mettere 4 argomenti:
    echo NomeFile Impostazione Vpos Vpar
    echo per esempio:
    echo Gauss G 30 0.1
    echo sapendo che:
    grep "#lunghezza" settings.set -A1
else
    echo con impostazione "$2", Vpos =$3 e Vpar =$4
    for N in 5 10 15 20
    do
	echo creo il file
	Fname=$1"_""$N"V.set
	echo $Fname
	echo "#" > $Fname
	echo $2 >> $Fname
	echo "#" >> $Fname
	echo $N $3 $4 >> $Fname
    done
fi
