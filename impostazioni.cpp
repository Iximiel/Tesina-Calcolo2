#include "impostazioni.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

double zero(double /*x*/, double /*a*/, double /*b*/){return 0;}
double H(double x, double a, double /*b*/){return (x > a)?1:0;}
double barrier (double x, double a, double b){return H(x,a,0) * H(b,x,0);}
double gauss(double x, double a, double b){return exp(-(x-a)*(x-a)/(2*b*b));}
double bump(double x, double a, double b){return (abs(x-a)<b)?exp(-1/(b*b-(x-a)*(x-a))):0;}

impostazioni::impostazioni(const char* wavefile, const char* potentialfile, const char* simulationfile){
  wavesetting(wavefile);
  simulationsetting(simulationfile);
  potentialsetting(potentialfile);
  cout << "Condizioni iniziali:exp(-( x -" << mid
       << ")^2/(2*" << stdev << "^2))*exp(" << Ik << "* x )"<<endl;
  cout << "Energia: " << E << endl;
  cout << "Altezza potenziale:" << Vval << endl;
}
  
void impostazioni::wavesetting(const char* wavefile){
  ifstream file(wavefile);
  char nameCC[3]={'D','C','R'};
  string dummy;
  file >> dummy >> norm >> stdev;
  file >> mid;
  int icc;
  file >> dummy >> icc >> CC0 >> weight0;
  infoCC[0] = nameCC[icc];
  file >> dummy >> icc >> CCN >> weightN;
  infoCC[1] = nameCC[icc];
  file >> dummy >> E;
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
  if(Vval == 0){
    pot = zero;
    cout << "Senza potenziale" <<endl;
  }else{
    cout << "Valore potenziale: " << Vval <<endl;
    if(type == 'G'){
      pot = gauss;
      cout << "Potenzialegaussiana: valor medio:" << Vpos << ", deviazione std:" << Vpar <<endl;
    }if(type == 'M'){
      if(Vpos > Vpar){
	double temp = Vpos;
	Vpos = Vpar;
	Vpar = temp;
      }
      cout << "Salita potenziale: " << Vpos <<" discesa "<< Vpar <<endl;  
      pot = barrier;
    }else{
      cout << "Posizione Salto: " << Vpos <<endl;  
      pot = H;
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
  Ik = costanti::I * sqrt(E*2*m/(costanti::hbar*costanti::hbar));
  file.close();
}
  
double impostazioni::eta(){return timestep/(spacestep*spacestep *2 *m);}
  
double impostazioni::potenziale(int i){
  //double x = i*spacestep;
  //gradino
  double x = i*spacestep;
  return Vval*pot(x,Vpos,Vpar);
  /*    if(i>Vnum)
	return Vval;
	else
	return 0;*/
}
  
Var impostazioni::Initial(int i){//Condizione iniziale
  double x = i*spacestep;
  return /*(norm/stdev*sqrt(2*PI)) **/ bump(x,mid,stdev)*exp(Ik*x);
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
