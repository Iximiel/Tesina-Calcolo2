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



  void setUnknown(int i, Var A, Var D, Var C);
  void setKnown(int i, Var A, Var D, Var C);

protected:

};

#endif //_Tridiag

