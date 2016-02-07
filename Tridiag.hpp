#ifndef _Tridiag
#define _Tridiag

#ifdef USECOMPLEX
#include <complex>
typedef std::complex<double> Var;
#else
typedef double Var;
#endif

struct tridiag{
public:
  tridiag(int N);
  tridiag(const tridiag& );
  virtual ~tridiag();
  tridiag& operator=(const tridiag& );
  virtual Var bi(int i, Var T_nm1,Var T_n,Var T_np1);
  Var GetA(int i);
  Var GetD(int i);
  Var GetC(int i);
  Var GetE(int i);
  Var GetAk(int i);
  Var GetDk(int i);
  Var GetCk(int i);
  Var GetEk(int i);
  Var H(int i);
  void create_h(bool lastPointDirichlet=false);
  Var pi(int i, Var bi, Var pim1);
  void SetE(int i, Var E);
  void SetEk(int i, Var E);
  void setUnknown(int i, Var A, Var D, Var C, Var E);
  void setKnown(int i, Var A, Var D, Var C, Var E);
protected:
  int dim;
  Var *h;
  Var *a, *d,*c;
  Var *ak, *dk,*ck;
  Var *e;
  Var *ek;
};

#endif //_Tridiag
