double teoria(double x){
  return x<1?1:(-1+sqrt(1-1/x))*(-1+sqrt(1-1/x))/((1+sqrt(1-1/x))*(1+sqrt(1-1/x)));
}
void Step(){
  const int n = 7;
  double rapporto[n]={10, 4, 2, 4./3., 1, 0.5, 1./3.};
  /* double s05[n]={0.0269145, 0.0734267, 0.176025, 0.347206, 0.866648, 1, 1};
     double s1[n]={0.0268029, 0.0730522, 0.174585, 0.340294, 0.903143, 1, 1};
     double s2[n]={0.0267752, 0.0729597, 0.174234, 0.338735, 0.936857, 1, 1};
     double s4[n]={0.0267683, 0.0729367, 0.174147, 0.338353, 0.966585, 1, 1};*/
  double s[4][n]= {{0.0269145, 0.0734267, 0.176025, 0.347206, 0.866648, 1, 1},
		   {0.0268029, 0.0730522, 0.174585, 0.340294, 0.903143, 1, 1},
		   {0.0267752, 0.0729597, 0.174234, 0.338735, 0.936857, 1, 1},
		   {0.0267683, 0.0729367, 0.174147, 0.338353, 0.966585, 1, 1}};
  double teo[n];
  for(int i=0;i<n;i++)
    teo[i] = teoria(rapporto[i]);
  TMultiGraph *grafi = new TMultiGraph("data","Dati");
  TGraph *Teo = new TGraph(n,rapporto,teo);
  grafi->Add(Teo);
  Teo->SetMarkerStyle(3);
  //  Teo->Draw("ap");
  string titles[4] = {"#sigma=0.5","#sigma=1","#sigma=2","#sigma=4"};
  for (int i=0;i<4;i++){
    TGraph *t = new TGraph(n,rapporto,s[i]);
    t->SetMarkerStyle(3);
    t->SetMarkerColor(i+2);
    t->SetLineColor(i+2);
    t->SetTitle(titles[i].c_str());
    //   t->Draw("samep");
    grafi->Add(t);
  }
  TCanvas *C = new TCanvas("c","mia");
  grafi->Draw("ap");
  C->BuildLegend();
}
