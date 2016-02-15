#ifndef __CINT__
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <complex>
#include <TROOT.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TF1.h>
using namespace std;
typedef complex<double> Var;
TApplication theApp("app",0,NULL);
//g++ allDataPrint.cpp `root-config --cflags --glibs`
int main(int argc, char** argv)
#endif
{
  int colore = 2;
  TMultiGraph *mg = new TMultiGraph("integrali","Integrali prima e dopo la barriera");
  TMultiGraph *merr = new TMultiGraph("errori","Andamento degli errori");
  cout<<"Carico i dati\n";
  ifstream filenames("namelist.txt");
  while(!filenames.eof()){
    string fname;
    filenames >> fname;//fname non deve contenere spazi e ".txt"
    
    if(fname.find(".dat")==string::npos)
      fname+=".dat";
    if(fname!=".dat"){
      cout << fname << ":" << endl;typedef complex<double> Var;
      cout<<"Analisi errore e integrali \n";
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
      //primo passo in t
      for(int i=0;i<Nl;i+=sskip){
	Var z;
	f >> z;
	integral+=norm(z);//norma L2
	if(i<Nl/2)
	  fhalf += norm(z);
	else
	  shalf += norm(z);
	Z.push_back(abs(z));
	X.push_back(i*sstep);
	T.push_back(0);
	//      g->SetPoint(g->GetN()+1,j*tstep,i*sstep,abs(z));
      }
      double initial = integral;
      vector<double> diffs, before,after,times;
      diffs.push_back(initial-initial);
      before.push_back(fhalf/initial);
      after.push_back(shalf/initial);
      times.push_back(T.back());
      for(int j=1;f.good();j++){
	integral = fhalf = shalf=0;
	for(int i=0;i<Nl&&f.good();i+=sskip){
	  Var z;
	  f >> z;
	  if(f.good()){
	    integral+=norm(z);//norma L2
	    if(i<Nl/2)
	      fhalf += norm(z);
	    else
	      shalf += norm(z);
	    Z.push_back(abs(z));
	    X.push_back(i*sstep);
	    T.push_back(j*tstep);
	  }
	}
	if(f.good()){
	  diffs.push_back(initial-integral);
	  before.push_back(fhalf/integral);
	  after.push_back(shalf/integral);
	  times.push_back(T.back());
	}
      }
  
      //TGraph2D *g = new TGraph2D(Z.size(),X.data(),T.data(),Z.data());


      TGraph *gb = new TGraph(times.size(),times.data(),before.data());
      gb->SetTitle(("Prima meta` in " +fname).c_str());    
      TGraph *ga = new TGraph(times.size(),times.data(),after.data());
      ga->SetTitle(("Seconda meta` in " +fname).c_str());
      TGraph *gerrs = new TGraph(times.size(),times.data(),diffs.data());
      gerrs->SetTitle((fname).c_str());
      gerrs->SetLineColor(colore);
      ga->SetLineColor(colore);
      ga->SetLineStyle(3);
      gb->SetLineColor(colore++);
      mg->Add(gb);
      //mg->Add(ga);
      merr->Add(gerrs);
      //g->Clear();
      //delete g;
    }
  }
  TCanvas c1("c1","Confronto",1280,512);
  // c1.Divide(2,1);
  //c1.cd(1);
  // merr->Draw("apl");
  mg->Draw("apl");
  c1.BuildLegend(0.2,0.35,0.4,0.65);
  /*
    c1.cd(2);
    merr->Draw("apl");
    c1.BuildLegend();
  */
#ifndef __CINT__
  theApp.Run(true);
  return 0;
#endif
}
