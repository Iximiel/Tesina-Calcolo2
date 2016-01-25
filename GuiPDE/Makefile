BASE	=../esercitazione1/
CC	= g++
CC11	= g++ -std=c++11
CFLAGS	= -g -Wall
CFLAGSROOT= `root-config --cflags`
LIBROOT	= `root-config --glibs`
LDROOT	= `root-config --ldflags`

all:main

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
