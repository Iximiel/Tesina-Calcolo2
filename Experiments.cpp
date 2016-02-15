#include <iostream>
#include <fstream>

#include "experiment.hpp"

using namespace std;


int main(int argc, char** argv){
  string CI = "gauss";
  string settings = "settings";
  if(argc>1){
    CI  = argv[1];
    size_t num = CI.find(".set");
    if(num!=string::npos)
      CI.erase(num);
  }
  //carico il file di impostazioni, per ricompilare meno spesso
  impostazioni *info = new impostazioni((CI+".set").c_str(), (settings+".set").c_str());

  ifstream filenames("namelist.txt");
  string fname;
  filenames >> fname;
  while(filenames.good()){
    size_t num = fname.find(".set");
    if(num!=string::npos)
      fname.erase(num);
    experiment(info, fname, CI, settings);
    filenames >> fname;
  }
  filenames.close();
  cout << "Finito"<<endl;
  return 0;
}
