#include <TGraph.h>
#include <TGraph2D.h>

#include <vector>
#include <complex>

using namespace std;

typedef complex<double> Var;
typedef vector<double> myV;

class preparedraw{
public:
  enum info{
    doErr = BIT(0),
    doFh = BIT(1)||BIT(0),
    doSh = BIT(2)||BIT(0),
    doMax = BIT(3)
  };
  preparedraw(std::string fname, int whatToDo);
  ~preparedraw();
  TGraph2D* data();
  TGraph* errs();
  TGraph* firsthalf();
  TGraph* secondhalf();
  TGraph* maximum();
  int NT();
  double errs(int i);
  double firsthalf(int i);
  double secondhalf(int i);
  double maximum(int i);
  double integral(int i);
  double limitedIntegral(int j, double start, double stop);
private:
  void controlErr();
  void controlFh();
  void controlSh();
  void controlMax();
  
  string name, pot, CI;
  int settings;
  //info
  int Nl,Nt, sskip, tskip;
  double sstep,atstep,tstep;
  //dati
  vector<Var> Z;
  myV integrals, before, after, times;
  myV maxs;
};
