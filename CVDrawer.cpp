#include "impostazioni.hpp"
#ifdef __CINT_
#include "impostazioni.cpp"
#else
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
  int colore = 2;
  TMultiGraph *mg = new TMultiGraph("potenziale","Potenziali");
  cout<<"Carico i dati\n";
  ifstream filenames("infonamelist.txt");
  string filename = "settings.set";
  if(argc>1)
    filename  = argv[1];
  //carico il file di impostazioni, per ricompilare meno spesso
  while(!filenames.eof()){
    string fname;
    filenames >> fname;//fname non deve contenere spazi e ".txt"
    if(fname.find(".set")==string::npos)
      fname+=".set";
    if(fname!=".set"){
      impostazioni info("gauss.set", fname.c_str(),filename.c_str());
      cout << fname << ":" << endl;
      int ns = info.NL(), skip = info.spaceSkip();
      double step = info.spaceStep();
      TGraph *gV = new TGraph();
      int j=0;
      for(int i=0;i<ns;i+=skip){
	double x =  i*step;
	gV->SetPoint(j++,x,info.potenziale(i));
      }

      gV->SetTitle(("Potenziale per " +fname).c_str());    
      gV->SetLineColor(colore++);
      mg->Add(gV);
    }
  }
  TCanvas c1("c1","Confronto Potenziali",600,450);
  // c1.Divide(2,1);
  //c1.cd(1);
  // merr->Draw("apl");
    mg->Draw("apl");
  c1.BuildLegend();
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
