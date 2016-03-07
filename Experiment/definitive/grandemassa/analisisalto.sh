e#!/bin/bash
#onda=gauss4.set
settings=settings.set
prog=../../../single

for En in 10 25 50 60 75 90 100 110 125 200 300
do
    fSalto=Salto$En.set
    echo $fSalto
    for N in 1 2 3 4
    do
	onda=gauss$N.set
	$prog $fSalto $onda $settings
    done
done
