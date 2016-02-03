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
  //CC
  char infoCC[2];
  double CC0, CCN;
  double weight0, weightN;
  double precision;
  impostazioni(string filename){
    ifstream file(filename.c_str());
    string dummy;
    char nameCC[3]={'D','C','R'};
    file >> dummy >> m;
    file >> dummy >> lenght;
    file >> dummy >> tmax;
    file >> dummy >> norm >> stdev;
    file >> mid;
    int icc;
    file >> dummy >> icc >> CC0 >> weight0;
    infoCC[0] = nameCC[icc];
    file >> dummy >> icc >> CCN >> weightN;
    infoCC[1] = nameCC[icc];
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
    if(Vval == 0)
      Vnum = Nl;
    else{
      Vnum = Vpos/spacestep;
      cout << "Posizione V: " << Vnum <<endl;
    }
    Ik = I * sqrt(E*2*m/(hbar*hbar));
    V = -I * Vval/hbar;
    file.close();
  }
  double eta(){return timestep/(spacestep*spacestep *2 *m);}
  double potenziale(int i){
    //double x = i*spacestep;
    //gradino
    if(i>Vnum)
      return Vval;
    else
      return 0;
  }
  Var Initial(int i){//Condizione iniziale
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
  Var perV =-I*info.timestep/eta;//moltiplicatore del potenziale

  //imposto a d c e le CI
  Var a = -1., d = 2./eta+2., c = -1.;
  Var ak = 1., dk = 2./eta-2., ck = 1.;
  cout << "a= "<< a <<" d=" <<d << " c="<< c<<endl;
  cout << "ak= "<< ak <<" dk=" <<dk << " ck="<< c<<endl; 

  Var CCi = 0, CCe = 0;
  if(info.infoCC[0]=='D'){
    mat.setUnknown(0,0,1,0,0);
    mat.setKnown(0,0,1,0,0);
    CCi = info.CC0;// e` moltiplicato per a in cranksolver
  }else if(info.infoCC[0]=='N'){
    mat.setUnknown(0,0,d - info.potenziale(0) * perV,a+c,
		   (-2.) * a * info.spacestep * info.CC0);
    mat.setKnown(0,0,dk + info.potenziale(0) * perV,ak+ck,
		 (-2.) * ak * info.spacestep * info.CC0);
  }else{//Robin
    mat.setUnknown(0,0,d - info.potenziale(0) * perV + 2.*a*info.spacestep*info.weight0,a+c,
		   (-2.) * a * info.spacestep * info.CC0);
    mat.setKnown(0,0,dk + info.potenziale(0) * perV + 2.*ak*info.spacestep*info.weight0,ak+ck,
		 (-2.) * ak * info.spacestep * info.CC0);
  }
  //primo punto di CI
  initial[0] = info.Initial(0);
  //CC in 0
  for(int j = 1;j < info.Nl-1;j++){
    initial[j] = info.Initial(j);
    mat.setUnknown(j,a,d - info.potenziale(j) * perV,c,0);
    mat.setKnown(j,ak,dk + info.potenziale(j) * perV,ck,0);
  }
  if(info.infoCC[0]=='D')
    mat.SetE(1,a*info.CC0);//si sottrae a b1
  //ultimo punto di CI
  initial[info.Nl-1] = info.Initial(info.Nl-1);
  //CC in N
  if(info.infoCC[1]=='D'){
    mat.setUnknown(info.Nl-1,0,1,0,0);
    mat.setKnown(info.Nl-1,0,1,0,0);
    mat.SetE(info.Nl-2,c*info.CCN);//si sottrae a bN-2
    CCe = info.CCN;//moltiplicato per c in crancsolver
  }else if(info.infoCC[1]=='N'){
    mat.setUnknown(info.Nl-1,a+c,d - info.potenziale(info.Nl-1) * perV,0,
		   (-2.) * c * info.spacestep * info.CCN);
    mat.setKnown(info.Nl-1,ak+ck,dk + info.potenziale(info.Nl-1) * perV,0,
		 (-2.) * ck * info.spacestep * info.CCN);
  }else{//Robin
    mat.setUnknown(info.Nl-1,a+c,d - info.potenziale(info.Nl-1) * perV - 2.*c*info.spacestep*info.weightN,0,
		   (-2.) * c * info.spacestep * info.CCN);
    mat.setKnown(info.Nl-1,ak+ck,dk + info.potenziale(info.Nl-1) * perV -2.*ck*info.spacestep*info.weightN,0,
		 (-2.) * ck * info.spacestep * info.CCN);
  }
  
  cout << "Inizializzo il Solver" <<endl;
  CrankSolver myIntegrator(mat,info.Nl,info.infoCC,CCi,CCe);
  cout << "Imposto le condizioni iniziali" <<endl;
  myIntegrator.SetInitialState(initial);
  cout << "Inizio i calcoli" <<endl;
  ofstream outfile("todraw.txt");
  int t = 0;

  bool precision = true;//controlla che l'integrale non vari troppo
  double integral = 0;//precisione voluta
  
  for(int i=0; i< info.Nl;i+=info.spaceskip){
    double z = norm(myIntegrator.getPoint(i));
    integral +=z;
    outfile << i* info.spacestep << "\t" << t * info.timestep << "\t"
	    << z << endl;
  }

  do{
    t = myIntegrator.doStep();
    if(t%info.timeskip==0){
      double control = 0;
      for(int i=0; i< info.Nl;i+=info.spaceskip){
	double z = norm(myIntegrator.getPoint(i));
	control +=z;
	outfile << i* info.spacestep << "\t" << t * info.timestep << "\t"
		<< z << endl;
      }
      if(abs(integral-control)>info.precision){
	cout <<"Annullo per degenerazione della precisione"<<endl;
	precision = false;
      }
    }
  }while(t<info.Nt&&precision);
  outfile.close();
  cout << "Finito"<<endl;
  return 0;
}
