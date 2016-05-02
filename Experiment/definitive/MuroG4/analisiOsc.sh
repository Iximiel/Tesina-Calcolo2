#!/bin/bash
#onda=gauss4.set
settings=settings.set
prog=../../../single

for fSalto in Osc*_2.set
do
    onda=gauss4.set
    echo $prog $fSalto $onda $settings
    $prog $fSalto $onda $settings
done
