#include <iostream>
#include <fstream>

#include "experiment.hpp"
using namespace std;

int main(int argc, char** argv){
  string settings = "settings.set";
  if(argc>1){
    settings  = argv[1];
    if(settings == "--help"){
      cout << "Utilizzo degli argomenti: nomefileimpostazioni\n"
	   << "nomefileimpostazioni(.set) di base \"settings.set\"\n";
      return 0;
    }
    size_t num = settings.find(".set");
    if(num!=string::npos)
      settings.erase(num);
  }
  
  ifstream file("Tunnel.set");
  string dummy;
  file >> dummy >> dummy;
  file >> dummy >> dummy;
  double Vpos,Vpar;
  file >> Vpos >> Vpar;//posizione parametro
  file.close();
  Vpos -= Vpar/2.;
  int nE = 4;
  double En[nE] = {25,50,75,100};
  impostazioni *info = new impostazioni("initial.set", "Tunnel.set", settings.c_str());
  for(int j=0;j<nE;j++){
    info->setE(En[j]);
    char fname[50];
    sprintf(fname,"tunnel%i.tdt",(int)En[j]);
    ofstream fout(fname);
    fout <<"ev\tE"<<En[j]<<"\n";
    
    int N=40;
    double a = 0.1, b=1.75;
    double incr = (b-a)/N; //andare da a a b in N passi (N+1 perche` b lo voglio compreso)
    double V[N+1];
    //  creo la lista dei potnziali:
    for(int i=0;i<N+1;i++)
      V[i] = En[j]/(a+incr*i);
    for(int i=0;i<N+1;i++){
      cout <<"\n** Valore potenziale:"<< V[i] <<"\n";
      info->setNewVval(V[i]);
      cout << "Simulazione!" << endl;
      Var t =  experiment(info,0.,Vpos);
      cout << "Salvo i dati!" << endl;
      fout << t.real() << '\t' << t.imag() << endl;
    }
    fout.close();
  }
  cout << "Finito"<<endl;
  return 0;
}
