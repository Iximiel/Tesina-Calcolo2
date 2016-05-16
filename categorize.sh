#!/bin/bash
#pensato per essere utilizzato con l'output di getInt e derivati
awk '{print $1}' Esperimento_1.tdt > tmp1.tmp

for f in Esperimento_*.tdt
do
    echo $f
    awk '{getline f1 <"tmp1.tmp";print f1,$2}' $f > tmp2.tmp
    cat tmp2.tmp > tmp1.tmp
done
cat  tmp1.tmp > data.tdt
rm tmp1.tmp tmp2.tmp
