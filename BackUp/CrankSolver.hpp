#ifndef _Cranck
#define _Cranck
#include "Tridiag.hpp"
#include <string>

class CranckSolver{
public:
  CranckSolver(const tridiag &mat, int Ns, int Nt, Var CCi, Var CCe);
  ~CranckSolver();
  bool doStep();
  void SetInitialState(Var* );
  void SetDerivativeCC(Var CCdi, Var CCde, Var xstep);
  Var getPoint(int t, int x);
  bool prepareTGraph2D(std::string ,double ,double, int=1, int=1);
private:
  void Stepper();
  double* CS_data;//[Ns*Nt]
  bool doProcessCC;//le CC basate sulle derivate
  Var CS_ccdi, CS_ccde, CS_Xstep;//CC sulle derivate
  void processCC();
  Var CS_cci,CS_cce;
  int CS_nt, CS_ns;
  int CS_step;
  tridiag CS_mat;
};

#endif //_Cranck
