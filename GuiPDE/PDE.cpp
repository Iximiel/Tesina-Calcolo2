#include "PDE.hpp"
#include <cmath>

//debug
#include <iostream>

PDECond::PDECond(){
  #ifndef __CINT__
  cc = nullptr;
  succ = nullptr;
  prec = nullptr;
  #endif /* __CINT __ */
  Eps = 1;
  SOR_par = 1.75;
  peso_errMax = 0.05;
  M = mJacobi;
  CI = 0.1;
  rho = 1;
}
PDECond::~PDECond(){
  for(int i=0; i<Y;i++){
    delete[] succ[i];
    delete[] prec[i];
    delete[] cc[i];
  }
  delete succ;
  delete prec;
  delete cc;
}

void PDECond::SetXY(int x,int y, double xdim, double ydim){
  X = x;
  Y = y;
  Xdim = xdim;
  Ydim = ydim;
  passoX = Xdim/X;
  passoY = Ydim/Y;
  Delq = passoX*passoY;
  /*
 for(int i=0; i<Y;i++){
    delete[] succ[i];
    delete[] prec[i];
    delete[] cc[i];
  }
  delete succ;
  delete prec;
  delete cc;
  */
  prec = new double*[X];
  succ = new double*[X];
  cc = new double*[X];
  for(int i=0; i<X;i++){
    prec[i] = new double[Y];
    succ[i] = new double[Y];
    cc[i] = new double[Y];
    for(int j=0; j<Y;j++){
      if(CI!=0){
	if(j*i==0)
	  prec[i][j] = 0;
	else if(j == (X-1))
	  prec[i][j] = 0;
	else if(i == (Y-1))
	  prec[i][j] = 0;
	else
	  prec[i][j] = CI;
      }else
	prec[i][j] = 0;
      succ[i][j] =  cc[i][j]=0;
    }
  }
  std::cout<< "SetXY(int x,int y, double xdim, double ydim) done\n";
}

double PDECond::Jacobi(int x,int y){
  double toreturn = prec[x+1][y]+prec[x][y+1]+prec[x-1][y]+prec[x][y-1];
  toreturn += 1/Eps*cc[x][y]*Delq;
  toreturn /= 4.;
  return toreturn;
}

double PDECond::GaussSeidel(int x,int y){
  double toreturn = prec[x+1][y]+prec[x][y+1]+succ[x-1][y]+succ[x][y-1];
  toreturn += 1/Eps*cc[x][y]*Delq;
  toreturn /= 4.;
  return toreturn;
}

double PDECond::SOR(int x,int y){
  double r = prec[x+1][y]+prec[x][y+1]+succ[x-1][y]+succ[x][y-1];
  r += 1/Eps*cc[x][y]*Delq;

  r /= 4.;
  r -= prec[x][y];
  return prec[x][y]+r*SOR_par;
}

double PDECond::Passo(){
  for(int i=1; i<X-1;i++){
    for(int j=1; j<Y-1;j++){
      if(M == mSOR)
	succ[i][j] = SOR(i,j);
      else if(M == mGaussSeidel)
	succ[i][j] = GaussSeidel(i,j);
      else
	succ[i][j] = Jacobi(i,j);
    }
  }
  return getErr();//ritorna l'errore la precisione e` decisa dall'utente
}

double PDECond::getErr(){
  double maxErr=0, sumErr=0;
  for(int i=1; i<X-1;i++){
    for(int j=1; j<Y-1;j++){
      double diff = std::abs(prec[i][j]-succ[i][j]);
      //possibilita` 1: errore piu` grande
      if(diff>maxErr)
	maxErr = diff;
      //possibilita` 2: media degli errori
      sumErr += diff;
    }
  }
  sumErr/=(Y*X);
  double error = peso_errMax * maxErr + (1-peso_errMax) * sumErr;
  for(int i=1; i<X-1;i++){//copio succ in prec l'esterno e` sempre 0
    for(int j=1; j<Y-1;j++)
      prec[i][j] = succ[i][j];
  }
  return error;
}
void PDECond::SetCC(double lenght, double dist){
  int posy = (Ydim-lenght)/(2*passoY);
  int posx = (Xdim-dist)/(2.*passoX);
  SetCC(posy,posx);
  std::cout<< "SetCC(double lenght, double dist) done\n";
}

void PDECond::SetCC(int posy, int posx){
    for(int j=posy; j<Y-posy;j++){
    //retep[posx][j] =
    cc[posx][j] = -rho;
    //retep[Long-posx][j] =
    cc[X-posx][j] = rho;
  }
    std::cout<< "SetCC(int posy, int posx) done\n";
}

void PDECond::SetMethod(int m, double sor){
  M = m;
  SOR_par = sor;
    std::cout<< "SetMethod(int m, double sor) done\n";
}
void PDECond::SetPrecisionOnErrMax(double weight){
  peso_errMax = weight;
  std::cout<< "SetPrecisionOnErrMax(double weight) done\n";
}
void PDECond::SetCI(double ci){
  CI = ci;
  std::cout<< "SetCI(double ci) done\n";
}

double** PDECond::GetData(){return succ;}
int PDECond::GetNum(){return X*Y;}
double PDECond::GetData(int x, int y){return succ[x][y];}
double PDECond::GetPassoX(){return passoX;}
double PDECond::GetPassoY(){return passoY;}

