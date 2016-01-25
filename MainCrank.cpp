#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct tridiag{
  double *a, *d,*c;
  tridiag(int N){
    a = new double[N];
    c = new double[N];
    d = new double[N];
  }
};

double* make_h(tridiag matr,int N){
  double *h = new double[N-1];//N-1 perche` la diagonale sopra alla diagonale e` di N-2 numeri (
  h[0] = 0;//0 e` l'indice della condizione a contorno
  h[1] = matr.c[1]/matr.d[1];
  for(int i=2;i<N-1;i++){
    h[i] = matr.c[i]/(matr.d[i]-matr.a[i]*h[i-1]);
    // cout<< h[i]<<endl;
  }
  //cin.get();
  
  return h; 
}

void Stepper(double* data,int Nt, int Ns, tridiag diag, double *h, double firstCC,double lastCC){
  data[Nt*Ns] = firstCC;
  data[(Nt+1)*Ns-1] = lastCC;
  int tm1 = (Nt-1)*Ns;
  double *p = new double[Ns-1];
  p[0] = 0;//0 e` un valore dummy //0 e Ns-1 non servono in quanto calcolerebbero le CC
  double b1 = data[Nt*Ns]+data[tm1+0]+diag.d[0]*data[tm1+1]+data[tm1+2];
  //cout<<  data[Nt*Ns]<<"+"<<data[tm1+0]<<"+"<<diag.d[0]*data[tm1+1]<<"+"<<data[tm1+2]<<endl;
  //b1 = t_0^(j+1)+t_0^j+(2/eta+2)t_1^j+t_2^j
  p[1] = b1/diag.d[1];

  for(int i=2;i<Ns-2;i++){
    double bi = data[tm1+i-1]+diag.d[i]*data[tm1+i]+data[tm1+i+1];
    if(abs(i-Ns/2) <5)
      cout <<  i<<" "  << data[tm1+i-1]<<"+"<<diag.d[i]*data[tm1+i]<<"+"<<data[tm1+i+1]<<endl;
    //bi = t_(i-1)^(j+1)+t_0^j+(2/eta+2)t_(i)^j+t_(i+1)^j
    p[i] = (bi-diag.a[i]*p[i-1])/(diag.d[i]-diag.a[i]*h[i-1]);
    if(abs(i-Ns/2) <5)
      cout << "\t" <<  p[i]<<"="<<"("<<bi<<"-"<<diag.a[i]*p[i-1]<<")/("<<diag.d[i]<<"-"<<diag.a[i]*h[i-1]<<")"<<endl;
  }
  double bnm1 = data[(Nt+1)*Ns-1]+data[tm1+(Ns-1)-2]+diag.d[Ns-1]*data[tm1+(Ns-1)-1]+data[tm1+(Ns-1)];
  //bnm1 = t_n^(j+1)+t_(n-2)^j+(2/eta+2)t_(n-1)^j+t_(n)^j  //vanno ridotti di 1 per convenzione c
  p[Ns-2] = (bnm1-diag.a[Ns-2]*p[Ns-2])/(diag.d[Ns-2]-diag.a[Ns-2]*h[Ns-2-1]);
  for(int i=Ns-2;i>1;i--){
    data[Nt*Ns+i] = p[i]-data[Nt*Ns+i+1]*h[i];
    if(abs(i-Ns/2) <5)
      cout<< i<<" "<<data[(Nt)*Ns+i]<<"="<< p[i]<<"-"<<data[(Nt)*Ns+i+1]<<"*"<<h[i]<<"\t"<< data[(Nt-1)*Ns+i] <<endl;
  }
   cin.get();
  delete p;
}

int main(int argc, char** argv){
  double *data;//[tempo*spazio]
  double lenght=10, tmax=1;
  int Nl = 1000, Nt = 100;
  double spacestep = lenght/Nl;
  double timestep = tmax/Nt;
  double k = 1.1;//diffusivita`
  double eta = k* timestep/(spacestep*spacestep);
  cout << "eta= "<<eta<<"="<<k<<"*"<<timestep<<"/"<<spacestep<<"^2" <<endl;
  data = new double[Nl*Nt];
  //condizioni iniziali

  tridiag mat(Nl);
  
  for(int j = 0;j< Nl;j++){
    data[j]=0;
    mat.a[j]=mat.c[j] = -1;
    mat.d[j] = 2./eta-2;;
  }
  data[Nl/2] = 1;
  double *h = make_h(mat,Nl);
  for(int i = 1;i< Nt;i++)
    Stepper(data,i,Nl,mat,h,0,0);
  
  ofstream ofile("crankout.txt");
  for(int i= 0;i<Nt/1;i+=1){
    for(int j = 0;j< Nl;j++){
      ofile << i*timestep  << "\t" << j*spacestep << "\t" << data[i*Nl+j]<<endl;
    }
  }
  return 0;

}
