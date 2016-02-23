#!/bin/bash
for dT in 0.01 0.001
do
    for dS in 0.01 0.001
    do
	fname=sets$dS'_'$dT.set
	echo $fname
#	../../single free.set gauss1.set $fname
	../../single free.set gauss2.set $fname
    done
done

