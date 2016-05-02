#!/bin/bash

awk '{print $1}' tunnel50.tdt > tmp1.tmp

for f in tunnel*.tdt
do
    echo $f
    awk '{getline f1 <"tmp1.tmp";print f1,$2}' $f > tmp2.tmp
    cat tmp2.tmp > tmp1.tmp
done
cat  tmp1.tmp > datatunnel.tdt
rm tmp1.tmp tmp2.tmp
