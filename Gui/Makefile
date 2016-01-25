BASE	=../esercitazione1/
CC         = g++ 
CFLAGS     = -g -Wall
CFLAGSROOT = `root-config --cflags`
LIBROOT = `root-config --glibs`

all:main

main: main.cpp
	$(CC) -o main -DSTANDALONE main.cpp $(LIBROOT) $(CFLAGSROOT)

#all: Main

Main: Main.cpp ODEInt.o PuntoMaterialeInMoto.o
	$(CC) $(CFLAGS) -o main Main.cpp ODEInt.o Particella.o CampoVettoriale.o PuntoMateriale.o PuntoMaterialeInMoto.o $(LIBROOT) $(CFLAGSROOT)

geocentrismo: geocentrismo.cpp ODEInt.o PuntoMaterialeInMoto.o
	$(CC) $(CFLAGS) -o geocentrismo geocentrismo.cpp ODEInt.o Particella.o CampoVettoriale.o PuntoMateriale.o PuntoMaterialeInMoto.o $(LIBROOT) $(CFLAGSROOT)

ODESolver.o: ODESolver.cpp ODESolver.hpp
	$(CC) -c ODESolver.cpp $(CFLAGSROOT)

Particella.o: $(BASE)Particella.cpp  $(BASE)Particella.h
	$(CC) $(CFLAGS) -c  $(BASE)Particella.cpp $(CFLAGSROOT)

CampoVettoriale.o: $(BASE)CampoVettoriale.cpp $(BASE)CampoVettoriale.h
	$(CC) $(CFLAGS) -c $(BASE)CampoVettoriale.cpp $(CFLAGSROOT)

PuntoMateriale.o: $(BASE)PuntoMateriale.cpp $(BASE)PuntoMateriale.h CampoVettoriale.o Particella.o
	$(CC) $(CFLAGS) -c $(BASE)PuntoMateriale.cpp $(CFLAGSROOT)

PuntoMaterialeInMoto.o: $(BASE)PuntoMaterialeInMoto.cpp $(BASE)PuntoMaterialeInMoto.h  PuntoMateriale.o
	$(CC) $(CFLAGS) -c $(BASE)PuntoMaterialeInMoto.cpp $(CFLAGSROOT)

ODEInt.o: ODEInt.cpp  ODEInt.h
	$(CC) $(CFLAGS) -c ODEInt.cpp $(CFLAGSROOT)

clean:
	rm *.o
