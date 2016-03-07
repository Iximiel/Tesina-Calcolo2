#!/bin/bash
#onda=gauss4.set
settings=settings.set
prog=../../../single

#for En in 10 25 50 60 75 90 100 110 125 200 300
for En in 10 25 50 60 75 90 100 110 125 200 300
do
    for L in 2 4 8 16 32
    do
	fSalto=Muro$En'_'$L.set
	echo $fSalto
	for N in 1 2 3 4
	do
	    onda=gauss$N.set
	    echo $onda
	    $prog $fSalto $onda $settings
	done
    done
done
