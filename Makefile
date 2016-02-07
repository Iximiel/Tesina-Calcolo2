BASE	=../esercitazione1/
CC	= g++
CC11	= g++ -std=c++11
PIC	= -fPIC #(Position-Indipendent-Code) non e` detto che questa riga funzioni, su ububtu 15.10 32bit non serviva, su lubuntu 15.10 64bit non metterla non fa compilare le .so, potrebbe servire scrivere -fpic, oppure ometterla del tutto
CFLAGS	= -g -Wall
CFLAGSROOT= `root-config --cflags`
LIBROOT	= `root-config --glibs`
LDROOT	= `root-config --ldflags`

all:maincrankC

#https://root.cern.ch/interacting-shared-libraries-rootcint

main: main.cpp Schrody.o DefineCC.o TridiagC.o TridiagMoreC.o CrankSolverC.o libSchrody.so libCC.so
	@echo Compilo il main
	@$(CC11) $(CFLAGS) -o $@ -DSTANDALONE $^ $(LIBROOT) $(CFLAGSROOT)

Schrody.o: Schrody.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^ $(LIBROOT) $(CFLAGSROOT)

DefineCC.o: DefineCC.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^ $(LIBROOT) $(CFLAGSROOT)

SchrodyDict.cpp: Schrody.hpp SchrodyLinkDef.h
	@echo Chiamo rootcint per compilare la libreria $@
	@rootcint -f $@ -c $^

libSchrody.so: SchrodyDict.cpp
	@echo Compilo la libreria $@
	@$(CC) $(CFLAGS) $(PIC) -shared -o $@ `root-config --ldflags` $(CFLAGSROOT) $^

CCDict.cpp: DefineCC.hpp CCLinkDef.h
	@echo Chiamo rootcint per compilare la libreria $@
	@rootcint -f $@ -c $^

libCC.so: CCDict.cpp
	@echo Compilo la libreria $@
	@$(CC) $(CFLAGS) $(PIC) -shared -o $@ `root-config --ldflags` $(CFLAGSROOT) $^

#@echo elimino i file GuiPDEDict.*
#@rm GuiPDEDict.*

clean:
	@echo Elimino i file *.o
	@rm *.o -v


#ricordati di usare -DUSECOMPLEX!!!
crank: MainCrank.cpp crankClass.o crankTridiag.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o main crankClass.o crankTridiag.o Main.cpp

impostazioni.o: impostazioni.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^ 

impostazioniC.o: impostazioni.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c -o $@ $^ -DUSECOMPLEX

CrankSolverC.o: CrankSolver.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c -o $@ $^ -DUSECOMPLEX

TridiagC.o: Tridiag.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c -o $@ $^ -DUSECOMPLEX

TridiagMoreC.o: TridiagMore.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c -o $@ $^ -DUSECOMPLEX

CrankSolver.o: CrankSolver.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^

TridiagMore.o: TridiagMore.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^

Tridiag.o: Tridiag.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^

crankClassD.o: crankClass.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -DDEBUG -c -o $@ $^

debug: MainCrank.cpp CrankSolverD.o Tridiag.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -DDEBUG -o main $^

experiment: Experiment.cpp TridiagC.o TridiagMoreC.o CrankSolverC.o impostazioniC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o main $^  -DUSECOMPLEX
	@echo Sposto il main nella cartella apposita
	@mv main ./Experiment

maincrankC: MainC.cpp TridiagC.o TridiagMoreC.o CrankSolverC.o impostazioniC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o main $^  -DUSECOMPLEX

maincrank: Main.cpp Tridiag.o TridiagMore.o CrankSolver.o impostazioni.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o main $^

drawer:drawer.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^ $(LIBROOT) $(CFLAGSROOT)

analisi:analisi.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^ $(LIBROOT) $(CFLAGSROOT)
	@echo Sposto analisi nella cartella apposita
	@mv analisi ./Experiment
