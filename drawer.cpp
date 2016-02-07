#ifndef __CINT__
#include <iostream>
#include <fstream>
#include <sstream>
#include <TROOT.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <vector>
#include <TF1.h>
using namespace std;
TApplication theApp("app",0,NULL);
//g++ allDataPrint.cpp `root-config --cflags --glibs`
int main(int argc, char** argv)
#endif
{
  cout<<"Carico i dati\n";
  TGraph2D *g = new TGraph2D("free.dat");
  cout<<"Analisi errore\n";
  int np = g->GetN(), NT = 0;
  double t = g->GetY()[0];
  double t2 = t;
  double integral = g->GetZ()[0];
  do{
    NT++;
    t2 = g->GetY()[NT];
    integral += g->GetZ()[NT];
  }while(t2==t);
  //cout << g->GetY()[NT-1]<<" " << integral <<endl;
  double initial = integral;
  vector<double> diffs, times, before,after;
  diffs.push_back(initial-initial);
  times.push_back(t);
  double fhalf=0,shalf=0;
  for(int i=0;i<NT;i++){
    double z =  g->GetZ()[i];
    if(i<NT/2)
      fhalf += z;
    else
      shalf += z;
  }
  before.push_back(fhalf/initial);
  after.push_back(shalf/initial);
  
  for (int j=1;j*NT<np;j++){
    int time = NT*j;
    integral = fhalf = shalf=0;
    for(int i=0;i<NT;i++){
      double z =  g->GetZ()[time+i];
      integral += z;
      if(i<NT/2)
	fhalf += z;
      else
	shalf += z;
    }
    diffs.push_back(initial-integral);
    before.push_back(fhalf/integral);
    after.push_back(shalf/integral);
    times.push_back(g->GetY()[time]);
  }
  cout<<"Disegno i grafici\n";
    TCanvas c3("c3","Grafico",640,512);
  TCanvas c1("c1","Confronto",1280,512);
  c1.Divide(2,1);
  TGraph *gb = new TGraph(times.size(),times.data(),before.data());
  TGraph *ga = new TGraph(times.size(),times.data(),after.data());
  TMultiGraph *mg = new TMultiGraph("integrali","Integrali prima e dopo la barriera");
  ga->SetLineColor(2);
  mg->Add(gb);
  mg->Add(ga);
  c1.cd(1);
  mg->Draw("apl");
    
  TGraph *gerrs = new TGraph(times.size(),times.data(),diffs.data());
  gerrs->SetTitle("Andamento degli errori");
  c1.cd(2);
  gerrs->Draw("apl");
  
  c3.cd();
  g->Draw("pcol");
  //grafo.Draw("surf1");
#ifndef __CINT__
   theApp.Run(true);
  return 0;
#endif
}
