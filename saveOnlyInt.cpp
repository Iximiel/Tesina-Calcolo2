#include <iostream>
#include <fstream>

#include "experiment.hpp"
using namespace std;

int main(int argc, char** argv){
  cout<< "\033[2J";//pulisce lo schermo
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
  
  ifstream file("Potenziale.set");
  string dummy;
  file >> dummy >> dummy;
  file >> dummy >> dummy;
  double Vpos,Vpar;
  file >> Vpos >> Vpar;//posizione parametro
  file.close();
  Vpos -= Vpar/2.;
  impostazioni *info = new impostazioni("initial.set", "Potenziale.set", settings.c_str());
  char disc;
  
  //scelgo come variare le condizioni iniziali
#ifdef SIGMA
  disc = 's';
  /*  int nP = 8;
  double Par[nP] = {0.5, 1, 2, 3, 4, 5, 6, 7};*/
  int nP = 4;
  double Par[nP] = {0.5, 1, 2, 4};
  for(int j=0;j<nP;j++){
    info->setNewIstdev(Par[j]);
#else
    disc = 'E';
    int nP = 4;
    double Par[nP] = {10, 15, 20, 25};
    for(int j=0;j<nP;j++){
      info->setE(Par[j]);
#endif
      char fname[50];
      sprintf(fname,"Esperimento_%i.tdt",j);
      ofstream fout(fname);
      fout <<"ev\t"<<disc<<Par[j]<<"\n";

      //imposto come variare il potenziale
      int N;
#ifdef REGULAR
      //incrementi regolari
      N=40;
      double a = 0.25, b=1.75;
      double incr = (b-a)/N; //andare da a a b in N passi (N+1 perche` b lo voglio compreso)
#else
      N=11;
      //punti decisi
      double div[N+1] = {1./3.,0.5,0.8,9./10.,1,11./10.,4./3.,5./3.,2,3,4,10};
#endif
      for(int i=0;i<N+1;i++){
	double V;
	cout <<"\n** Rapporto E/V:\t\t";
#ifdef REGULAR
	V = info->getE()/(a+incr*i);
	cout << (a+incr*i);
#else
	V = info->getE()/(div[i]);
	cout <<(div[i]);
#endif
	info->setNewVval(V);
	cout <<"\n** Valore potenziale:\t"<< info->getVheight();
	cout <<"\n** Valore Energia:\t"<< info->getE() <<"\n";
	cout << "Simulazione!" << endl;
	Var t =  experiment(info,0.,Vpos);
	cout << "Salvo i dati!" << endl;
	//real: rapporto E/V, imag: rapporto integrali
	fout << t.real() << '\t' << t.imag() << endl;
      }
      fout.close();
      cout << "\n*******************\n\n";      
    }
    cout << "Finito"<<endl;
    return 0;
  }
