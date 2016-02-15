#include <vector>

using namespace std;

void preparedraw(string fname, TGraph2D* data, TGraph *errs, TGraph *firsthalf, TGraph *secondhalf){
  if(data!=nullptr){
    data->Clear();
    delete data;
  }
  if(errs!=nullptr){
    errs->Clear();
    delete secondhalf;
  }
  if(firsthalf!=nullptr){
    firsthalf->Clear();
    delete secondhalf;
  }
  if(secondhalf!=nullptr){
    secondhalf->Clear();
    delete secondhalf;
  }
  cout<<"Carico i dati di "<<fname<<"!\n";
  ifstream f(fname);
  int Nl, sskip;
  double sstep,tstep;
  //carico le impostazioni
  f >> sskip >> Nl >> sstep >> tstep;
  cout << "Salto spaziale: "<< sskip << ", Passi spaziali:" << Nl
       << ", Passo spaziale:" << sstep << "\nPasso temporale:" << tstep << endl;
  //carico i dati
  vector<double> Z;
  //vector<Var> Z;
  vector<double> X,T;
  double integral = 0, fhalf=0,shalf=0;
  bool simP2 = true;
  //primo passo in t
  for(int i=0;i<Nl;i+=sskip){
    Var z;
    f >> z;
    //integrale di simpson
    if(i == 0||i== info->NL()-1){
      integral += norm(z);
      if(i<Nl/2)
	fhalf += norm(z);
      else
	shalf += norm(z);
    }else{
      integral += norm(z)*2.*(1+simP2);    
      if(i<Nl/2)
	fhalf += norm(z)*2.*(1+simP2);    
      else
	shalf += norm(z)*2.*(1+simP2);
      simP2 = !simP2;
    }
    Z.push_back(abs(z));
    X.push_back(i*sstep);
    T.push_back(0);
    //      g->SetPoint(g->GetN()+1,j*tstep,i*sstep,abs(z));
  }
  integral *= sstep*sskip/3.;
  fhalf *= sstep*sskip/3.;
  shalf *= sstep*sskip/3.;
  integral = sqrt(integral);
  fhalf = sqrt(fhalf);
  shalf = sqrt(shalf);
  double initial = integral;
  vector<double> diffs, before,after,times;
  diffs.push_back(initial-initial);
  before.push_back(fhalf/initial);
  after.push_back(shalf/initial);
  times.push_back(T.back());
  for(int j=1;f.good();j++){
    integral = fhalf = shalf=0;
    simP2 = true; 
    for(int i=0;i<Nl&&f.good();i+=sskip){
      Var z;
      f >> z;
      if(f.good()){
        //integrale di simpson
	if(i == 0||i== info->NL()-1){
	  integral += norm(z);
	  if(i<Nl/2)
	    fhalf += norm(z);
	  else
	    shalf += norm(z);
	}else{
	  integral += norm(z)*2.*(1+simP2);    
	  if(i<Nl/2)
	    fhalf += norm(z)*2.*(1+simP2);    
	  else
	    shalf += norm(z)*2.*(1+simP2);
	  simP2 = !simP2;
	}
	Z.push_back(abs(z));
	X.push_back(i*sstep);
	T.push_back(j*tstep);
      }
    }
    integral *= sstep*sskip/3.;
    fhalf *= sstep*sskip/3.;
    shalf *= sstep*sskip/3.;
    integral = sqrt(integral);
    fhalf = sqrt(fhalf);
    shalf = sqrt(shalf);
    
    if(f.good()){
      diffs.push_back(initial-integral);
      before.push_back(fhalf/integral);
      after.push_back(shalf/integral);
      times.push_back(T.back());
    }
  }
  
  data = new TGraph2D(Z.size(),X.data(),T.data(),Z.data());
  firsthalf = new TGraph(times.size(),times.data(),before.data());
  secondhalf = new TGraph(times.size(),times.data(),after.data());
  errs = new TGraph(times.size(),times.data(),diffs.data());
}
