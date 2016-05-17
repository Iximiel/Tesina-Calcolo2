CC	= g++
CC11	= g++ -std=c++11
CFLAGS	= -g -Wall
DIR	= Experiment
#Root
CFLAGSROOT= `root-config --cflags`
LIBROOT	= `root-config --glibs`
LDROOT	= `root-config --ldflags`
#####Position-Indipendent-Code
PIC	= -fPIC
#non e` detto che questa riga funzioni, su ubuntu 15.10_32bit non e` necessaria.
#su lubuntu 15.10 64bit non metterla non fa compilare le .so
#potrebbe servire scrivere -fpic, oppure ometterla del tutto
#####Position-Indipendent-Code
all:single drawer analisi experiment getInt

#https://root.cern.ch/interacting-shared-libraries-rootcint
#il progamma principale --help per aiuto
single: MainC.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX
#funziona come single, ma ripete l'esperimento per una lista di potenziali
#--help per aiuto
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
#un'interfaccia grafica per osservare un esperimento alla volta
#permette di fare qualche analisi sulla dispersione e salvare delle immagini
preview: preview.cpp visual.o libVisual.so
	@echo Compilo $@ 
	@$(CC11) $(CFLAGS) -o $@ -DSTANDALONE $^ $(LIBROOT) $(CFLAGSROOT)
#come analisi limitato alla velocita` salva i risultati nel file "datavel.txt"
getVel:getVel.cpp preparedraw.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^ $(LIBROOT) $(CFLAGSROOT)
#svolgono tutta la simulazione e salvano solo il risultato,
#utilizzare categorize.sh per raccogliere i risultati in un unico file
getInt: getIntR getIntD getIntS getIntSR

#lo ho utilizzato per costruire alcune gif
doSin: sinStudy.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX

getIntD: saveOnlyInt.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX

getIntR: saveOnlyInt.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX -DREGULAR

getIntS: saveOnlyInt.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX -DSIGMA

getIntSR: saveOnlyInt.cpp TridiagC.o CrankSolverC.o impostazioniC.o experimentC.o
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -o $@ $^  -DUSECOMPLEX -DREGULAR -DSIGMA

visualDict.cpp: visual.hpp visualLinkDef.h
	@echo Chiamo rootcint per compilare la libreria $@
	@rootcint -f $@ -c $^

libVisual.so: visualDict.cpp
	@echo Compilo la libreria $@
	@$(CC) $(CFLAGS) $(PIC) -shared -o $@ `root-config --ldflags` $(CFLAGSROOT) $^

#ricordati di usare -DUSECOMPLEX!!!
visual.o: visual.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^ $(CFLAGSROOT)

preparedraw.o: preparedraw.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^ $(CFLAGSROOT)

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

clean:
	@echo Elimino i file *.o
	@rm *.o -v
