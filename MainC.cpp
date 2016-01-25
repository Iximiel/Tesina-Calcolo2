#include <iostream>
#include <cmath>
#include <fstream>

#include "CrankSolver.hpp"

using namespace std;

const double PI = 4*atan(1);

struct impostazioni{
  int Nl, spaceskip;
  double lenght, spacestep;
  double mid, stdev ,norm;
  double Vpos, Vmod;
  int Vnum;
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
    file >> dummy >> Vpos >> Vmod;
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
    if(Vmod == 0)
      Vnum = Nl;
    else{
      Vnum = Vpos/spacestep;
      cout << "Posizione V: " << Vnum <<endl;
    }
    file.close();
  }
  double eta(){return k* timestep/(spacestep*spacestep);}
  Var gauss(int i){//Condizione iniziale
    double x = i*spacestep;
    return (norm/stdev*sqrt(2*PI)) * exp(-(x-mid)*(x-mid)/(2*stdev*stdev))*exp(.1*Var(0,1)*x);
  }
};

int main(int argc, char** argv){
  string filename = "out.txt";
  if(argc>1)
    filename  = argv[1];
  //carico il file di impostazioni, per ricompilare meno spesso
  impostazioni info("Cimpostazioni.txt");
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
  Var eta = info.eta() * Var(0,1);
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
  Var *initial = new Var[info.Nl];
  //condizioni al contorno:
  Var a = -1., d = 2./eta+2., c = -1.;
  Var ak = 1., dk = 2./eta-2., ck = 1.;
  initial[0] = info.gauss(0);
  mat.setUnknown(0,0,d,a+c,0);
  mat.setKnown(0,0,dk,ak+ck,0);
  for(int j = 1;j< info.Nl-1;j++){
    if(j==info.Vnum){
      d -= info.Vmod * info.timestep/eta ;
      dk+= info.Vmod * info.timestep/eta;
    }
    /****
     *NB: se ho CI troppo strette,
     *un alto valore di eta rende instabile la soluzione
     ***/
    /* if(j==3*info.Nl/4){
      d = 2./(eta*5)+2;
      dk = 2./(eta*5)-2;
      }*/
    initial[j] = info.gauss(j);//+j*5./info.Nl;
    mat.setUnknown(j,a,d,c,0);
    mat.setKnown(j,ak,dk,ck,0);
  }
  // int set =3*info.Nl/4;
  //  mat.setKnown(set,ak,dk,ck,0.1);
  initial[info.Nl-1] = info.gauss(info.Nl-10);
  mat.setUnknown(info.Nl-1,a+c,d,0.,0.);
  mat.setKnown(info.Nl-1,ak+ck,dk,0.,0.);
  
  // initial[Nl/2] = 10;
  Var df0 = 0, dfN = -0;
  Var CCi = 2*info.spacestep*(a - ak)*df0;
  Var CCe =- 2*info.spacestep*(c - ck)*dfN;
  cout << "Inizializzo il Solver" <<endl;
  CranckSolver myIntegrator(mat,info.Nl,info.Nt,CCi,CCe);
  cout << "Imposto le condizioni iniziali" <<endl;
  myIntegrator.SetInitialState(initial);
  cout << "Inizio i calcoli" <<endl;
  while(myIntegrator.doStep());

  //preparo il file per root
  myIntegrator.prepareTGraph2D(filename,info.timestep,info.spacestep,info.timeskip,info.spaceskip);
  
  return 0;
}
