CC	= g++
CC11	= g++ -std=c++11
CFLAGS	= -g -Wall
DIR	= Experiment
#Root
CFLAGSROOT= `root-config --cflags`
LIBROOT	= `root-config --glibs`
LDROOT	= `root-config --ldflags`
#Position-Indipendent-Code
PIC	= -fPIC
#non e` detto che questa riga funzioni, su ubuntu 15.10_32bit non e` necessaria.
#su lubuntu 15.10 64bit non metterla non fa compilare le .so
#potrebbe servire scrivere -fpic, oppure ometterla del tutto
all:single drawer analisi experiment

#https://root.cern.ch/interacting-shared-libraries-rootcint
#il progama principale
single: MainC.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX
#funziona come single, ma ripete l'esperimento per una lista di potenziali
experiment: Experiments.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX
#disegna soluzione, errore e pesi dell'integrale del file di dati in argomento
drawer:drawer.cpp preparedraw.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^ $(LIBROOT) $(CFLAGSROOT)
#controlla i .dat letti in namelist.txt, varie opzioni con --help
analisi:analisi.cpp preparedraw.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^ $(LIBROOT) $(CFLAGSROOT)
#visualizza vari potenziali in diversi files
CVD: CVDrawer.cpp impostazioniC.o TridiagC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX $(LIBROOT) $(CFLAGSROOT)
#una interfaccia grafica per osservare un esperimento alla volta
preview: preview.cpp visual.o libVisual.so
	@echo Compilo $@ 
	@$(CC11) $(CFLAGS) -o $@ -DSTANDALONE $^ $(LIBROOT) $(CFLAGSROOT)

doSin: sinStudy.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX

getInt: saveOnlyInt.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX

pesi:pesi.cpp preparedraw.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^ $(LIBROOT) $(CFLAGSROOT)

pesiMuro:pesiMuro.cpp preparedraw.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^ $(LIBROOT) $(CFLAGSROOT)

pesiOsc:pesiOsc.cpp preparedraw.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^ $(LIBROOT) $(CFLAGSROOT)

gui: main.cpp Schrody.o DefineCC.o TridiagC.o CrankSolverC.o libSchrody.so libCC.so
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ -DSTANDALONE $^ $(LIBROOT) $(CFLAGSROOT)

install: single drawer CVD experiment analisi
	@echo Sposto i programmi nella cartella Experiment
	@cp $? ./$(DIR) -v

Schrody.o: Schrody.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^ $(LIBROOT) $(CFLAGSROOT)

DefineCC.o: DefineCC.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^ $(LIBROOT) $(CFLAGSROOT)

visualDict.cpp: visual.hpp visualLinkDef.h
	@echo Chiamo rootcint per compilare la libreria $@
	@rootcint -f $@ -c $^

libVisual.so: visualDict.cpp
	@echo Compilo la libreria $@
	@$(CC) $(CFLAGS) $(PIC) -shared -o $@ `root-config --ldflags` $(CFLAGSROOT) $^

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

#ricordati di usare -DUSECOMPLEX!!!
visual.o: visual.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^ $(CFLAGSROOT)

preparedraw.o: preparedraw.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^ $(CFLAGSROOT)

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

experimentC.o: experiment.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c -o $@ $^ -DUSECOMPLEX

CrankSolver.o: CrankSolver.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^

Tridiag.o: Tridiag.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^

experiment.o: experiment.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^

#riolve l'equazione del calore
maincrank: Main.cpp Tridiag.o CrankSolver.o impostazioni.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o main $^

clean:
	@echo Elimino i file *.o
	@rm *.o -v
