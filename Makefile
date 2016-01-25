BASE	=../esercitazione1/
CC	= g++
CC11	= g++ -std=c++11
CFLAGS	= -g -Wall
CFLAGSROOT= `root-config --cflags`
LIBROOT	= `root-config --glibs`
LDROOT	= `root-config --ldflags`

all:maincrankC

#https://root.cern.ch/interacting-shared-libraries-rootcint

main: mainPDE.cpp GuiPDE.o PDE.o libPDE.so
	@echo Compilo il main
	@$(CC) $(CFLAGS) -o $@ -DSTANDALONE $^ $(LIBROOT) $(CFLAGSROOT)

GuiPDE.o: GuiPDE.cpp
	@echo Compilo $@
	@$(CC) $(CFLAGS) -c $^ $(LIBROOT) $(CFLAGSROOT)

PDE.o: PDE.cpp
	@echo Compilo $@
	@$(CC11) $(CFLAGS) -c $^

GuiPDEDict.cpp: GuiPDE.hpp GuiPDELinkDef.h
	@echo Chiamo rootcint per compilare le librerie
	@rootcint -f $@ -c $^

libPDE.so: GuiPDEDict.cpp
	@echo Compilo le librerie
	@$(CC) $(CFLAGS) -shared -o$@ `root-config --ldflags` $(CFLAGSROOT) $^

#@echo elimino i file GuiPDEDict.*
#@rm GuiPDEDict.*

clean:
	@echo Elimino i file *.o
	@rm *.o -v


#ricordati di usare -DUSECOMPLEX!!!
crank: MainCrank.cpp crankClass.o crankTridiag.o
	$(CC11) $(CFLAGS) -o main crankClass.o crankTridiag.o Main.cpp

CrankSolverC.o: CrankSolver.cpp
	$(CC11) $(CFLAGS) -c -o $@ $^ -DUSECOMPLEX

TridiagC.o: Tridiag.cpp
	$(CC11) $(CFLAGS) -c -o $@ $^ -DUSECOMPLEX

TridiagMoreC.o: TridiagMore.cpp
	$(CC11) $(CFLAGS) -c -o $@ $^ -DUSECOMPLEX

CrankSolver.o: CrankSolver.cpp
	$(CC11) $(CFLAGS) -c $^

TridiagMore.o: TridiagMore.cpp
	$(CC11) $(CFLAGS) -c $^

Tridiag.o: Tridiag.cpp
	$(CC11) $(CFLAGS) -c $^

debug: MainCrank.cpp CrankSolverD.o Tridiag.o
	$(CC11) $(CFLAGS) -DDEBUG -o main $^

maincrankC: MainC.cpp TridiagC.o TridiagMoreC.o CrankSolverC.o
	$(CC11) $(CFLAGS) -o main $^  -DUSECOMPLEX

maincrank: Main.cpp Tridiag.o TridiagMore.o CrankSolver.o
	$(CC11) $(CFLAGS) -o main $^

crankClassD.o: crankClass.cpp
	$(CC11) $(CFLAGS) -DDEBUG -c -o $@ $^

drawer:rootdrawComplex.cpp
	$(CC11) $(CFLAGS) -o $@ $^ $(LIBROOT) $(CFLAGSROOT)
