#include <iostream>
#include <cmath>
#include <fstream>

#include "CrankSolver.hpp"
#include "impostazioni.hpp"//contiene le costanti e il file di impostazioni
using namespace std;

void experiment(impostazioni* info, string name){
  Var eta = info->eta() * I * hbar;
  cout << "Esperimento \"" << name << "\"" << endl;
  string ifilename = name+".txt";//file del potenziale
  string ofilename = name+".dat";
  info->potentialsetting(ifilename.c_str());//ricarico il potenziale
  
  //condizioni iniziali
  tridiagM mat(info->NL());
  Var *initial = new Var[info->NL()];
  Var perV =-I*info->timeStep()/eta;//moltiplicatore del potenziale
  //imposto a d c e le CI
  Var a = -1., d = 2./eta+2., c = -1.;
  Var ak = 1., dk = 2./eta-2., ck = 1.;
  cout << "a= "<< a <<" d=" <<d << " c="<< c<<endl;
  cout << "ak= "<< ak <<" dk=" <<dk << " ck="<< c<<endl; 

  Var CCi = 0, CCe = 0;
  if(info->CCSetting(0)=='D'){
    mat.setUnknown(0,0,1,0,0);
    mat.setKnown(0,0,1,0,0);
    CCi = info->getCC0();// e` moltiplicato per a in cranksolver
  }else if(info->CCSetting(0)=='N'){
    mat.setUnknown(0,0,d - info->potenziale(0) * perV,a+c,
		   (-2.) * a * info->spaceStep() * info->getCC0());
    mat.setKnown(0,0,dk + info->potenziale(0) * perV,ak+ck,
		 (-2.) * ak * info->spaceStep() * info->getCC0());
  }else{//Robin
    mat.setUnknown(0,0,d - info->potenziale(0) * perV + 2.*a*info->spaceStep()*info->getweight0(),a+c,
		   (-2.) * a * info->spaceStep() * info->getCC0());
    mat.setKnown(0,0,dk + info->potenziale(0) * perV + 2.*ak*info->spaceStep()*info->getweight0(),ak+ck,
		 (-2.) * ak * info->spaceStep() * info->getCC0());
  }
  //primo punto di CI
  initial[0] = info->Initial(0);

  for(int j = 1;j < info->NL()-1;j++){
    initial[j] = info->Initial(j);
    mat.setUnknown(j,a,d - info->potenziale(j) * perV,c,0);
    mat.setKnown(j,ak,dk + info->potenziale(j) * perV,ck,0);
  }
  
  if(info->CCSetting(0)=='D')
    mat.SetE(1,a*info->getCC0());//si sottrae a b1
  //ultimo punto di CI
  initial[info->NL()-1] = info->Initial(info->NL()-1);
  //CC in N
  if(info->CCSetting(1)=='D'){
    mat.setUnknown(info->NL()-1,0,1,0,0);
    mat.setKnown(info->NL()-1,0,1,0,0);
    mat.SetE(info->NL()-2,c*info->getCCN());//si sottrae a bN-2
    CCe = info->getCCN();//moltiplicato per c in crancsolver
  }else if(info->CCSetting(1)=='N'){
    mat.setUnknown(info->NL()-1,a+c,d - info->potenziale(info->NL()-1) * perV,0,
		   (-2.) * c * info->spaceStep() * info->getCCN());
    mat.setKnown(info->NL()-1,ak+ck,dk + info->potenziale(info->NL()-1) * perV,0,
		 (-2.) * ck * info->spaceStep() * info->getCCN());
  }else{//Robin
    mat.setUnknown(info->NL()-1,a+c,d - info->potenziale(info->NL()-1) * perV - 2.*c*info->spaceStep()*info->getweightN(),0,
		   (-2.) * c * info->spaceStep() * info->getCCN());
    mat.setKnown(info->NL()-1,ak+ck,dk + info->potenziale(info->NL()-1) * perV -2.*ck*info->spaceStep()*info->getweightN(),0,
		 (-2.) * ck * info->spaceStep() * info->getCCN());
  }
  
  cout << "Inizializzo il Solver" <<endl;
  CrankSolver myIntegrator(mat,info->NL(),info->CCSettings(),CCi,CCe);
  cout << "Imposto le condizioni iniziali" <<endl;
  myIntegrator.SetInitialState(initial);
  cout << "Inizio i calcoli" <<endl;
  ofstream outfile(ofilename.c_str());
  int t = 0;
  bool precision = true;//controlla che l'integrale non vari troppo
  double integral = 0;//precisione voluta
  
  for(int i=0; i< info->NL();i+=info->spaceSkip()){
    double z = norm(myIntegrator.getPoint(i));
    integral +=z;
    outfile << i* info->spaceStep() << "\t" << t * info->timeStep() << "\t"
	    << z << endl;
  }

  do{
    t = myIntegrator.doStep();
    if(t%info->timeSkip()==0){
      double control = 0;
      double Time = t * info->timeStep();
      for(int i=0; i< info->NL();i+=info->spaceSkip()){
	double z = norm(myIntegrator.getPoint(i));
	control +=z;
	outfile << i* info->spaceStep() << "\t" << Time << "\t"
		<< z << endl;
      }
      precision = info->doNextStep(abs(integral-control));
    }
  }while(t<info->NT()&&precision);
  cout << "Tempo trascorso (nella simulazione): " << t*info->timeStep() <<endl;
    cout << "Scritto il file: " << ofilename <<endl;
  outfile.close();
}

int main(int argc, char** argv){
  string filename = "out.txt";
  if(argc>1)
    filename  = argv[1];
  //carico il file di impostazioni, per ricompilare meno spesso
  impostazioni *info = new impostazioni("onda.txt", "potenziale.txt", "settings.txt");

  Var eta = info->eta() * I * hbar;
  cout << "eta: "<<eta<<"=Ih/(2m)*"
       <<info->timeStep()<<"/("<<info->spaceStep()<<"^2)" <<endl;
  ifstream filenames("namelist.txt");
  while(filenames.good()){
    string fname;
    filenames >> fname;//fname non deve contenere spazi e ".txt"
    experiment(info, fname);
 } 
  filenames.close();
  cout << "Finito"<<endl;
  return 0;
}
