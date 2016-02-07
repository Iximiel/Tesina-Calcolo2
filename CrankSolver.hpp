#ifndef _Crank
#define _Crank
#include "Tridiag.hpp"

//NB: questo solver non e` generalizzato per CC e V variabili nel tempo
class CrankSolver{
public:
  CrankSolver(const tridiag &mat, int Ns, const char *options, Var CCi, Var CCe);
  ~CrankSolver();
  int doStep();
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
  tridiag CS_mat;
};

#endif //_Cranck
