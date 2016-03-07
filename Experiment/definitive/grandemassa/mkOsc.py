#!/usr/bin/env python

Pos=60

#valori per rapporti 10, 4, 2, 5/3, 4/3,10/9, 1,10/11, 0.8 0.5, 1/3,
for Val in [25, 27, 30, 33, 35, 37, 40, 43, 45, 47, 50]:
    for Vpar in [2,4]:
        fname= "Osc%s_%s.set" %(Val,Vpar)
        print fname
        out_file= open(fname,"w")
        out_file.write("#tipo_Gauss_Muro_Salto\n")
        out_file.write("M\n")
        out_file.write("#impostazioni_Val_Pos_Vpar\n")
        out_file.write("%s\t%s\t%s"%(Val,Pos,Vpar))
