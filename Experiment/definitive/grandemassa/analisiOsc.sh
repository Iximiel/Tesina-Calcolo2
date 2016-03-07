#!/bin/bash
#onda=gauss4.set
settings=settings.set
prog=../../../single

#for En in  25 27 30 33 35 37 40 43 45 47 50
for En in  27 33 37 43 47
do
    for L in 2 4
    do
	fSalto=Osc$En'_'$L.set
	echo $fSalto
	for N in 1 2 3 4
	do
	    onda=gauss$N.set
	    echo $onda
	    $prog $fSalto $onda $settings
	done
    done
done
