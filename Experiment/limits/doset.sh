#!/bin/bash
for dT in 0.1 0.075 0.05 0.01 0.001 0.0001
do
    for dS in 0.1 0.01 0.001
    do
	fname=sets$dS'_'$dT.set
	echo $fname
	../../single free.set gauss1.set $fname
	../../single free.set gauss2.set $fname
    done
done

