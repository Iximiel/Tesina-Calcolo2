#include "CrankSolver.hpp"
#include <iostream>

using namespace std;

CrankSolver::CrankSolver(tridiag *mat, int Ns){
  CS_mat = mat;

  CS_ns = Ns;
  CS_data = nullptr;
  CS_step = -1;
  CS_mat->create_h();
}

CrankSolver::~CrankSolver(){
  delete[] CS_data;
  delete CS_mat;
}

void CrankSolver::SetInitialState(Var* initialVector){
  CS_data = new Var[CS_ns];
  for(int i=0;i<CS_ns;i++)
    CS_data[i] = initialVector[i];
  CS_step =0;
}

int CrankSolver::doStep(){
  if(CS_step <0){
    cout << "Non ho acquisito le condizioni iniziali"<<endl;
  }else{
    Stepper();
    CS_step++;
  }
  return CS_step;
}

Var CrankSolver::getPoint(int x){
  return CS_data[x];
}
//da fare: rendere lo stepper flessibile
void CrankSolver::Stepper(){
  //preparo il vettore delle p[]
  //NB: il vettore CS_data in memoria in questo mometo e` il vettore del passo precedente
  Var *p = new Var [CS_ns];
  //0 e` l'indice delle condizioni al contorno, se uso Dirichlet 0 serve a non aggiungere eccezioni all'algoritmo
  //la spiegazione e` in create_h() di Tridiag.cpp
  Var b0 = CS_mat->bi(0,0,
		      CS_data[0],
		      CS_data[1]);
  p[0] = CS_mat->pi(0,0,b0);
  
  for(int i=1;i<CS_ns-1;i++){
    //calcolo il valore di b[i]
    Var bi = CS_mat->bi(i,CS_data[i-1],
		       CS_data[i],
		       CS_data[i+1]);
    p[i] = CS_mat->pi(i,p[i-1],bi);
  }
  Var bnm1 = CS_mat->bi(CS_ns-1,
			CS_data[CS_ns-2],
			CS_data[CS_ns-1],0);
  p[CS_ns-1] = CS_mat->pi(CS_ns-1,p[CS_ns-2],
			  bnm1);
  //ora procedo finalmente con l'assegnare i risultati
  //CS_data diventa il vettore del passo attuale
  CS_data[CS_ns-1] = p[CS_ns-1];
  for(int i=CS_ns-2;i>=0;i--){
    CS_data[i] = p[i] - CS_mat->H(i) * CS_data[i+1];
    //da pi = xi + hi x(i+1)G
  }
  delete[] p;
    //NB: il vettore CS_data in memoria  ora e` il vettore del passo attuale
}
