#ifndef _Impostazioni
#define _Impostazioni
#include "Tridiag.hpp"
#include <cmath>

namespace costanti{
#ifdef USECOMPLEX
  const Var I(0,1);
#else
  const Var I=1.;
#endif

  const double PI = 4*atan(1);
  const double hbar = 1;
}

class impostazioni{
private:
  int Nl, spaceskip;
  double lenght, spacestep;
  double mid, stdev ,norm;
  double Vpos, Vval, Vpar;
  double E;
  int Nt, timeskip;
  double tmax, timestep;
  double m;
  Var Ik;
  //CC
  char infoCC[2];
  double CC0, CCN;
  double weight0, weightN;
  double precision;
  double (*pot)(double,double,double);
  double (*ini)(double,double,double);
public:
  impostazioni(const char* wavefile, const char* potentialfile, const char* simulationfile);
  impostazioni(const char* wavefile, const char* simulationfile);
  void wavesetting(const char* wavefile);
  void potentialsetting(const char* potentialfile);
  void simulationsetting(const char* simulationfile);
  void plotSettings(const char*, double);
  double eta();
  double potenziale(int i);
  double spaceStep();
  double timeStep();
  int NT();
  int NL();
  int timeSkip();
  int spaceSkip();
  char CCSetting(int i);
  char* CCSettings();
  double getCC0();
  double getweight0();
  double getweightN();
  double getCCN();
  bool doNextStep(double error);
  tridiag* createTriMatrix();
  Var Initial(int i);
};

#endif //_Impostazioni
