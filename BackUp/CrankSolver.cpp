#include "CrankSolver.hpp"
#include <iostream>
#include <fstream>

#ifdef DEBUG
#include <cmath>//per gli abs
void wait(){
  cout<< "Premi enter per continuare."<<endl;
  cin.get();
}
#endif //DEBUG

using namespace std;

CranckSolver::CranckSolver(const tridiag &mat, int Ns, int Nt, double CCi, double CCe)
  :CS_mat(mat){
  //CS_mat = mat;   
  CS_ns = Ns;
  CS_nt = Nt;
  CS_cci = CCi;
  CS_cce =CCe;
  CS_data = new Var [CS_ns * CS_nt];
  CS_step = 0;
  CS_mat.create_h();
  doProcessCC = false;
}

CranckSolver::~CranckSolver(){
  //delete h;
  delete CS_data;
}

void CranckSolver::SetInitialState(Var* initialVector){
  for(int i=0;i<CS_ns;i++)
    CS_data[i] = initialVector[i];
  CS_step =1;
#ifdef DEBUG
  cout << "Acquisite condizioni iniziali"<< endl;
#endif //DEBUG
}

bool CranckSolver::doStep(){
  if(CS_step ==0){
    cout << "Non ho acquisito le condizioni iniziali"<<endl;
    return false;
  }else if(CS_step >= CS_nt){
    cout << "Ho fatto tutti i passi previsti"<<endl;
    return false;
  }else{
    if(doProcessCC)
      processCC();
    Stepper();
    CS_step++;
    return true;
  }
}

Var CranckSolver::getPoint(int t, int x){
  return CS_data[t*CS_ns+x];
}

void CranckSolver::Stepper(){
  int t = CS_step*CS_ns; //dummy per comodita`
  int tm1 = (CS_step-1)*CS_ns; //dummy per comodita`
  CS_data[t+0] = CS_cci;
  CS_data[t+CS_ns-1] = CS_cce;
  Var *p = new Var [CS_ns-1];
  p[0] = 0;//0 e` l'indice delle condizioni al contorno, 0 serve a non aggiungere eccezioni all'algoritmo
  //la spiegazione e` in create_h() di Tridiag.cpp
  //preparo del vettore delle p[]
  for(int i=1;i<CS_ns-1;i++){
    //calcolo il valore di b[i]
    Var bi = CS_mat.bi(i,CS_data[tm1+i-1],
			  CS_data[tm1+i],CS_data[tm1+i+1]);
    //aggiungo le CC, non penso che questi if rallentino eccessivamente il calcolo
    if(i==1)
      bi-=CS_mat.GetA(i)*CS_cci;// so che h[0] = 0, p[0] = 0
    else if(i==CS_ns-2)
      bi-=CS_mat.GetC(i)*CS_cce;

    p[i] = CS_mat.pi(i,p[i-1],bi);

#ifdef DEBUG
    if(abs(CS_ns/2.-i)<=5){
      cout << i <<": b[i] = "<< bi <<" p[i]= "<<p[i];//<<endl;
      cout << "\t" <<  (CS_mat.d[i]-CS_mat.a[i]*h[i-1])<< " " << h[i-1]<<endl;
    }
#endif //DEBUG
  }
  
  //ora procedo finalmente con l'assegnare i risultati
  for(int i=CS_ns-2;i>0;i--){
    CS_data[t+i] = p[i] - CS_mat.H(i) * CS_data[t+i+1];
    //da pi = xi + hi x(i+1)
#ifdef DEBUG
    if(abs(CS_ns/2.-i)<=5)
      cout << i <<": p[i]= "<<p[i] <<",x[i](t-1)="<<CS_data[tm1+i]
	   <<"=>x[i](t)="<<CS_data[t+i]<<endl;
#endif //DEBUG
  }
#ifdef DEBUG
  wait();
#endif //DEBUG
}

bool CranckSolver::prepareTGraph2D(string filename, double timestep, double spacestep, int timespan, int spacespan){
  if(CS_step <= 1){
    cout << "Non ho svolto alcun calcolo, non preparo il file \""
	 << filename <<"\"" << endl;
    return false;
  }else{
    ofstream outfile(filename.c_str());
    if(!outfile.is_open()){
      cout << "Non sono riuscito ad aprire il file \""
	   << filename <<"\"" << endl;
      return false;
    }else{
      for(int i= 0;i<CS_nt/1;i+=timespan){
	int t = CS_ns * i;
	for(int j = 0;j< CS_ns ;j+=spacespan){
	  outfile << i*timestep  << "\t" << j*spacestep << "\t"
		  << CS_data[t+j]<<endl;
	}
      }
      cout << "Ho salvato i dati sul file \""
	   << filename <<"\"" << endl;
      return true;
    }
  }
}

void CranckSolver::processCC(){
  int t = CS_step*CS_ns; //dummy per comodita`
  int tm1 = (CS_step-1)*CS_ns; //dummy per comodita`
  CS_data[t+0] = CS_cci;
  CS_data[t+CS_ns-1] = CS_cce;
}
