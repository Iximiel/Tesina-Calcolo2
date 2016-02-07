TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += "USECOMPLEX"

SOURCES += \
    MainC.cpp \
    CrankSolver.cpp \
    Tridiag.cpp \
    impostazioni.cpp

HEADERS += \
    CrankSolver.hpp \
    Tridiag.hpp \
    impostazioni.hpp


DISTFILES += \
    Cimpostazioni.txt \
#    ../build-Tesina-Calcolo2-Desktop/Cimpostazioni.txt
