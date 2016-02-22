#include "preparedraw.hpp"
#include <vector>
#include <complex>
#include <iostream>
#include <fstream>

using namespace std;

typedef complex<double> Var;
#ifdef _NO2D
void preparedraw(string fname, TGraph *errs, TGraph *firsthalf, TGraph *secondhalf, TGraph *maximum){
#else
void preparedraw(string fname, TGraph2D* data, TGraph *errs, TGraph *firsthalf, TGraph *secondhalf, TGraph *maximum){
  data->Clear();
#endif  
  errs->Clear();
  firsthalf->Clear();
  secondhalf->Clear();
  maximum->Clear();
  
  cout<<"Carico i dati di "<<fname<<"!\n";
  ifstream f(fname);
  int Nl, sskip, tskip;
  double sstep,atstep,tstep;
  //carico le impostazioni
  f >> sskip >> Nl >> sstep >>tskip >> atstep;
  f >> tstep;//tstep tra le righe
  cout << "Salto spaziale: "<< sskip << ", Passi spaziali:" << Nl
       << ", Passo spaziale:" << sstep <<endl;
  cout << "Salto temporale: "<< tskip << ", Passo temporale:" << atstep
       << "\nPasso temporale registrato: "<< tstep << endl;
  //carico i dati
  vector<double> Z;
  //vector<Var> Z;
  vector<double> X,T;
  double integral = 0, fhalf=0,shalf=0;
  bool simP2 = true;
  double max = -999999;
  double pos = 0;
  //primo passo in t

  for(int i=0;i<Nl;i++){
    Var z;
    f >> z;
    //integrale di simpson
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
    Z.push_back(abs(z));
    X.push_back(i*sskip*sstep);
    T.push_back(0);
    
    if(Z.back()>max){
      max = Z.back();
      pos = X.back();
    }
  }

  integral *= sstep*sskip/3.;
  fhalf *= sstep*sskip/3.;
  shalf *= sstep*sskip/3.;
  integral = sqrt(integral);
  fhalf = sqrt(fhalf);
  shalf = sqrt(shalf);
  double initial = integral;
  vector<double> diffs, before,after,times;
  vector<double> maxs;
  maxs.push_back(pos);
  diffs.push_back(initial-initial);
  before.push_back(fhalf/initial);
  after.push_back(shalf/initial);
  times.push_back(T.back());
  for(int j=1;f.good();j++){
    integral = fhalf = shalf=0;
    simP2 = true;
    max = -999999;
    pos = 0;
    for(int i=0;i<Nl&&f.good();i++){
      Var z;
      f >> z;
      if(f.good()){
        //integrale di simpson
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
	Z.push_back(abs(z));
	X.push_back(i*sskip*sstep);
	T.push_back(j*tstep);
	
	if(Z.back()>max){
	  max = Z.back();
	  pos = X.back();
	}
      }
    }
    integral *= sstep*sskip/3.;
    fhalf *= sstep*sskip/3.;
    shalf *= sstep*sskip/3.;
    integral = sqrt(integral);
    fhalf = sqrt(fhalf);
    shalf = sqrt(shalf);
    
    if(f.good()){
      maxs.push_back(pos);      
      diffs.push_back(initial-integral);
      before.push_back(fhalf/integral);
      after.push_back(shalf/integral);
      times.push_back(T.back());
    } 
  }
  //estraggo dal nome le info sulla funzione:
  size_t pospot = -1;
  pospot = fname.find("_");
  string pot = fname.substr(0,pospot);
  size_t posCI  = -1;
  posCI = fname.find("-");
  string CI = fname.substr(pospot+1,posCI-pospot-1);
  /*
    size_t posSet = -1;
    posSet = fname.find(".dat");
    string Set = fname.substr(posCI+1,posSet-posCI-1);
  */
  /*
  string title = pot+", "+CI+", dT="+to_string(atstep)+", dS="+to_string(sstep);
  string title2 = "dT="+to_string(atstep)+", dS="+to_string(sstep)+
    ", in " + pot+", "+CI;
*/
  char title[50], title2[50];
  sprintf(title,"%s, %s, dT=%g, dS=%g",pot.c_str(),CI.c_str(),atstep,sstep);
  sprintf(title2,"dT=%g, dS=%g in %s %s",atstep,sstep,pot.c_str(),CI.c_str());
  //to_string();
#ifndef _NO2D
  *data       = *(new TGraph2D(Z.size(),X.data(),T.data(),Z.data()));
#endif
  *firsthalf  = *(new TGraph(times.size(), times.data(), before.data()));
  *secondhalf = *(new TGraph(times.size(), times.data(), after.data()));
  *errs       = *(new TGraph(times.size(), times.data(), diffs.data()));
  *maximum    = *(new TGraph(times.size(), times.data(), maxs.data()));
  /*  firsthalf  -> SetTitle((title).c_str());
  secondhalf -> SetTitle((title).c_str());
  errs       -> SetTitle((title2).c_str());
  maximum    -> SetTitle((title2).c_str());*/
  firsthalf  -> SetTitle(title);
  secondhalf -> SetTitle(title);
  errs       -> SetTitle(title2);
  maximum    -> SetTitle(title2);
}
