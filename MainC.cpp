#include <iostream>

#include "experiment.hpp"
using namespace std;

int main(int argc, char** argv){
  string filename = "free";
  string ondaSet = "gauss";
  string settings = "settings";
  if(argc>1){
    filename  = argv[1];
    if(filename == "--help"){
      cout << "Utilizzo degli argomenti: nomepotenziale nomeCondizioniIniziali nomefileimpostazioni\n"
	   << "nomepotenziale(.set) il file che contiene il potenziale, default \"free.set\"\n"
	   << "nomeCondizioniIniziali(.set) il file che condiete le informazioni sulle condizioni iniziali, default \"gauss.set\"\n"
	   << "nomefileimpostazioni(.set) di base \"settings.set\"\n";
      return 0;
    }
    size_t num = filename.find(".set");
    if(num!=string::npos)
      filename.erase(num);
  }if(argc>2){
    ondaSet  = argv[2];
    size_t num = ondaSet.find(".set");
    if(num!=string::npos)
      ondaSet.erase(num);
  }if(argc>3){
    settings  = argv[3];
    size_t num = settings.find(".set");
    if(num!=string::npos)
      settings.erase(num);
  }
  cout << "********************************************"<<endl;
  cout << "carico le impostazioni da " << filename << ".set, " << ondaSet << ".set e "<<settings<<".set" <<  endl;
  //carico il file di impostazioni, per ricompilare meno spesso
  impostazioni info((ondaSet+".set").c_str(), (settings+".set").c_str());

  experiment(&info, filename,ondaSet,settings);
  
  cout << "Finito"<<endl;
  return 0;
}
