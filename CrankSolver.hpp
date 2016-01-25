#ifndef _Cranck
#define _Cranck
#include "TridiagMore.hpp"
#include <string>

class CranckSolver{
public:
  CranckSolver(const tridiagM &mat, int Ns, int Nt,/* std::string opt,*/ Var CCi, Var CCe);
  ~CranckSolver();
  bool doStep();
  void SetInitialState(Var* );
  void SetDerivativeCC(Var CCdi, Var CCde, Var xstep);
  Var getPoint(int t, int x);
  bool prepareTGraph2D(std::string ,double ,double, int=1, int=1);
private:
  void Stepper();
  void processCC();
  int CCfstep, CCestep;//includo o no il primo/ultimo punto
  //  std::string options;
  Var* CS_data;//[Ns*Nt]
  Var CS_ccdi, CS_ccde, CS_Xstep;//CC sulle derivate
  Var CS_cci,CS_cce;
  int CS_nt, CS_ns;
  int CS_step;
  tridiagM CS_mat;
};

#endif //_Cranck
