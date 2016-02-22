#define _NO2D
#include "preparedraw.hpp"
#ifndef __CINT__
#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
//#include <TF1.h>
using namespace std;

//g++ allDataPrint.cpp `root-config --cflags --glibs`
int main(int argc, char** argv)
#endif
{
  string opt = "-e";
  if(argc>1){
    if(argv[1][0]=='-')
      opt = argv[1];
    if(opt=="--help"){
      cout << "Di base mostra l'errore dei file .dat elencati in \"namelist.txt\""<<endl;
      cout << "se in argomente passi un \"-\" seguito da:"<<endl;
      cout << "\"E\" o \"e\" per mostrare l'errore"<< endl;
      cout << "\"V\" o \"v\" per mostrare la posizione del massimo"<< endl;
      cout << "\"F\" o \"f\" per mostrare l'integrale fino a meta` dominio"<< endl;
      cout << "\"S\" o \"s\" per mostrare l'integrale dopo meta` dominio"<< endl;
      cout << "Puoi concatenare piu` copmandi es \"-eF\""<<endl;
      return 0;
    }
  }
  //parser
  bool err,fh,sh,gv;
  err=fh=sh=gv=false;
  if(opt.find('e')!=string::npos||opt.find('E')!=string::npos)
    err = true;
  if(opt.find('f')!=string::npos||opt.find('F')!=string::npos)
    fh = true;
  if(opt.find('s')!=string::npos||opt.find('S')!=string::npos)
    sh = true;
  if(opt.find('v')!=string::npos||opt.find('V')!=string::npos)
    gv = true;
#ifndef __CINT__
  TApplication theApp("app",0,NULL);
#endif
  int colore = 2;
  TMultiGraph *mg = new TMultiGraph("integrali","Integrali");
  TMultiGraph *merr = new TMultiGraph("errori","Andamento degli errori");
  TMultiGraph *mm = new TMultiGraph("massimi","Posizione del massimo nel tempo"); 
  cout<<"Carico i dati\n";
  ifstream filenames("namelist.txt");
  while(!filenames.eof()){
    string fname;
    filenames >> fname;//fname non deve contenere spazi e ".txt"
    
    if(fname.find(".dat")==string::npos)
      fname+=".dat";
    if(fname!=".dat"){
      cout <<"*\n"<< fname << ":" << endl;

      TGraph *gb = new TGraph();//before
      TGraph *ga = new TGraph();//after
      TGraph *gerrs = new TGraph();
      TGraph *maxs = new TGraph();
	    
      preparedraw(fname,gerrs,gb,ga,maxs);
      
      //aggiungo i grafici ai multigraph e cancello oi grafici che pesano sulla memoria
      if(gv){
	maxs->SetLineColor(colore);	
	mm->Add(maxs);
      }else
	delete maxs;
      
      if(fh){
	gb->SetLineColor(colore);
	mg->Add(gb);
      }else
	delete gb;
      
      if(sh){
	ga->SetLineColor(colore);
	ga->SetLineStyle(3);
	mg->Add(ga);
      }else
	delete ga;
      
      if(err){
	gerrs->SetLineColor(colore);
	merr->Add(gerrs);
      }else
	delete gerrs;
     
      colore++;
    }
  }

  TCanvas*E   = nullptr;
  TCanvas*PM  = nullptr;
  TCanvas*Int = nullptr;
  
  if(fh||sh){
    Int = new TCanvas("Int","Integrale",800,600);
    mg->Draw("apl");
    Int->BuildLegend(0.2,0.35,0.4,0.65);
  }
  if(err){
    E = new TCanvas("E","Errore",800,600);
    E->cd();
    merr->Draw("apl");
    E->BuildLegend(0.5,0.875,0.125,0.675);
  }
  if(gv){
    PM = new TCanvas("PM","Posizione Massimi",800,600);
    PM->cd();
    mm->Draw("apl");
    PM->BuildLegend(0.5,0.875,0.125,0.675);
  }
#ifndef __CINT__
  theApp.Run(true);
  return 0;
#endif
}
