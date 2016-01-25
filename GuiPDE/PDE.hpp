#ifndef myPDECond
#define myPDECond
class PDECond{
public:
  enum Method{mSOR=0,mGaussSeidel=1,mJacobi=2};
  PDECond();
  ~PDECond();
  double Passo();
  void SetXY(int x,int y, double xdim, double ydim);
  void SetMethod(int m, double sor);
  void SetPrecisionOnErrMax(double);
  void SetCI(double ci);
  void SetCC(int posy, int posx);//distanze dal centro
  void SetCC(double lenght, double dist);
  int GetNum();
  double** GetData();
  double GetData(int x, int y);
  double GetPassoX();
  double GetPassoY();
private:
  double Jacobi(int, int);
  double GaussSeidel(int, int);
  double SOR(int, int);
  void setupCC();
  double getErr();
  double SOR_par;
  double peso_errMax;
  double **cc, **succ, **prec;
  double Eps, rho, Delq;
  double Xdim, Ydim, passoX, passoY, CI;
  int X,Y;//dimensioni
  int M;
};
#endif //myPDECond
