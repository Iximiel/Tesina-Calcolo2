#include "TridiagMore.hpp"

tridiagM::tridiagM(int N)
  : tridiag(N){
  e = new Var[dim];
  ek = new Var[dim];
}

tridiagM::tridiagM(const tridiag& x)
  : tridiag(x){
  e  = new Var[dim];
  ek = new Var[dim];
  for(int i=0;i<dim;i++){
    e[i]  = 0;
    ek[i] = 0;
  }
}

tridiagM::tridiagM(const tridiagM& x)
  :tridiag(x)
{
  /* dim = x.dim;
  a = new Var[dim];
  c = new Var[dim];
  d = new Var[dim];*/
  e = new Var[dim];
  /*ak = new Var[dim];
  ck = new Var[dim];
  dk = new Var[dim];*/
  ek = new Var[dim];
  //  h = nullptr;
  for(int i=0;i<dim;i++){
    /* a[i] = x.a[i];
    c[i] = x.c[i];
    d[i] = x.d[i];*/
    e[i] = x.e[i];
    /* ak[i] = x.ak[i];
    ck[i] = x.ck[i];
    dk[i] = x.dk[i];*/
    ek[i] = x.ek[i];
  }
}

tridiagM& tridiagM::operator=(const tridiagM& x){
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
/*
tridiagM& tridiagM::operator=(const tridiag& x){
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
      e[i] = 0;
      ak[i] = x.ak[i];
      ck[i] = x.ck[i];
      dk[i] = x.dk[i];
      ek[i] = 0;
    }
  }
  // by convention, always return *this
  return *this;
}
*/
Var tridiagM::bi(int i, Var F_nm1,Var F_n,Var F_np1){
  //preferisco avere il vettore dei bi esterno, dato che sara` temporaneo, anzi me ne servira` uno alla volta, l'eccezione delle condizioni al contorno sara` data nell'algoritmo che includera` questa funzione
  Var toreturn = tridiag::bi(i,F_nm1,F_n,F_np1) + ek[i] - e[i];
  return toreturn;
}

void tridiagM::setUnknown(int i, Var A, Var D, Var C, Var E){
  a[i] = A;
  d[i] = D;
  c[i] = C;
  e[i] = E;
}

void tridiagM::setKnown(int i, Var A, Var D, Var C, Var E){
  ak[i] = A;
  dk[i] = D;
  ck[i] = C;
  ek[i] = E;
}

Var tridiagM::GetE(int i){return e[i];}

Var tridiagM::GetEk(int i){return ek[i];}
