#!/usr/bin/env python

for En in [10, 25, 50, 75, 100, 150, 200]:
        fname= "g4_E%s.set" %(En)
        print fname
        out_file= open(fname,"w")
        out_file.write("#Bump_Gauss\n")
        out_file.write("G\n")
        out_file.write("#impostazioni_onda_norm_stdev_midpoint\n")
        out_file.write("1 4 40\n")
        out_file.write("#impostazionicc0_012DCR_val_pesorobin\n")
        out_file.write("0 0 0\n")
        out_file.write("#impostazioniccN_012DCR_val_pesorobin\n")
        out_file.write("0 0 0\n")
        out_file.write("#Energia\n")
        out_file.write("%s"%(En))
