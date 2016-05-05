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
#include <TF1.h>
using namespace std;

int main(int argc, char** argv)
#endif
{
  ifstream filenames("namelist.txt");
  ofstream velfile("datavel.txt");
  velfile << "nomefile\tvelocita\tpunto iniziale\n";
  TF1  *line = new TF1 ("linea", "[0]+[1]*x", 0., 20.);
  line->SetParNames("x_0","v");
  while(!filenames.eof()){
    string fname;
    filenames >> fname;//fname non deve contenere spazi e ".txt"
    
    if(fname.find(".dat")==string::npos)
      fname+=".dat";
    if(fname!=".dat"){
      cout <<"*\n"<< fname << ":" << endl;
      int sets=0;
      sets |= preparedraw::doMax;
      
      preparedraw myData(fname,sets);
      myData.maximum()->Fit(line,"N");
      velfile << fname << "\t" <<line->GetParameter(1)<< "\t"<< line->GetParameter(0)<<endl;
    }
  }
  velfile.close();
}
    
