#include <fstream>
#include <iostream>

#include "experiment.hpp"

using namespace std;

void experiment(impostazioni* info, string name, string ondaSet, string settings){
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
  name+="_"+ondaSet+"_"+settings;
  //file in una cartella superiore
  name = "./results/"+name;
  cout << "Inizio i calcoli, salvo su "<< name << ".dat" << endl;
  ofstream outfile(name+".dat");
  int t = 0;

  bool precision = true, simP2 = true;
  double integral = 0;
  
  outfile << info->spaceSkip()
	  << "\t" << info->NL()
	  << "\t" <<info->spaceStep()
	  << endl;
  outfile << info->timeSkip()*info->timeStep() << endl;//il delta t tra le righe
  for(int i=0; i< info->NL();i+=info->spaceSkip()){
    Var z = myIntegrator->getPoint(i);
    //integrale di simpson
    if(i == 0||i== info->NL()-1)
      integral += norm(z);
    else{
      integral += norm(z)*2.*(1+simP2);
      simP2 = !simP2;
    }
    outfile << z <<"\n";
    //outfile << z.real() <<"\t"<<z.imag()<<"\n";
  }
  integral*=info->spaceStep()*info->spaceSkip()/3.;
  integral = sqrt(integral);
  do{
    t = myIntegrator->doStep();
    if(t%info->timeSkip()==0){
      simP2 = true;
      double control = 0;
      for(int i=0; i< info->NL();i+=info->spaceSkip()){
	Var z = myIntegrator->getPoint(i);
	if(i == 0||i== info->NL()-1)
	  integral += norm(z);
	else{
	  integral += norm(z)*2.*(1+simP2);
	  simP2 = !simP2;
	}
	outfile << z <<"\n";
	//outfile << z.real() <<"\t"<<z.imag()<<"\n";
      }
      control*=info->spaceStep()*info->spaceSkip()/3.;
      control = sqrt(control);
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
