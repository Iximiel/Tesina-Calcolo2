#include "preparedraw.hpp"
#ifndef __CINT__
#include <TROOT.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TMultiGraph.h>

using namespace std;


TApplication theApp("app",0,NULL);
//g++ allDataPrint.cpp `root-config --cflags --glibs`
int main(int argc, char** argv)
#endif
{
  TCanvas c3("c3","Grafico",640,512);
  TCanvas c1("c1","Confronto",1280,512);
  c1.Divide(2,1);
  
  TGraph2D *g = new TGraph2D();
  TGraph *gb = new TGraph();//before
  TGraph *ga = new TGraph();//after
  TGraph *gerrs = new TGraph();
  TGraph *dummy = new TGraph();
  
  preparedraw(argv[1],g,gerrs,gb,ga,dummy);

  dummy->Clear();
  delete dummy;
  
  c3.cd();
  g->GetXaxis()->SetTitle("X");
  g->GetYaxis()->SetTitle("T");
  //g->Draw("cont1");
  g->Draw("pcol");
  //g->Draw();
  //grafo.Draw("surf1");

  cout<<"Disegno i grafici\n";
  TMultiGraph *mg = new TMultiGraph("integrali","Integrali prima e dopo la barriera");
  
  ga->SetLineColor(2);
  mg->Add(gb);
  mg->Add(ga);
  c1.cd(1);
  mg->Draw("apl");
    

  gerrs->SetTitle("Andamento degli errori");
  c1.cd(2);
  gerrs->Draw("apl");
#ifndef __CINT__
  theApp.Run(true);
  return 0;
#endif
}
