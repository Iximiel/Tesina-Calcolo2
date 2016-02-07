TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += "USECOMPLEX"

SOURCES += Experiment.cpp \
    impostazioni.cpp \
    TridiagMore.cpp \
    CrankSolver.cpp

HEADERS += impostazioni.hpp \
    TridiagMore.hpp \
    CrankSolver.hpp
