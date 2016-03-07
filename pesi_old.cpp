#define _NO2D
#include "preparedraw.hpp"
#ifndef __CINT__
#include <iostream>
#include <fstream>
using namespace std;

//g++ allDataPrint.cpp `root-config --cflags --glibs`
int main(int argc, char** argv)
#endif
{
  bool fh = true;
  cout<<"Carico i dati\n";
  ifstream filenames("namelist.txt");
  ofstream of("pesi.dat");  //costruito per passi uguali e tempo uguale!
  while(!filenames.eof()){
    string fname;
    filenames >> fname;//fname non deve contenere spazi e ".txt"
    
    if(fname.find(".dat")==string::npos)
      fname+=".dat";
    if(fname!=".dat"){
      cout <<"*\n"<< fname << ":" << endl;
      of << '\t' << fname;
      
      TGraph *gb = new TGraph();//before
      TGraph *ga = new TGraph();//after
	    
      preparedraw(fname,gb,ga);
      
      if(fh){
	Int N = gb->GetN();
	gb->GetX();
	gb->GetY();
      }else{
	Int N = ga->GetN();
	ga->GetX();
	ga->GetY();
      }
       delete ga;
       delete gb;     
    }
  }
  of.close();
 #ifndef __CINT__
  return 0;
#endif
}
