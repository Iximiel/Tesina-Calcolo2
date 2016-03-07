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
  ofstream of("pesi.dat");
  //impostazioni
  int npot =11, Nonda=4;
  double Energia = 100.;
  //
  double pesif[npot*Nonda], pesis[npot*Nonda];
  int pot[npot]={10,25,50,60,75,90,100,110,125,200,300};
  int onda[Nonda]={1,2,3,4};
  of << "ev";
  for(int j=0;j<Nonda;j++)
    of << "\tfhS"<<onda[j]<< "\tshS"<<onda[j];
  
  for(int i=0;i<npot;i++){
    for(int j=0;j<Nonda;j++){

      char fname[50];
      sprintf(fname,"Salto%i_gauss%i-settings.dat",pot[i],onda[j]);
      cout <<"*\n"<< fname << ":" << endl;
	    
      preparedraw myData(fname,preparedraw::doFh|preparedraw::doSh);
      cout << Nonda*i+j << " " << npot*Nonda<<endl;
      int N = myData.NT();
      pesif[Nonda*i+j]=myData.firsthalf(N-1);
      pesis[Nonda*i+j]=myData.secondhalf(N-1);
    }
  }
  of<< endl;
  for(int i=0;i<npot;i++){
    of << Energia/pot[i];
    for(int j=0;j<Nonda;j++){
      of << '\t'<< pesif[i*Nonda+j]<< '\t'<< pesis[i*Nonda+j];
    }
    of<< endl;
  }
  of.close();
#ifndef __CINT__
  return 0;
#endif
}
