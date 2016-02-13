#include <fstream>
#include <iostream>

#include "experiment.hpp"

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
  outfile << info->spaceSkip()
	  << "\t" << info->NL()
	  << "\t" <<info->spaceStep()
	  << endl;
  outfile << info->timeSkip()*info->timeStep() << endl;//il delta t tra le righe
  for(int i=0; i< info->NL();i+=info->spaceSkip()){
    Var z = myIntegrator->getPoint(i);
    integral += norm(z);
    outfile << z <<"\n";
  }
  // outfile << endl;
  do{
    t = myIntegrator->doStep();
    if(t%info->timeSkip()==0){
      double control = 0;
      for(int i=0; i< info->NL();i+=info->spaceSkip()){
	Var z = myIntegrator->getPoint(i);
	control += norm(z);
	outfile << z <<"\n";
      }
      // outfile << endl;
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
