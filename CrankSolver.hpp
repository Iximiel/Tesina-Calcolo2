#ifndef _Crank
#define _Crank
#include "TridiagMore.hpp"

//NB: questo solver non e` generalizzato per CC e V variabili nel tempo
class CrankSolver{
public:
  CrankSolver(const tridiagM &mat, int Ns, int Nt, const char *options, Var CCi, Var CCe);
  ~CrankSolver();
  bool doStep();
  void SetInitialState(Var* );
  Var getPoint(int x);
private:
  void Stepper();
  char CC0, CCN;
  Var* CS_data_prec;//[Ns*Nt]
  Var* CS_data;//[Ns*Nt]
  Var CS_cci,CS_cce;
  int CS_ns;
  int CS_step;
  tridiagM CS_mat;
};

#endif //_Cranck
