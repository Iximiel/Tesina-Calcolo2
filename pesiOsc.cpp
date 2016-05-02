#include "preparedraw.hpp"
#ifndef __CINT__
#include <iostream>
#include <fstream>
using namespace std;

//g++ allDataPrint.cpp `root-config --cflags --glibs`
int main(int argc, char** argv)
#endif
{
  cout<<"Carico i dati\n";
  //programma costruito ad hoc per analisisalto.sh
  int Z=4;
  char file[50];
  sprintf(file,"pesiOscg%i.tdt",Z);
  ofstream of(file);
  //impostazioni
  int npot =26, Nlarg=1;
  double Energia = 100.;
  int pot[npot];
  for (int i=0;i<26;i++)
    pot[i] = i+25;
  int larg[Nlarg]={2};
  double pesif[npot*Nlarg];//, pesis[npot*Nlarg];
  of << "ev";
  for(int j=0;j<Nlarg;j++)
    of << "\tL"<<larg[j];
  for(int i=0;i<npot;i++){
    for(int j=0;j<Nlarg;j++){
      char fname[50];
      sprintf(fname,"Osc%i_%i_gauss%i-settings.dat",pot[i],larg[j],Z);
      cout <<"*\n"<< fname << ":" << endl;	    
      preparedraw myData(fname,preparedraw::doErr);
      int N = myData.NT();
      double integral = myData.limitedIntegral(N-1,0.,(120-larg[j])/2.);
      integral *= integral;
      double tot = myData.integral(N-1);
      tot *= tot;
      pesif[Nlarg*i+j]=integral/tot;
    }
  }
  of<< endl;
  for(int i=0;i<npot;i++){
    of << Energia/pot[i];
    for(int j=0;j<Nlarg;j++){
      of << '\t'<< pesif[i*Nlarg+j];
    }
    of<< endl;
  }
  of.close();
  //delete []&pesif;
  
#ifndef __CINT__
  return 0;
#endif
}
