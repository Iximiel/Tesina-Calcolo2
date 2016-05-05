#!/bin/bash
#settings=m20.set
pot=free.set
prog=../../../single

for Mass in 10 20
do
    settings=msm$Mass.set
    #    for sigma in 05 1 2 4
    #    do
    #	onda=gauss$sigma.set
    for E in 10 25 50 75 100 150 200
    do
	onda=g4_E$E.set
	echo $prog $pot $onda $settings
	$prog $pot $onda $settings
    done
done
