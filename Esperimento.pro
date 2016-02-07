TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += "USECOMPLEX"

SOURCES += Experiment.cpp \
    impostazioni.cpp \
    CrankSolver.cpp \
    Tridiag.cpp

HEADERS += impostazioni.hpp \
    CrankSolver.hpp \
    Tridiag.hpp
