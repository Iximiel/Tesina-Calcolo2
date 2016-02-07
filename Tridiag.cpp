#include "Tridiag.hpp"

tridiag::tridiag(int N){
  dim = N;
  a = new Var[dim];
  c = new Var[dim];
  d = new Var[dim];
  ak = new Var[dim];
  ck = new Var[dim];
  dk = new Var[dim];
  h = nullptr;
}

tridiag::tridiag(const tridiag& x){
  dim = x.dim;
  a = new Var[dim];
  c = new Var[dim];
  d = new Var[dim];
  ak = new Var[dim];
  ck = new Var[dim];
  dk = new Var[dim];
  h = nullptr;
  for(int i=0;i<dim;i++){
    a[i] = x.a[i];
    c[i] = x.c[i];
    d[i] = x.d[i];
    ak[i] = x.ak[i];
    ck[i] = x.ck[i];
    dk[i] = x.dk[i];
  }
}

tridiag::~tridiag(){
  delete[] a;
  delete[] c;
  delete[] d;
  delete[] ak;
  delete[] ck;
  delete[] dk;
  if(h!=nullptr)
    delete[] h;
}

tridiag& tridiag::operator=(const tridiag& x){
  if (this != &x){ // protect against invalid self-assignment
    dim = x.dim;
    a = new Var[dim];
    c = new Var[dim];
    d = new Var[dim];
    ak = new Var[dim];
    ck = new Var[dim];
    dk = new Var[dim];
    h = nullptr;
    for(int i=0;i<dim;i++){
      a[i] = x.a[i];
      c[i] = x.c[i];
      d[i] = x.d[i];
      ak[i] = x.ak[i];
      ck[i] = x.ck[i];
      dk[i] = x.dk[i];
    }
  }
  // by convention, always return *this
  return *this;
}

void tridiag::create_h(bool lastPointDirichlet){
  if(h!=nullptr)
    delete h;
  
  /*****************************************************************
   *NB la matrice e` quadrata di dim x dim (considerando
   *quindi la diagonale superiore e` di dim-1 elementi
   *l'indice parte da 0 e arriva a dim-2
   *ma la faccio di dim per avere l'elemento dim-1 come "0"
   *semplificando cosi` la struttura dell'algoritmo(meno ecezzioni)
   *****************************************************************/
  
  h = new Var[dim];
  h[0] =  c[0]/(d[0]);//se uso Dirichlet devo far si` che sia 0
  h[dim-1] = 0;// non esiste h nell'ultima riga!

  for(int i=1;i<dim-1;i++)
    h[i] = c[i]/(d[i]-a[i]*h[i-1]);
  
  if(lastPointDirichlet)
    h[dim-2]=0;
}

Var tridiag::bi(int i, Var F_nm1,Var F_n,Var F_np1){
  //preferisco avere il vettore dei bi esterno, dato che sara` temporaneo, anzi me ne servira` uno alla volta, l'eccezione delle condizioni al contorno sara` data nell'algoritmo che includera` questa funzione
  Var toreturn = ak[i] * F_nm1 + dk[i] * F_n + ck[i] *F_np1;
  return toreturn;
}



void tridiag::setUnknown(int i, Var A, Var D, Var C){
  a[i] = A;
  d[i] = D;
  c[i] = C;
}

void tridiag::setKnown(int i, Var A, Var D, Var C){
  ak[i] = A;
  dk[i] = D;
  ck[i] = C;
}




