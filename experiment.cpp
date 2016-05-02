#include <fstream>
#include <iostream>

#include "experiment.hpp"

using namespace std;

CrankSolver *myInt(impostazioni* info){
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
  delete[] initial;
  return myIntegrator;
}

CrankSolver *myInt(impostazioni* info, string name){
  cout << "Esperimento \"" << name << "\"" << endl;
  
  info->potentialsetting((name+".set").c_str());
  return myInt(info);
}

void doexperiment(CrankSolver* myIntegrator, impostazioni* info, string name, string ondaSet, string settings){
  name+="_"+ondaSet+"-"+settings;
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
  outfile << info->timeSkip()
	  << "\t" << info->timeStep()
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
	  control += norm(z);
	else{
	  control += norm(z)*2.*(1+simP2);
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
  delete myIntegrator;
  cout << "Tempo trascorso (nella simulazione): " << t*info->timeStep() <<endl;
  outfile.close();
  info->plotSettings((name+".nfo").c_str(),t*info->timeStep());
  cout << "Ho finito con " << name <<endl;
}

void experiment_sin(impostazioni* info, string name, string ondaSet, string settings, int n){
  double E, k;
  double L = info->NL()*info->spaceStep();
  k = (n*costanti::PI)/L;
  E = (k*costanti::hbar)*(k*costanti::hbar)/(2*info->getM());
  if(info->getE()!=0){
    info->setE(E);
  }else{
    cout <<"Imposto l'energia a 0 invece che a " << E << " perche` cosi` il programma non moltiplica le condizioni iniziali per exp(iomega x)\n";
    info->setE(0);
    info->setNewIstdev(k);
  }
  char num[50];
  sprintf(num,"%i",n);
  doexperiment(myInt(info),info, name, ondaSet, settings+"n"+num);
}

void experiment(impostazioni* info, string name, string ondaSet, string settings){
  doexperiment(myInt(info, name),info, name, ondaSet, settings);
}

Var experiment(impostazioni* info, double Istart, double Istop){
  CrankSolver *myIntegrator = myInt(info);
  //faccio tutti i passi e guardo solo l'ultimo
  for(int t=0;t<info->NT();)
    t = myIntegrator->doStep();
  double sstep = info->spaceStep();

  int a = Istart/(sstep);
  int b = Istop/(sstep);

  if(a>b){
    int c= a;
    a=b;
    b=c;
  }
  if((b-a)%2)
    a++;
  double integral    = norm(myIntegrator->getPoint(0))
    + norm(myIntegrator->getPoint(info->NL()-1));
  double limIntegral =norm(myIntegrator->getPoint(a))
    + norm(myIntegrator->getPoint(b-1));
  bool simP2 = true,simP2l = true;
  for(int i=1; i< info->NL()-1;i++){
    Var z = myIntegrator->getPoint(i);
    integral += norm(z)*2.*(1+simP2);
    simP2 = !simP2;
    if(i<b-1&&i>a){
      limIntegral += norm(z)*2.*(1+simP2l);
      simP2l = !simP2l;
    }
  }
  integral *= sstep/3.;
  limIntegral *= sstep/3.;
  delete myIntegrator;
  return Var(info->getE()/info->getVheight(),limIntegral/integral);//usare il complesso serve a girare intorno al fatto che devo ritornare due numeri;
}

