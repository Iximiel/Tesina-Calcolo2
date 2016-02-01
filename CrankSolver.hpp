#ifndef _Crank
#define _Crank
#include "TridiagMore.hpp"
#include <string>
//NB: questo solver non e` generalizzato per CC e V variabili nel tempo
class CrankSolver{
public:
  CrankSolver(const tridiagM &mat, int Ns, int Nt, const char *options, Var CCi, Var CCe);
  ~CrankSolver();
  bool doStep();
  void SetInitialState(Var* );
  Var getPoint(int t, int x);
  bool prepareTGraph2D(std::string filename, double timestep, double spacestep, int timespan=1, int spacespan=1);
  bool writeEverithing(std::string filename, double timestep, double spacestep);
private:
  void Stepper();
  int CCfstep, CCestep;//includo o no il primo/ultimo punto
  char CC0, CCN;
  Var* CS_data;//[Ns*Nt]
  Var CS_ccdi, CS_ccde, CS_Xstep;//CC sulle derivate
  Var CS_cci,CS_cce;
  int CS_nt, CS_ns;
  int CS_step;
  tridiagM CS_mat;
};

#endif //_Cranck
