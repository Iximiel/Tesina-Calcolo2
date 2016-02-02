#include <iostream>
#include <cmath>
#include <fstream>

#include "CrankSolver.hpp"

using namespace std;

const double PI = 4*atan(1);
const Var I(0,1);
const double hbar = 1;

struct impostazioni{
  int Nl, spaceskip;
  double lenght, spacestep;
  double mid, stdev ,norm;
  double Vpos, Vval;
  Var V;
  double E;
  int Vnum;
  int Nt, timeskip;
  double tmax, timestep;
  double m;
  Var Ik;
  impostazioni(string filename){
    ifstream file(filename.c_str());
    string dummy;
    file >> dummy >> m;
    file >> dummy >> lenght;
    file >> dummy >> tmax;
    file >> dummy >> norm >> stdev;
    file >> mid;
    //    mid = lenght/2.;
    file >> dummy >> Vpos >> Vval;
    file >> dummy >> E;
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
    if(Vval == 0)
      Vnum = Nl;
    else{
      Vnum = Vpos/spacestep;
      cout << "Posizione V: " << Vnum <<endl;
    }
    Ik = I * sqrt(E*2*m/(hbar*hbar));
    V = -I *Vval/hbar;
    file.close();
  }
  double eta(){return timestep/(spacestep*spacestep *2 *m);}
  Var gauss(int i){//Condizione iniziale
    double x = i*spacestep;
    return /*(norm/stdev*sqrt(2*PI)) **/ exp(-(x-mid)*(x-mid)/(2*stdev*stdev))*exp(Ik*x);
  }
};

int main(int argc, char** argv){
  string filename = "out.txt";
  if(argc>1)
    filename  = argv[1];
  //carico il file di impostazioni, per ricompilare meno spesso
  impostazioni info("Cimpostazioni.txt");

  Var eta = info.eta() * I * hbar;
  
  cout << "eta: "<<eta<<"=Ih/(2"<<info.m<<")*"
       <<info.timestep<<"/("<<info.spacestep<<"^2)" <<endl;

  //condizioni iniziali
  tridiagM mat(info.Nl);
  Var *initial = new Var[info.Nl];
  //condizioni al contorno:
  Var a = -1., d = 2./eta+2., c = -1.;
  Var ak = 1., dk = 2./eta-2., ck = 1.;
  cout << "a= "<< a <<" d=" <<d << " c="<< c<<endl;
  cout << "ak= "<< ak <<" dk=" <<dk << " ck="<< c<<endl;
  
  initial[0] = info.gauss(0);
  mat.setUnknown(0,0,d,a+c,0);
  mat.setKnown(0,0,dk,ak+ck,0);
  for(int j = 1;j< info.Nl-1;j++){
    if(j==info.Vnum){
      d -= info.V * info.timestep/eta;
      dk+= info.V * info.timestep/eta;
      cout << "new d = "<< d <<"\nnew dk = " << dk <<endl;
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
  CrankSolver myIntegrator(mat,info.Nl,"RR",CCi,CCe);
  cout << "Imposto le condizioni iniziali" <<endl;
  myIntegrator.SetInitialState(initial);
  cout << "Inizio i calcoli" <<endl;
  ofstream outfile("out.txt");
  int t = 0;
  for(int i=0; i< info.Nl;i+=10){
    outfile << i* info.spacestep << "\t" << 0 << "\t"
	    << norm(myIntegrator.getPoint(i));
  }
  do{
    t = myIntegrator.doStep();
    if(t%info.timeskip==0||t == 1){
      for(int i=0; i< info.Nl;i+=info.spaceskip){
	outfile << i* info.spacestep << "\t" << t* info.timestep << "\t"
		<< norm(myIntegrator.getPoint(i)) << endl;
      }
    }
  }while(t<info.Nt);
  cout << "Finito"<<endl;
  outfile.close();
  
  return 0;
}
