#include "impostazioni.hpp"
#include <iostream>
#include <string>
#include <fstream>

namespace myfuncs{
  double zero(double /*x*/, double /*a*/, double /*b*/){return 0;}
  double sin(double x, double /*a*/, double b){return std::sin(b*x);}
  double errsin(double x, double a, double b){return std::sin(b*x)+0.01*std::sin((a*b)*x);}
  double gauss(double x, double a, double b){return exp(-(x-a)*(x-a)/(2*b*b));}
  double bump(double x, double a, double b){return (abs(x-a)<b)? M_E*exp(-b*b/(b*b-(x-a)*(x-a))):0;}
  double H(double x, double a, double /*b*/){return (x > a)?1:0;}
  double barrier (double x, double a, double b){return H(x,a,0) * H(b,x,0);}
}

using namespace std;

impostazioni::impostazioni(const char* wavefile, const char* simulationfile){
  simulationsetting(simulationfile);
  wavesetting(wavefile);
}

impostazioni::impostazioni(const char* wavefile, const char* potentialfile, const char* simulationfile){
  simulationsetting(simulationfile);
  wavesetting(wavefile);
  potentialsetting(potentialfile);
}
  
void impostazioni::wavesetting(const char* wavefile){
  ifstream file(wavefile);
  char nameCC[3]={'D','C','R'};
  string dummy;
  char tipo;
  file >> dummy >> tipo;
  cout << "Condizioni iniziali:" << endl;
  switch(tipo){
  case 'B':
  case 'b':
    ini = myfuncs::bump;
    cout << "\t\"Bump\""<<endl;
    break;
  case 'S':
  case 's':
    ini = myfuncs::sin;
    cout << "\t\"Seno\""<<endl;
    break;
  case 'E':
  case 'e':
    ini = myfuncs::errsin;
    cout << "\t\"Seno+ errore (sinusoidale)\""<<endl;
    break;
  default:
    ini = myfuncs::gauss;
    cout << "\tGaussiana"<<endl;
  }
  file >> dummy >> norm >> stdev;
  file >> mid;
  int icc;
  file >> dummy >> icc >> CC0 >> weight0;
  infoCC[0] = nameCC[icc];
  file >> dummy >> icc >> CCN >> weightN;
  infoCC[1] = nameCC[icc];
  file >> dummy >> E;
  cout << "\tEnergia: " << E << endl;
  Ik = costanti::I * sqrt(E*2*m/(costanti::hbar*costanti::hbar));
  cout<< "\tPunto centrale: " << mid
      << ", Larghezza:" << stdev << ", Parametro Ik" << Ik <<endl;
}
  
void impostazioni::potentialsetting(const char* potentialfile){
  ifstream file(potentialfile);
  string dummy;
  char type;
  /*
   *Gaussiana scrivo G
   *Bump scrivo B
   *Muro scrivo M:  __-__
   *Salto scrovo S: __---
   */
  file >> dummy >> type;
  file >> dummy >> Vval;
  file >> Vpos >> Vpar;//posizione parametro
  pot = nullptr;
  if(Vval == 0){
    pot = myfuncs::zero;
    cout << "Senza potenziale" <<endl;
  }else{
    cout << "Potenziale: " <<endl;
    cout <<"\tAltezza: " << Vval <<endl;
    switch(type){//gli switch non mi piacciono, ma non fanno dimenticare gli else
    case 'b':
    case 'B':
      pot = myfuncs::bump;
      cout << "\tBump:\n\t\tpunto medio:" << Vpos << ", larghezza:" << Vpar <<endl;
      break;
    case 'g':
    case 'G':
      cout << "\tGaussiana\n\t\tpunto medio:" << Vpos << ", deviazione std:" << Vpar <<endl;
      pot = myfuncs::gauss;
      break;
    case 'm':
    case 'M':
      //converto centro+larghezza in salita+discesa
      Vpos -= Vpar/2.;
      Vpar += Vpos;
      cout << "\tBarriera:\n\t\tsalita: " << Vpos <<", discesa "<< Vpar <<endl;  
      pot = myfuncs::barrier;
      break;
    default:
      cout << "\tSalto:\n\t\tposizione: " << Vpos <<endl;  
      pot = myfuncs::H;
    }
  }
}
  
void impostazioni::simulationsetting(const char* simulationfile){
  ifstream file(simulationfile);
  string dummy;
  file >> dummy >> m;
  file >> dummy >> lenght;
  file >> dummy >> tmax;
  bool Ndep;
  file >> dummy >> Ndep;
  file >> dummy >> Nl;
  file >> dummy >> spacestep;
  file >> dummy >> Nt;
  file >> dummy >> timestep;
  file >> dummy >> timeskip;
  file >> dummy >> spaceskip;
  file >> dummy >> precision;
  if(Ndep){
    spacestep = lenght/Nl;
    timestep = tmax/Nt;
    cout << "Passo spaziale: " << spacestep <<endl;
    cout << "Passo temporale: " << timestep <<endl;
  }else{
    Nl = lenght / spacestep;
    Nt = tmax / timestep;
    cout << "Passi spaziali: " << Nl <<endl;
    cout << "Passi temporali: " << Nt <<endl;
  }
  //protezione da errore di scrittura
  if(timeskip<1)
    timeskip = 1;
  if(spaceskip<1)
    spaceskip = 1;
  file.close();
}
  
double impostazioni::eta(){return timestep/(spacestep*spacestep *2 *m);}
  
double impostazioni::potenziale(int i){
  double x = i*spacestep;
  return Vval*pot(x,Vpos,Vpar);
}

void impostazioni::plotSettings(const char* file, double myTmax){
  //non metto i nomi dei dati
  ofstream ofile(file);
  ofile << spacestep << " " << timestep << " " << precision << endl;
  ofile << lenght << " " << tmax  << " " << myTmax << endl;
  ofile << E <<endl;
  ofile << norm << " " << mid << " " << stdev;
  ofile << Vval << " " << Vpos << " " << Vpar;
  ofile << infoCC[0] << " " << CC0 << " " << weight0;
  ofile << infoCC[1] << " " << CCN << " " << weightN;
  ofile.close();
}
  
Var impostazioni::Initial(int i){//Condizione iniziale
  double x = i*spacestep;
  return /*(norm/stdev*sqrt(2*PI)) **/norm * ini(x,mid,stdev)*exp(Ik*x);
}

bool impostazioni::doNextStep(double error){
  if(precision <=0)
    return true;
  else if(error>precision){
    cout <<"Annullo per degenerazione della precisione"<<endl;
    return false;
  }else
    return true;
}

tridiag* impostazioni::createTriMatrix(){
  tridiag *mat = new tridiag(Nl);
  Var Eta = eta() * costanti::I * costanti::hbar;
  
  cout << "eta: "<<Eta<<"=Ih/(2m)*"
       <<timestep<<"/("<<spacestep<<"^2)" <<endl;
  //moltiplicatore del potenziale
  Var perV =(timestep/Eta)*(-costanti::I/costanti::hbar);
  //imposto a d c di base
  Var a = -1., d = 2./Eta+2., c = -1.;
  Var ak = 1., dk = 2./Eta-2., ck = 1.;
  cout << "Valori di base: " << endl;
  cout << "a= "<< a <<" d=" << d << " c=" << c <<endl;
  cout << "ak= "<< ak <<" dk=" << dk << " ck=" << c <<endl;
  //CC in 0
  if(infoCC[0]=='D'){
    mat->setUnknown(0,0,1,0,0);
    mat->setKnown(0,0,1,0,0);
  }else if(infoCC[0]=='N'){
    mat->setUnknown(0,0,d - potenziale(0) * perV,a+c,
		    (-2.) * a * spacestep * CC0);
    mat->setKnown(0,0,dk + potenziale(0) * perV,ak+ck,
		  (-2.) * ak * spacestep * CC0);
  }else{//Robin
    mat->setUnknown(0,0,d - potenziale(0) * perV + 2.*a*spacestep* weight0,a+c,
		    (-2.) * a * spacestep * CC0);
    mat->setKnown(0,0,dk + potenziale(0) * perV + 2.*ak*spacestep*weight0,ak+ck,
		  (-2.) * ak * spacestep * CC0);
  }
  
  for(int j = 1;j < Nl-1;j++){
    mat->setUnknown(j,a,d - potenziale(j) * perV,c,0);
    mat->setKnown(j,ak,dk + potenziale(j) * perV,ck,0);
  }
  
  if(infoCC[0]=='D'){
    mat->SetA(1,0);
    mat->SetE(1,a*CC0  );//si sottrae a b1
  }
  //CC in N
  if(infoCC[1]=='D'){
    mat->setUnknown(Nl-1,0,1,0,0);
    mat->setKnown(Nl-1,0,1,0,0);
    mat->SetC(Nl-2,0);
    mat->SetE(Nl-2,c*CCN);//si sottrae a bN-2
  }else if(infoCC[1]=='N'){
    mat->setUnknown(Nl-1,a+c,d - potenziale(Nl-1) * perV,0,
		    (-2.) * c * spacestep * CCN);
    mat->setKnown(Nl-1,ak+ck,dk + potenziale(Nl-1) * perV,0,
		  (-2.) * ck * spacestep * CCN);
  }else{//Robin
    mat->setUnknown(Nl-1,a+c,d - potenziale(Nl-1) * perV - 2.*c*spacestep*weightN,0,
		    (-2.) * c * spacestep * CCN);
    mat->setKnown(Nl-1,ak+ck,dk + potenziale(Nl-1) * perV -2.*ck*spacestep*weightN,0,
		  (-2.) * ck * spacestep * CCN);
  }
  return mat;
}

double impostazioni::spaceStep(){return spacestep;}
double impostazioni::timeStep(){return timestep;}
int impostazioni::NT(){return Nt;}
int impostazioni::NL(){return Nl;}
int impostazioni::timeSkip(){return timeskip;}
int impostazioni::spaceSkip(){return spaceskip;}
char impostazioni::CCSetting(int i){return infoCC[i];}
char* impostazioni::CCSettings(){return infoCC;}
double impostazioni::getCC0(){return CC0;}
double impostazioni::getweight0(){return weight0;}
double impostazioni::getweightN(){return weightN;}
double impostazioni::getCCN(){return CCN;}
double impostazioni::getVheight(){return Vval;}
double impostazioni::getE(){return E;}
double impostazioni::getM(){return m;}
void impostazioni::setE(double newE){
  E = newE;
  Ik = costanti::I * sqrt(E*2*m/(costanti::hbar*costanti::hbar));
  cout <<"Nuovi parametri:\n";
  cout << "\tEnergia: " << E << endl;
  cout << "\tIk" << Ik <<endl;
}
void impostazioni::setNewVval(double val){Vval = val;}
void impostazioni::setNewIstdev(double Nstdev){
  stdev = Nstdev;
  cout <<"Nuovi parametri:\n";
  cout << "\tstdev: " << stdev << endl;
}
