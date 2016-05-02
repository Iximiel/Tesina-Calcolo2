#!/bin/bash
awk '{print $1}' Osc2_4.tdt > DataOsc4.tdt

for f in Osc*_4.tdt
do
    awk '{getline f1 <"DataOsc4.tdt";print f1,$2}' $f >Osc_p.tmp
    cat Osc_p.tmp > DataOsc4.tdt
done
rm Osc_p.tmp
