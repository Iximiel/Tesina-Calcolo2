#include <iostream>
#include <cmath>
#include <fstream>

#include "CrankSolver.hpp"
#include "impostazioni.hpp"//contiene le costanti e il file di impostazioni
using namespace std;

void experiment(impostazioni* info, string name, string ondaSet){
  cout << "Esperimento \"" << name << "\"" << endl;

  info->potentialsetting((name+".set").c_str());

  //imposto la matrice
  tridiag *mat = info->createTriMatrix();
  Var *initial = new Var[info->NL()];

  //imposto le CI
  if(info->CCSetting(0)=='D')
    initial[0] = info->getCC0();
  else
    initial[0] = info->Initial(0);
  
  for(int j = 1;j < info->NL()-1;j++)
    initial[j] = info->Initial(j);

  if(info->CCSetting(1)=='D')
    initial[info->NL()-1] = info->getCCN();
  else
    initial[info->NL()-1] = info->Initial(info->NL()-1);
  
  
  cout << "Inizializzo il Solver" <<endl;
  CrankSolver *myIntegrator = new CrankSolver(mat,info->NL());
  cout << "Imposto le condizioni iniziali" <<endl;
  myIntegrator->SetInitialState(initial);
  name+="_"+ondaSet;
  //file in una cartella superiore
  name = "./results/"+name;
  cout << "Inizio i calcoli, salvo su "<< name << ".dat" << endl;
  ofstream outfile(name+".dat");
  int t = 0;

  bool precision = true;//controlla che l'integrale non vari troppo
  double integral = 0;//precisione voluta
  
  for(int i=0; i< info->NL();i+=info->spaceSkip()){
    double z = norm(myIntegrator->getPoint(i));
    integral +=z;
    outfile << i* info->spaceStep() << "\t" << t * info->timeStep() << "\t"
	    << z << endl;
  }

  do{
    t = myIntegrator->doStep();
    if(t%info->timeSkip()==0){
      double control = 0;
      double Time = t * info->timeStep();
      for(int i=0; i< info->NL();i+=info->spaceSkip()){
    double z = norm(myIntegrator->getPoint(i));
	control +=z;
	outfile << i* info->spaceStep() << "\t" << Time << "\t"
		<< z << endl;
      }
      precision = info->doNextStep(abs(integral-control));
    }
  }while(t<info->NT()&&precision);
  delete mat;
  delete[] initial;
  delete myIntegrator;
  cout << "Tempo trascorso (nella simulazione): " << t*info->timeStep() <<endl;
  outfile.close();
  info->plotSettings((name+".nfo").c_str(),t*info->timeStep());
  cout << "Ho finito con " << name <<endl;
}

int main(int argc, char** argv){
  string CI = "gauss";
  if(argc>1)
    CI  = argv[1];
  //carico il file di impostazioni, per ricompilare meno spesso
  impostazioni *info = new impostazioni((CI+".set").c_str(), "settings.set");

  ifstream filenames("namelist.txt");
  string fname;
  filenames >> fname;
  while(filenames.good()){
    size_t num = fname.find(".set");
    if(num!=string::npos)
      fname.erase(num);
    experiment(info, fname, CI);
    filenames >> fname;
 }
  filenames.close();
  cout << "Finito"<<endl;
  return 0;
}
