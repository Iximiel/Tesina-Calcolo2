#include "CrankSolver.hpp"
#include <iostream>

#ifdef DEBUG
#include <cmath>//per gli abs
void wait(){
  cout<< "Premi enter per continuare."<<endl;
  cin.get();
}
#endif //DEBUG

using namespace std;

CrankSolver::CrankSolver(const tridiagM &mat, int Ns, const char *options, Var CCi, Var CCe)
  :CS_mat(mat){
  
  CC0 = options[0];
  CCN = options[1];  

  CS_ns = Ns;
  CS_cci = CCi;
  CS_cce =CCe;
  CS_data = nullptr;
  CS_data = nullptr;
  CS_step = 0;
  CS_mat.create_h(CCN == 'D');
}

CrankSolver::~CrankSolver(){
  delete CS_data;
}

void CrankSolver::SetInitialState(Var* initialVector){
  CS_data = new Var[CS_ns];
  for(int i=0;i<CS_ns;i++)
    CS_data[i] = initialVector[i];
  CS_step =1;
#ifdef DEBUG
  cout << "Acquisite condizioni iniziali"<< endl;
#endif //DEBUG
}

int CrankSolver::doStep(){
  if(CS_step ==0){
    cout << "Non ho acquisito le condizioni iniziali"<<endl;
  }else{
    delete CS_data_prec;
    CS_data_prec = CS_data;//sposto i vecchi punti sul nuovo array
    CS_data = new Var[CS_ns];
    Stepper();
    CS_step++;
  }
  return CS_step;
}

Var CrankSolver::getPoint(int t, int x){
  return CS_data[x];
}
//da fare: rendere lo stepper flessibile
void CrankSolver::Stepper(){
  Var *p = new Var [CS_ns];
  //0 e` l'indice delle condizioni al contorno, se uso Dirichlet 0 serve a non aggiungere eccezioni all'algoritmo
  //la spiegazione e` in create_h() di Tridiag.cpp
  //preparo il vettore delle p[]
  int pstart = 1, pstop = 1;
  if(CC0 == 'D'){
    p[0] = CS_cci;
    pstart = 2;
    Var b1 = CS_mat.bi(1,CS_data_prec[0],
		       CS_data_prec[1],
		       CS_data_prec[2]);
	b1 -= CS_mat.GetA(1)*CS_cci;
	p[1] =  CS_mat.pi(1,0,b1);
	//in questo caso mi aspetto che h[0]=0
  }else{
    p[0] = CS_mat.pi(0,0,
		     CS_mat.bi(0,0,CS_data_prec[0],CS_data_prec[1])+CS_cci);
  }
  if(CCN == 'D')
    pstop = 2;
  for(int i=pstart;i<CS_ns-pstop;i++){
    //calcolo il valore di b[i]
    Var bi = CS_mat.bi(i,CS_data_prec[i-1],
		       CS_data_prec[i],
		       CS_data_prec[i+1]);
    p[i] = CS_mat.pi(i,p[i-1],bi);
#ifdef DEBUG
    if(abs(CS_ns/2.-i)<=5){
      cout << i <<": b[i] = "<< bi <<" p[i]= "<<p[i];//<<endl;
      cout << "\t" <<  (CS_mat.d[i]-CS_mat.a[i]*h[i-1])<< " " << h[i-1]<<endl;
    }
#endif //DEBUG
  }
  //assegno l'ultimo punto
  if(CCN == 'D'){
    p[CS_ns-1] = CS_cce;
    //matematicamente e` sbagliato, ma preferisco avere meno ecezzioni possibili nell'algoritmo
    Var bNm2 = CS_mat.bi(CS_ns-2,CS_data_prec[CS_ns-3],
		       CS_data_prec[CS_ns-2],
		       CS_data_prec[CS_ns-1]);
	bNm2 -= CS_cce * CS_mat.GetC(CS_ns-2);
	p[CS_ns-2] =  CS_mat.pi(CS_ns-2,p[CS_ns-3],bNm2);
	//in questo caso mi aspetto che h[CS_ns-2]=0
	CS_data[CS_ns-2] = p[CS_ns-2];
  }else{
    p[CS_ns-1] = CS_mat.pi(CS_ns-1,p[CS_ns-2],
			   CS_mat.bi(CS_ns-1,
				     CS_data_prec[CS_ns-2],
				     CS_data_prec[CS_ns-1],
				     0)+CS_cce);
  }
  //ora procedo finalmente con l'assegnare i risultati
  CS_data[CS_ns-1] = p[CS_ns-1];
  for(int i=CS_ns-pstop-1;i>=0;i--){//parte da n-2 o n-3 se uso dirichlet
    CS_data[i] = p[i] - CS_mat.H(i) * CS_data[i+1];
    //da pi = xi + hi x(i+1)
#ifdef DEBUG
    if(abs(CS_ns/2.-i)<=5)
      cout << i <<": p[i]= "<<p[i] <<",x[i](t-1)="<<CS_data_prec[i]
	   <<"=>x[i](t)="<<CS_data[i]<<endl;
#endif //DEBUG
  }
#ifdef DEBUG
  wait();
#endif //DEBUG
}
