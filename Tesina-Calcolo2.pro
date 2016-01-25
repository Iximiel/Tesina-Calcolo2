TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += "USECOMPLEX"

SOURCES += \
    MainC.cpp \
    CrankSolver.cpp \
    TridiagMore.cpp \
    Tridiag.cpp

HEADERS += \
    CrankSolver.hpp \
    TridiagMore.hpp \
    Tridiag.hpp


DISTFILES += \
    Cimpostazioni.txt
