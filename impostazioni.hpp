#ifndef _Impostazioni
#define _Impostazioni

#ifndef _Tridiag
#ifdef USECOMPLEX
#include <complex>
typedef std::complex<double> Var;
#else
typedef double Var;
#endif
#endif

#ifdef USECOMPLEX
const Var I(0,1);
#else
const Var I=1.;
#endif

const double PI = 4*atan(1);
const double hbar = 1;

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
public:
  impostazioni(const char* wavefile, const char* potentialfile, const char* simulationfile);
  void wavesetting(const char* wavefile);
  void potentialsetting(const char* potentialfile);
  void simulationsetting(const char* simulationfile);
  double eta();
  double potenziale(int i);
  const double spaceStep();
  const double timeStep();
  const int NT();
  const int NL();
  const int timeSkip();
  const int spaceSkip();
  const char CCSetting(int i);
  const char* CCSettings();
  const double getCC0();
  const double getweight0();
  const double getweightN();
  const double getCCN();
  bool doNextStep(double error);
  Var Initial(int i);
};

#endif //_Impostazioni
