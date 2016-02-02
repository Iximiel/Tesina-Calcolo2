#ifndef __CINT__
#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph2D.h>
#include <TF1.h>
using namespace std;
TApplication theApp("app",0,NULL);
//g++ allDataPrint.cpp `root-config --cflags --glibs`
int main()
#endif
{
  /*  TCanvas c("c","Real",640,512);
  TGraph2D *grafo = new TGraph2D("out.txt");
  grafo->Draw("pcol");
  TCanvas c2("c2","Imaginary",640,512);
  TGraph2D *Cgrafo = new TGraph2D("iout.txt");
  Cgrafo->Draw("pcol");*/
  TCanvas c3("c3","Norm",640,512);
  TGraph2D *Ngrafo = new TGraph2D("out.txt");
  Ngrafo->Draw("pcol");
  //grafo.Draw("surf1");
#ifndef __CINT__
  theApp.Run(true);
  return 0;
#endif
}
