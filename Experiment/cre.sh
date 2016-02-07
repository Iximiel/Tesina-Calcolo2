#!/bin/bash

if [ "$#" -ne 4 ]; then
    echo devi mettere 4 argomenti:
    echo ./cre.sh NomeFile Impostazione Vpos Vpar
    echo per esempio:
    echo ./cre.sh Gauss G 30 0.1
else
    echo creo i file
    Fname=$1
    echo con impostazione "$2", Vpos =$3 e Vpar =$4
    for N in 5 10 15 20
    do
	echo $Fname"$N"V.txt
	echo "#" >> $Fname"$N"V.txt
	echo $2 >> $Fname"$N"V.txt
	echo "#" >> $Fname"$N"V.txt
	echo $N $3 $4 >> $Fname"$N"V.txt
    done
fi
