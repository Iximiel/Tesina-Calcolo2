#include "preparedraw.hpp"
#include <iostream>
#include <fstream>

using namespace std;

preparedraw::preparedraw(string fname, int whatToDo){
  cout<<"Carico i dati di "<<fname<<"!\n";
  settings = whatToDo;
  ifstream f(fname);
  //carico le impostazioni
  f >> sskip >> Nl >> sstep >>tskip >> atstep;
  f >> tstep;//tstep tra le righe
  cout << "Salto spaziale: "<< sskip << ", Passi spaziali:" << Nl
       << ", Passo spaziale:" << sstep <<endl;
  cout << "Salto temporale: "<< tskip << ", Passo temporale:" << atstep
       << "\nPasso temporale registrato: "<< tstep << endl;
  size_t pospot = -1;
  pospot = fname.find("_");
  pot = fname.substr(0,pospot);
  size_t posCI  = -1;
  posCI = fname.find("-");
  CI = fname.substr(pospot+1,posCI-pospot-1);

  //carico i dati  
  double integral = 0, fhalf=0, shalf=0;
  bool simP2 = true;
  double max = -999999;
  double pos = 0;

  for(int j=0;f.good();j++){
    integral = fhalf = shalf=0;
    simP2 = true;
    max = -999999;
    pos = 0;
    for(int i=0;i<Nl&&f.good();i++){
      Var z;
      f >> z;
      if(f.good()){
        //integrale di simpson
	if(settings&doErr){
	  if(i == 0||i== Nl-1){
	    integral += norm(z);
	    if(i<Nl/2)
	      fhalf += norm(z);
	    else
	      shalf += norm(z);
	  }else{
	    integral += norm(z)*2.*(1+simP2);    
	    if(i<Nl/2-1)
	      fhalf += norm(z)*2.*(1+simP2);
	    else if(i==Nl/2-1)
	      fhalf += norm(z);
	    else if(i==Nl/2)
	      shalf += norm(z);
	    else
	      shalf += norm(z)*2.*(1+simP2);
	    simP2 = !simP2;
	  }
	}
	Z.push_back(z);
	if(settings&doMax){
	  double test = abs(Z.back());
	  if(test>max){
	    max = test;
	    pos = i*sskip*sstep;
	  }
	}
      }
    }
    if(f.good()){
      if(settings&doMax)
	maxs.push_back(pos);
      if(settings&doErr){      
	integral *= sstep*sskip/3.;
	if(settings&doFh){            
	  fhalf *= sstep*sskip/3.;
	  //fhalf = sqrt(fhalf);
	  before.push_back(fhalf/integral);
	}
	if(settings&doSh){      
	  shalf *= sstep*sskip/3.;
	  //shalf = sqrt(shalf);
	  after.push_back(shalf/integral);
	}
	integral = sqrt(integral);
	integrals.push_back(integral);
      }
      times.push_back(j*tstep);
    } 
  }
  Nt = times.size();
}

preparedraw::~preparedraw(){
  Z.clear();
  integrals.clear();
  before.clear();
  after.clear();
  times.clear();
  maxs.clear();
}

TGraph2D* preparedraw::data(){
  TGraph2D *toreturn = new TGraph2D(Z.size());
  for(int j=0;j<Nt;j++){
    for(int i=0;i<Nl;i++)
      toreturn->SetPoint(i+j*Nl,sstep*sskip*i,times.at(j),abs(Z.at(i+j*Nl)));
  }
  return toreturn;
}

TGraph* preparedraw::errs(){
  controlErr();
  TGraph* toreturn = new TGraph(Nt);
  double initial = integrals.at(0);
  for(int i=0;i<Nt;i++)
    toreturn->SetPoint(i,times.at(i),initial-integrals.at(i));
  
  char title[50];
  sprintf(title,"dT=%g, dS=%g in %s %s",atstep,sstep,pot.c_str(),CI.c_str());
  toreturn -> SetTitle(title);
  return toreturn;
}

TGraph* preparedraw::firsthalf(){
  controlFh();
  TGraph* toreturn = new TGraph(Nt, times.data(), before.data());

  char title[50];
  sprintf(title,"Prima meta` %s",pot.c_str());
  toreturn -> SetTitle(title);
  return toreturn;
}

TGraph* preparedraw::secondhalf(){
  controlSh();
  TGraph* toreturn = new TGraph(Nt, times.data(), after.data());

  char title[50];
  sprintf(title,"Seconda meta` %s",pot.c_str());
  toreturn -> SetTitle(title);
  return toreturn;
}

TGraph* preparedraw::maximum(){
  controlMax();
  TGraph* toreturn = new TGraph(Nt, times.data(), maxs.data());

  char title[50];
  sprintf(title,"dT=%g, dS=%g in %s %s",atstep,sstep,pot.c_str(),CI.c_str());
  toreturn -> SetTitle(title);
  return toreturn;
}

int preparedraw::NT(){return Nt;}

double preparedraw::errs(int i){
  controlErr();
  return integrals.at(0) - integrals.at(i);
}

double preparedraw::integral(int i){
  controlErr();
  return integrals.at(i);
}

double preparedraw::firsthalf(int i){
  controlFh();
  return before.at(i);
}

double preparedraw::secondhalf(int i){
  controlSh();
  return after.at(i);
}

double preparedraw::maximum(int i){
  controlMax();
  return maxs.at(i);
}

void preparedraw::controlErr(){
  if(!(doErr&settings)){
    settings |= doErr;
    cout << "La prossima vola imposta preparedraw::doErr nel costruttore"<<endl;
    double integral = 0;
    bool simP2 = true;
    
    for(int j=0;j<Nt;j++){
      integral = norm(Z.at(Nl*j)) + norm(Z.at(Nl-1+Nl*j));
      simP2 = true;
      for(int i=0;i<Nl-1;i++){
	//integrale di simpson
	integral += norm(Z.at(i+Nl*j))*2.*(1+simP2);    
	simP2 = !simP2;
      }
      integral *= sstep*sskip/3.;
      integral = sqrt(integral);
      integrals.push_back(integral);
    }
  }
}

void preparedraw::controlFh(){
  controlErr();
  if(!(doFh&settings)){
    settings |= doFh;
    cout << "La prossima vola imposta preparedraw::doFh nel costruttore"<<endl;
    double integral = 0;
    bool simP2 = true;
    
    for(int j=0;j<Nt;j++){
      simP2 = true;
      //integrale di simpson
      integral = norm(Z.at(Nl*j))+norm(Z.at(Nl/2-1+Nl*j));
      for(int i=1;i<Nl/2-1;i++){
	integral += norm(Z.at(i+Nl*j))*2.*(1+simP2);    
	simP2 = !simP2;
      }
      integral *= sstep*sskip/3.;
      //integral = sqrt(integral);
      double div = integrals.at(j);
      div*=div;
      before.push_back(integral/div);
    }
  }
}


void preparedraw::controlSh(){
  controlErr();
  if(!(doSh&settings)){
    settings |= doSh;
    cout << "La prossima vola imposta preparedraw::doSh nel costruttore"<<endl;
    double integral = 0;
    bool simP2 = true;

    for(int j=0;j<Nt;j++){
      simP2 = true;
      //integrale di simpson
      integral = norm(Z.at(Nl/2+Nl*j))+norm(Z.at(Nl-1+Nl*j));
      for(int i=Nl/2;i<Nl;i++){
	integral += norm(Z.at(i+Nl*j))*2.*(1+simP2);    
	simP2 = !simP2;
      }
      integral *= sstep*sskip/3.;
      //integral = sqrt(integral);
      double div = integrals.at(j);
      div*=div;
      before.push_back(integral/div);
    }
  }
}

void preparedraw::controlMax(){
  if(!(doMax&settings)){
    settings |= doMax;
    cout << "La prossima vola imposta preparedraw::doMax nel costruttore"<<endl;
    double max = -999999;
    double pos = 0;

    for(int j=0;j<Nt;j++){
      max = -999999;
      pos = 0;
      for(int i=0;i<Nl;i++){
	double test = abs(Z.at(i+Nl*j));
	if(test > max){
	  max = test;
	  pos = i*sskip*sstep;
	}
      }
    }
    maxs.push_back(pos);
  } 
}

double preparedraw::limitedIntegral(int j, double start, double stop){
  //integro da 'a' a 'b'
  int a = start/(sstep*sskip);
  int b = stop/(sstep*sskip);
  if(a<0)
    a=0;
  if(b>Nl)
    b = Nl-1;
  //cout << a<< " "<< b;
  double integral = norm(Z.at(Nl*j+a)) + norm(Z.at(b-1+Nl*j));
  bool simP2 = true;
  for(int i=0;i<b-1;i++){
    //integrale di simpson
    integral += norm(Z.at(i+Nl*j))*2.*(1+simP2);    
    simP2 = !simP2;
  }
  integral *= sstep*sskip/3.;
  integral = sqrt(integral);
  return integral; 
}
