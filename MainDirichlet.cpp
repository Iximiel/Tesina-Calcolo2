#include <iostream>
#include <cmath>
#include <fstream>

#include "CrankSolver.hpp"

using namespace std;

struct impostazioni{
  int Nl, spaceskip;
  double lenght, spacestep;
  double mid, stdev ,norm;
  int Nt, timeskip;
  double tmax, timestep;
  double k;
  impostazioni(string filename){
    ifstream file(filename.c_str());
    string dummy;
    file >> dummy >> k;
    file >> dummy >> lenght;
    file >> dummy >> tmax;
    file >> dummy >> norm >> stdev;
    mid = lenght/2.;
    bool Ndep;
    file >> dummy >> Ndep;
    file >> dummy >> Nl;
    file >> dummy >> spacestep;
    file >> dummy >> Nt;
    file >> dummy >> timestep;
    file >> dummy >> timeskip;
    file >> dummy >> spaceskip;
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
  double eta(){return k* timestep/(spacestep*spacestep);}
  double gauss(int i){
    double x = i*spacestep;
    return norm * exp(-(x-mid)*(x-mid)/(stdev*stdev));
  }
};

int main(int argc, char** argv){
  string filename = "out.txt";
  if(argc>1)
    filename  = argv[1];
  //carico il file di impostazioni, per ricompilare meno spesso
  impostazioni info("impostazioni.txt");
  /*
  for(int i=1;i<argc;i++){
  if(dummy.find("-") == 0)
  cout << i <<" " <<argv[i+1]<<endl;
  }
  */
  /***passo dipende da N***
  double lenght=10, tmax=10;
  int Nl = 1000, Nt = 10000;
  double spacestep = lenght/Nl;
  double timestep = tmax/Nt;
  **************************/
  /***N dipende dal passo***
  double lenght=5, tmax=0.1;
  double spacestep = 10./1000.;
  double timestep = 10./10000.;
  int Nl = lenght / spacestep;
  int Nt = tmax / timestep;
  ***********************
  double k = 1;//diffusivita`*/
  double eta = info.eta();

  /*while(eta > 1){
    cout << "Per rendere eta <1 (eta = " << eta << "), cambio k: "<< k <<" -> ";
    k /= 10;//diffusivita`
    cout << k <<endl;
     eta = k* timestep/(spacestep*spacestep);
     }*/
  
  cout << "eta: "<<eta<<"="<<info.k<<"*"
       <<info.timestep<<"/("<<info.spacestep<<"^2)" <<endl;

  //condizioni iniziali
  tridiag mat(info.Nl);
  double *initial = new double[info.Nl];
  //condizioni al contorno:
  initial[0]=0;
  mat.setUnknown(0,0,1,0);
  mat.setKnown(0,0,1,0);
  initial[info.Nl-1]=0;
  mat.setUnknown(info.Nl-1,0,1,0);
  mat.setKnown(info.Nl-1,0,1,0); 
  for(int j = 1;j< info.Nl-1;j++){
    /****
     *NB: se ho CI troppo strette,
     *un alto valore di eta rende instabile la soluzione
     ***/
    initial[j]=info.gauss(j/*+info.Nl/3*/);//+j*5./info.Nl;
    mat.setUnknown(j,-1,2./eta+2,-1);
    mat.setKnown(j,1,2./eta-2,1);
  }
  // initial[Nl/2] = 10;
  
  CranckSolver myIntegrator(mat,info.Nl,info.Nt,0,0);
  
  myIntegrator.SetInitialState(initial);
  
  while(myIntegrator.doStep());

  //preparo il file per root
  myIntegrator.prepareTGraph2D(filename,info.timestep,info.spacestep,info.timeskip,info.spaceskip);
  
  return 0;
}
