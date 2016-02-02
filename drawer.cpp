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
#include <vector>
#include <TF1.h>
using namespace std;
TApplication theApp("app",0,NULL);
//g++ allDataPrint.cpp `root-config --cflags --glibs`
int main(int argc, char** argv)
#endif
{
  TCanvas c3("c3","Norm",640,512);
    TCanvas c2("c2","Err",640,512);
  TGraph2D *g = new TGraph2D("todraw.txt");
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
  vector<double> diffs, times;
  diffs.push_back(initial-initial);
  times.push_back(t);
  
  for (int j=1;j*NT<np;j++){
    int time = NT*j;
    integral = 0;
    for(int i=0;i<NT;i++){
      integral += g->GetZ()[time+i];
    }
    diffs.push_back(initial-integral);
    times.push_back(g->GetY()[time]);
  }
  TGraph *gerrs = new TGraph(times.size(),times.data(),diffs.data());
  c2.cd();
  gerrs->Draw("apl");
  c3.cd();
  g->Draw("pcol");
  //grafo.Draw("surf1");
#ifndef __CINT__
   theApp.Run(true);
  return 0;
#endif
}
