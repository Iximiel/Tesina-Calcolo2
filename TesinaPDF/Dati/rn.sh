#!/bin/bash

for j in *.dat
do
    mv $j ${j%.dat}.tdt
done
