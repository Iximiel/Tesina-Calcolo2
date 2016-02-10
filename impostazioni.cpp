#include "impostazioni.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

double zero(double /*x*/, double /*a*/, double /*b*/){return 0;}
double gauss(double x, double a, double b){return exp(-(x-a)*(x-a)/(2*b*b));}
double bump(double x, double a, double b){return (abs(x-a)<b)? M_E*exp(-b*b/(b*b-(x-a)*(x-a))):0;}
double H(double x, double a, double /*b*/){return (x > a)?1:0;}
double barrier (double x, double a, double b){return H(x,a,0) * H(b,x,0);}

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
  if(tipo == 'B'||tipo == 'b'){
    ini = bump;
    cout << "\t\"Bump\""<<endl;
  }else{
    ini = gauss;
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
   *Muro scrivo M:  __-__
   *Salto scrovo S: __---
   */
  file >> dummy >> type;
  file >> dummy >> Vval;
  file >> Vpos >> Vpar;//posizione parametro (per muro e` la discesa, per G e` la stdev)
  pot = nullptr;
  if(Vval == 0){
    pot = &zero;
    cout << "Senza potenziale" <<endl;
  }else{
    cout << "Potenziale: " <<endl;
    cout <<"\tAltezza: " << Vval <<endl;
    switch(type){//gli switch non mi piacciono, ma non fanno dimenticare gli else
    case 'b':
    case 'B':
      pot = &bump;
      cout << "\tBump:\n\t\tpunto medio:" << Vpos << ", larghezza:" << Vpar <<endl;
      break;
    case 'g':
    case 'G':
      cout << "\tGaussiana\n\t\tpunto medio:" << Vpos << ", deviazione std:" << Vpar <<endl;
      pot = &gauss;
      break;
    case 'm':
    case 'M':
      if(Vpos > Vpar){
	double temp = Vpos;
	Vpos = Vpar;
	Vpar = temp;
      }
      cout << "\tBarriera:\n\t\tsalita: " << Vpos <<", discesa "<< Vpar <<endl;  
      pot = &barrier;
      break;
    default:
      cout << "\tSalto:\n\t\tposizione: " << Vpos <<endl;  
      pot = &H;
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
  if(error>precision){
    cout <<"Annullo per degenerazione della precisione"<<endl;
    return false;
  }else
    return true;
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
