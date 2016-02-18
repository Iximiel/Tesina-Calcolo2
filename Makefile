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
#risolve un'equazione di Schodinger: come primo argonento il file del potenziale
#come secondo, opzionale, il file che indica le CI, di base e` gauss.set
single: MainC.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX
#disegna soluzione, errore e pesi dell'integrale del file di dati in argomento
drawer:drawer.cpp preparedraw.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^ $(LIBROOT) $(CFLAGSROOT)
#controlla i .dat letti in namelist.txt
analisi:analisi.cpp preparedraw.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^ $(LIBROOT) $(CFLAGSROOT)
#si comporta come maincrankC, solo che carica i nomi dei file del potenziale da
#namelist.txt, e come argomento opzionale ha il file delle CI
experiment: Experiments.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX
#visualizza vari potenziali in diversi files.
CVD: CVDrawer.cpp impostazioniC.o TridiagC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX $(LIBROOT) $(CFLAGSROOT)
#una interfaccia grafica per impostare un esperimento alla volta
gui: main.cpp Schrody.o DefineCC.o TridiagC.o CrankSolverC.o libSchrody.so libCC.so
	@echo Compilo il main
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
