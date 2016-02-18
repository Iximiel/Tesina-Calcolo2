#!/usr/bin/env python

TMAX=10
npunti=100

for dT in [0.1,0.075,0.05,0.01,0.005,0.001,0.0001]:
    for dS in [0.1,0.01,0.001]:
	fname= "sets%s_%s.set" %(dS,dT)
        print fname
        out_file = open(fname,"w")
        out_file.write("#massa\n1\n#lunghezza\n60\n#tmax\n")
        out_file.write("%i\n"%int(TMAX))
        out_file.write("#Ndipende_da_int=0\n0\n#Nl\n10000\n#spacestep\n")
        out_file.write("%s\n"%(dS))
        out_file.write("#Nt\n1000\n#timestep\n")
        out_file.write("%s\n"%(dT))
        out_file.write("#timeskip\n")
        sskip = int(TMAX/(npunti*dT))
        out_file.write("%i\n"%(sskip))
        out_file.write("#spaceskip\n")
        out_file.write("%i\n"%(1))
        out_file.write("#precisione\n10")
