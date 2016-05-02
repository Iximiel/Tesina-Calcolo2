#include "CrankSolver.hpp"
#include "impostazioni.hpp"//contiene le costanti e il file di impostazioni

void experiment(impostazioni* info, std::string name, std::string ondaSet, std::string settings);

void experiment_sin(impostazioni* info, std::string name, std::string ondaSet, std::string settings, int n);

Var experiment(impostazioni* info, double Istart, double Istop);
