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
    file >> mid;
    //    mid = lenght/2.;
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
  Var eta = info.eta();

  /*while(eta > 1){
    cout << "Per rendere eta <1 (eta = " << eta << "), cambio k: "<< k <<" -> ";
    k /= 10;//diffusivita`
    cout << k <<endl;
     eta = k* timestep/(spacestep*spacestep);
     }*/
  
  cout << "eta: "<<eta<<"="<<info.k<<"*"
       <<info.timestep<<"/("<<info.spacestep<<"^2)" <<endl;

  //condizioni iniziali
  tridiagM mat(info.Nl);
  Var *initial = new double[info.Nl];
  //condizioni al contorno:
  Var a = -1, d = 2./eta+2, c = -1;
  Var ak = 1, dk = 2./eta-2, ck = 1;
  initial[0] = 0*info.gauss(0);
  mat.setUnknown(0,0,d,a+c,0);
  mat.setKnown(0,0,dk,ak+ck,0);
  for(int j = 1;j< info.Nl-1;j++){
    /****
     *NB: se ho CI troppo strette,
     *un alto valore di eta rende instabile la soluzione
     ***/
    /* if(j==3*info.Nl/4){
      d = 2./(eta*5)+2;
      dk = 2./(eta*5)-2;
      }*/
    initial[j]=0*info.gauss(j);//+j*5./info.Nl;
    mat.setUnknown(j,a,d,c,0);
    mat.setKnown(j,ak,dk,ck,0);
  }
  int set =3*info.Nl/4;
  mat.setKnown(set,ak,dk,ck,0.1);
  initial[info.Nl-1]=0*info.gauss(info.Nl-1);
  mat.setUnknown(info.Nl-1,a+c,d,0.,0.);
  mat.setKnown(info.Nl-1,ak+ck,dk,0.,0.);
  
  // initial[Nl/2] = 10;
  double df0 = 0, dfN = -0;
  double CCi = 2*info.spacestep*(a - ak)*df0;
  double CCe = - 2*info.spacestep*(c - ck)*dfN;
  CranckSolver myIntegrator(mat,info.Nl,info.Nt,CCi,CCe);
  
  myIntegrator.SetInitialState(initial);
  
  while(myIntegrator.doStep());

  //preparo il file per root
  myIntegrator.prepareTGraph2D(filename,info.timestep,info.spacestep,info.timeskip,info.spaceskip);
  
  return 0;
}
