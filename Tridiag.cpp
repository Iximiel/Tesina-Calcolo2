#include "Tridiag.hpp"

tridiag::tridiag(int N){
  dim = N;
  a = new Var[dim];
  c = new Var[dim];
  d = new Var[dim];
  ak = new Var[dim];
  ck = new Var[dim];
  dk = new Var[dim];
  e = new Var[dim];
  ek = new Var[dim];
  h = nullptr;
}

tridiag::tridiag(const tridiag& x)
{
  dim = x.dim;
  a = new Var[dim];
  c = new Var[dim];
  d = new Var[dim];
  e = new Var[dim];
  ak = new Var[dim];
  ck = new Var[dim];
  dk = new Var[dim];
  ek = new Var[dim];
  h = nullptr;
  for(int i=0;i<dim;i++){
    a[i] = x.a[i];
    c[i] = x.c[i];
    d[i] = x.d[i];
    e[i] = x.e[i];
    ak[i] = x.ak[i];
    ck[i] = x.ck[i];
    dk[i] = x.dk[i];
    ek[i] = x.ek[i];
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
  delete[] e;
  delete[] ek;
}

tridiag& tridiag::operator=(const tridiag& x){
  if (this != &x){ // protect against invalid self-assignment
    dim = x.dim;
    a = new Var[dim];
    c = new Var[dim];
    d = new Var[dim];
    e = new Var[dim];
    ak = new Var[dim];
    ck = new Var[dim];
    dk = new Var[dim];
    ek = new Var[dim];
    h = nullptr;
    for(int i=0;i<dim;i++){
      a[i] = x.a[i];
      c[i] = x.c[i];
      d[i] = x.d[i];
      e[i] = x.e[i];
      ak[i] = x.ak[i];
      ck[i] = x.ck[i];
      dk[i] = x.dk[i];
      ek[i] = x.ek[i];
    }
  }
  // by convention, always return *this
  return *this;
}

void tridiag::create_h(){
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
}

Var tridiag::pi(int i, Var pim1, Var bi){
  //preferisco avere il vettore dei pi esterno, dato che sara` temporaneo
  if(i==0)
    return bi/d[i];
  else
    return (bi-a[i]*pim1)/(d[i]-a[i]*h[i-1]);
}

Var tridiag::bi(int i, Var F_nm1,Var F_n,Var F_np1){
  //preferisco avere il vettore dei bi esterno, dato che sara` temporaneo,
  //anzi me ne servira` uno alla volta, l'eccezione delle condizioni
  //al contorno sara` data nell'algoritmo che includera` questa funzione
  Var toreturn = ak[i] * F_nm1 + dk[i] * F_n + ck[i] *F_np1;
  toreturn += ek[i] - e[i];
  return toreturn;
}

void tridiag::setUnknown(int i, Var A, Var D, Var C, Var E){
  a[i] = A;
  d[i] = D;
  c[i] = C;
  e[i] = E;
}

void tridiag::setKnown(int i, Var A, Var D, Var C, Var E){
  ak[i] = A;
  dk[i] = D;
  ck[i] = C;
  ek[i] = E;
}

void tridiag::SetE(int i, Var E){e[i] = E;}
void tridiag::SetA(int i, Var A){a[i] = A;}
void tridiag::SetC(int i, Var C){c[i] = C;}

Var tridiag::H(int i){return h[i];}

Var tridiag::GetA(int i){return a[i];}
Var tridiag::GetD(int i){return d[i];}
Var tridiag::GetC(int i){return c[i];}
Var tridiag::GetE(int i){return e[i];}

Var tridiag::GetAk(int i){return ak[i];}
Var tridiag::GetDk(int i){return dk[i];}
Var tridiag::GetCk(int i){return ck[i];}
Var tridiag::GetEk(int i){return ek[i];}
