double teo(double x){
  return x<1?
	   1:
    (-1+sqrt(1-1/x))*(-1+sqrt(1-1/x))/((1+sqrt(1-1/x))*(1+sqrt(1-1/x)));
}

void table(){
  ifstream f("pesi2.dat");
  int n=11;
  double ev[n], fhS1[n], shS1[n], fhS2[n], shS2[n], fhS3[n], shS3[n], fhS4[n], shS4[n];
  for(int i=0;i<9;i++){
    string dummy;
    f >> dummy;
  }
  for(int i=0;i<n;i++)
    f >> ev[i] >> fhS1[i] >> shS1[i] >> fhS2[i] >> shS2[i] >> fhS3[i] >> shS3[i] >> fhS4[i] >> shS4[i];
  ofstream r("latex.txt");

  for(int i=0;i<n;i++){
    r << "$" << ev[i] << "$\t&\t$" << fhS1[i] <<"$\t&\t$"
      << fhS2[i] <<"$\t&\t$"  << fhS3[i] <<"$\t&\t$"
      << fhS4[i] <<"$\t&\t$" << teo(ev[i])<<"$\t\t \\\\ \\midrule"<<endl;
  }
  for(int i=0;i<n;i++){
    r << "$" << ev[i] << "$\t&\t$" << shS1[i] <<"$\t&\t$"
      << shS2[i] <<"$\t&\t$"  << shS3[i] <<"$\t&\t$"
      << shS4[i] <<"$\t&\t$" << 1-teo(ev[i])<<"$\t\t \\\\ \\midrule"<<endl;
  }
  r.close();
}
