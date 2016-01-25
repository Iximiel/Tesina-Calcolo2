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
  tridiag& operator=(const tridiag& );
  void create_h();
  Var bi(int i, Var T_nm1,Var T_n,Var T_np1);
  Var pi(int i, Var bi, Var pim1);
  Var GetA(int i);
  Var GetD(int i);
  Var GetC(int i);
  Var GetAk(int i);
  Var GetDk(int i);
  Var GetCk(int i);
  void setUnknown(int i, Var A, Var D, Var C);
  void setKnown(int i, Var A, Var D, Var C);
  Var H(int i);
private:
  int dim;
  Var *h;
  Var *a, *d,*c;
  Var *ak, *dk,*ck;
};

#endif //_Tridiag

