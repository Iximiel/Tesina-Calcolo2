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

      TGraph *gb, *ga, *gerrs,*maxs;
      int sets=0;
      if(gv)
	sets |= preparedraw::doMax;
      if(fh);
	sets |= preparedraw::doFh;      
      if(sh)
	sets |= preparedraw::doSh;
      if(err)
	sets |= preparedraw::doErr;
      
      preparedraw myData(fname,sets);
      
      //aggiungo i grafici ai multigraph e cancello oi grafici che pesano sulla memoria
      if(gv){
	maxs = myData.maximum();
	maxs->SetLineColor(colore);	
	mm->Add(maxs);
      }      
      if(fh){
	gb = myData.firsthalf();
	gb->SetLineColor(colore);
	mg->Add(gb);
      }
      
      if(sh){
	ga = myData.secondhalf();
	ga->SetLineColor(colore);
	if(fh)
	  ga->SetLineStyle(3);
	mg->Add(ga);
      }
      
      if(err){
	gerrs = myData.errs();
	gerrs->SetLineColor(colore);
	merr->Add(gerrs);
      }
     
      colore++;
    }
  }

  TCanvas*E   = nullptr;
  TCanvas*PM  = nullptr;
  TCanvas*Int = nullptr;
  
  if(fh||sh){
    Int = new TCanvas("Int","Coefficienti",800,600);
    Int->cd();
    Int->SetGridy(1);
    mg->Draw("al");
    Int->BuildLegend(0.2,0.35,0.4,0.65);
  }
  if(err){
    E = new TCanvas("E","Errore",800,600);
    E->cd();
    merr->Draw("al");
    E->BuildLegend(0.5,0.875,0.125,0.675);
  }
  if(gv){
    PM = new TCanvas("PM","Posizione Massimi",800,600);
    PM->cd();
    mm->Draw("al");
    PM->BuildLegend(0.5,0.875,0.125,0.675);
  }
#ifndef __CINT__
  theApp.Run(true);
  return 0;
#endif
}
