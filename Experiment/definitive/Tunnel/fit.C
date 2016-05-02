double func(double *x, double *par){
  //par[0]=a
  //par[1]=m
  //par[2]=En
  return (x[0]==1)?1-2/(2+par[0]*par[0]*par[2]*par[1]):1 +(8*(x[0]-1)*x[0])/(cos(2*par[0]*sqrt(2*par[1]*par[2]*(x[0]-1)))-1-8*x[0]*(x[0]-1));
}

void fit(){
  TGraph *tofit = new TGraph("tunnel100fit.tdt");
  TF1 *myfunc = new TF1("thefunc",func,0.,2.,3,1);
  myfunc->SetParameters(0.1,15.,100.);
  myfunc->SetParNames("a","m","E");
  myfunc->SetParLimits(0,0,1);
  myfunc->SetParLimits(1,0.1,20);
  myfunc->SetParLimits(2,0,300);
  tofit->Fit(myfunc);
  tofit->Draw("ap");
}
