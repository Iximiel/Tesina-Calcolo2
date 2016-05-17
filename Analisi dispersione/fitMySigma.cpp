{
  string data[9] = {"p", "m10s4", "m10","m2s4","m2","m1s4","m1s1e10","m1s2e10","m1s4e10"};
  TCanvas c("c");
  for(int i=7;i<9;i++){
    ifstream file("dispersione"+data[i]+"_data.nfo");
    TGraph a(21);
    for(int j=0;j<21;j++){
      double dummy, t, sigma;
      file >> t >> dummy >> dummy >> sigma;
      a.SetPoint(j,t,sigma);
    }
    file.close();
    TF1 f("myFit","sqrt(([0]**4+([1]*x)**2)/[0]**2)",0,11);
    a.SetTitle("");
    f.SetParameters(1,1);
    f.SetParNames("#sigma_0","#hbar/m");
    a.Fit("myFit");
    a.SetMarkerStyle(2);
    a.Draw("ap");
    gStyle->SetOptFit(true);
    char fname[100];
    sprintf(fname,"./dispersione_%s.png",data[i].c_str());
    c.SaveAs(fname);
  }
/*#include <iostream>
#include <fstream>

#include <TGraph.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TStyle.h>

using namespace std;
// g++ -std=c++11 -g -Wall fitMySigma.cpp `root-config --cflags --glibs`
int main(int argc, char** argv)*/
}
