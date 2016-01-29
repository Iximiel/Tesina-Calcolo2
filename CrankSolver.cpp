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

CranckSolver::CranckSolver(const tridiagM &mat, int Ns, int Nt, const char *options, Var CCi, Var CCe)
  :CS_mat(mat){
  
  CC0 = options[0];
  CCN = options[1];  

  CS_ns = Ns;
  CS_nt = Nt;
  CS_cci = CCi;
  CS_cce =CCe;
  CS_data = new Var [CS_ns * CS_nt];
  CS_step = 0;
  CS_mat.create_h(CCN == 'D');
}

CranckSolver::~CranckSolver(){
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
    Stepper();
    CS_step++;
    return true;
  }
}

Var CranckSolver::getPoint(int t, int x){
  return CS_data[t*CS_ns+x];
}
//da fare: rendere lo stepper flessibile
void CranckSolver::Stepper(){
  int t = CS_step*CS_ns; //dummy per comodita`
  int tm1 = (CS_step-1)*CS_ns; //dummy per comodita`
  Var *p = new Var [CS_ns];
  //0 e` l'indice delle condizioni al contorno, se uso Dirichlet 0 serve a non aggiungere eccezioni all'algoritmo
  //la spiegazione e` in create_h() di Tridiag.cpp
  //preparo il vettore delle p[]
  int pstart = 1, pstop = 1;
  if(CC0 == 'D'){
    p[0] = CS_cci;
    pstart = 2;
    Var b1 = CS_mat.bi(1,CS_data[tm1+0],
		       CS_data[tm1+1],
		       CS_data[tm1+2]);
	b1 -= CS_mat.GetA(1)*CS_cci;
	p[1] =  CS_mat.pi(1,0,b1);
	//in questo caso mi aspetto che h[0]=0
  }else{
    p[0] = CS_mat.pi(0,0,
		     CS_mat.bi(0,0,CS_data[tm1],CS_data[tm1+1])+CS_cci);
  }
  if(CCN == 'D')
    pstop = 2;
  for(int i=pstart;i<CS_ns-pstop;i++){
    //calcolo il valore di b[i]
    Var bi = CS_mat.bi(i,CS_data[tm1+i-1],
		       CS_data[tm1+i],
		       CS_data[tm1+i+1]);
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
    Var bNm2 = CS_mat.bi(CS_ns-2,CS_data[tm1+CS_ns-3],
		       CS_data[tm1+CS_ns-2],
		       CS_data[tm1+CS_ns-1]);
	bNm2 -= CS_cce * CS_mat.GetC(CS_ns-2);
	p[CS_ns-2] =  CS_mat.pi(CS_ns-2,p[CS_ns-3],bNm2);
	//in questo caso mi aspetto che h[CS_ns-2]=0
	CS_data[t+CS_ns-2] = p[CS_ns-2];
  }else{
    p[CS_ns-1] = CS_mat.pi(CS_ns-1,p[CS_ns-2],
			   CS_mat.bi(CS_ns-1,
				     CS_data[tm1+CS_ns-2],
				     CS_data[tm1+CS_ns-1],
				     0)+CS_cce);
  }
  //ora procedo finalmente con l'assegnare i risultati
  CS_data[t+CS_ns-1] = p[CS_ns-1];
  for(int i=CS_ns-pstop-1;i>=0;i--){//parte da n-2 o n-3 se uso dirichlet
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
#ifdef USECOMPLEX
    ofstream outfile(filename.c_str());
    ofstream Coutfile(("i"+filename).c_str());
    ofstream Noutfile(("N"+filename).c_str());
    if(!outfile.is_open()){
      cout << "Non sono riuscito ad aprire il file \""
	   << filename <<"\"" << endl;
      return false;
    }else if(!Coutfile.is_open()){
      cout << "Non sono riuscito ad aprire il file \""
	   << "i"+filename <<"\"" << endl;
      return false;
    }else if(!Noutfile.is_open()){
      cout << "Non sono riuscito ad aprire il file \""
	   << "N"+filename <<"\"" << endl;
      return false;
    }else{
      for(int i= 0;i<CS_nt/1;i+=timespan){
	int t = CS_ns * i;
	for(int j = 0;j< CS_ns ;j+=spacespan){
	  outfile << i*timestep  << "\t" << j*spacestep << "\t"
		  << CS_data[t+j].real()<<endl;
	  Coutfile << i*timestep  << "\t" << j*spacestep << "\t"
		   << CS_data[t+j].imag()<<endl;
	  Noutfile << i*timestep  << "\t" << j*spacestep << "\t"
		   << norm(CS_data[t+j])<<endl;
	}
      }
      cout << "Ho salvato i dati sui file \""
	   << filename <<"\", \""
      	   << "i"+filename <<"\" e \""
      	   << "N"+filename <<"\"" << endl;
      return true;
    }
#else
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
#endif
  }
}

bool CranckSolver::writeEverithing(string filename, double timestep, double spacestep){//timestep e spacestep non vengono salvati nel Solver
  //l'idea e` salvare un file con tutti i dati in questo modo:
  /*
    real/complex
    N_Passi_temporali passo_T
    N_Passi_spaziali passo_S
    riga per il passo T_0(CI)
    riga per il passo T_1
    ....
    riga per il passo CS_step(in caso ci siamo fermati prima della fine)
    in caso di complessi ogni riga avra real_0 img_0 norm_0 real_1 img_1 norm_1... e cosi` via sino alla fine
  */
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
#ifdef USECOMPLEX
      outfile << "complex"<<endl;
#else
      outfile << "real"<<endl;
#endif
      outfile << CS_step << timestep << endl
	      << CS_ns << spacestep<< endl;
      for(int i= 0;i<CS_step;i++){
	int t = CS_ns * i;
	for(int j = 0;j< CS_ns ;j++){
#ifdef USECOMPLEX
	  outfile << "\t" << CS_data[t+j].real() << CS_data[t+j].imag() << norm(CS_data[t+j]);
#else
	  outfile << CS_data[t+j];
#endif
	}
	outfile << endl;
      }
      cout << "Ho salvato i dati sul file \""
	   << filename <<"\"" << endl;
      return true;
    }
  }
}
