#ifndef _TridiagMore
#define _TridiagMore

#include "Tridiag.hpp"

struct tridiagM : public tridiag{
public:
  tridiagM(int N);
  tridiagM(const tridiagM& );
  tridiagM(const tridiag& );
  tridiagM& operator=(const tridiagM& );
  // tridiagM& operator=(const tridiag& );
  Var bi(int i, Var T_nm1,Var T_n,Var T_np1);
  Var GetE(int i);
  Var GetEk(int i);
  void setUnknown(int i, Var A, Var D, Var C, Var E);
  void setKnown(int i, Var A, Var D, Var C, Var E);
protected:
  Var *e;
  Var *ek;
};

#endif //_TridiagMore
