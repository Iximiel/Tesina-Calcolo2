#!/usr/bin/env python

Pos=60

#valori per rapporti 10, 4, 2, 5/3, 4/3,10/9, 1,10/11, 0.8 0.5, 1/3,
for Val in [10, 25, 50, 60, 75, 90 ,100, 110, 125, 200, 300]:
    for Vpar in [2,4,8,16,32]:
        fname= "Muro%s_%s.set" %(Val,Vpar)
        print fname
        out_file= open(fname,"w")
        out_file.write("#tipo_Gauss_Muro_Salto\n")
        out_file.write("M\n")
        out_file.write("#impostazioni_Val_Pos_Vpar\n")
        out_file.write("%s\t%s\t%s"%(Val,Pos,Vpar))
