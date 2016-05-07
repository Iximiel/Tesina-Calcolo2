#include "visual.hpp"

#include <TGLabel.h>
#include <TRootEmbeddedCanvas.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TGFileDialog.h>
#include <TAxis.h>
#include <TF1.h>

#include <fstream>
#include <iostream>
using namespace std;



double gauss(double x, double a, double b){return exp(-(x-a)*(x-a)/(2*b*b));}
double bump(double x, double a, double b){return (abs(x-a)<b)? M_E*exp(-b*b/(b*b-(x-a)*(x-a))):0;}
double H(double x, double a, double /*b*/){return (x > a)?1:0;}
double barrier (double x, double a, double b){return H(x,a,0) * H(b,x,0);}

Visual::Visual(const TGWindow *p,int w,int h)
  :TGMainFrame(p,w,h,kMainFrame | kHorizontalFrame){
  SetWindowName("Visualizzatore risoluzione equazione di Schrodinger");
  Connect("CloseWindow()","Visual",this,"exit()");//con questo schiacciando la x chiudo il programma e non solo la finestra
  DontCallClose();
  AddFrame(setButtons(this), new TGLayoutHints(kLHintsLeft | kLHintsTop/*|kLHintsExpandX*/|kLHintsExpandY,2,2,2,2));
  TGVerticalFrame *tVBtFrame =  new TGVerticalFrame(this);
  tVBtFrame->AddFrame(setCanvas(tVBtFrame), new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY,2,2,2,2));
  sliderZoom = new TGDoubleHSlider(tVBtFrame);
  tVBtFrame->AddFrame(sliderZoom,new TGLayoutHints(kLHintsExpandX | kLHintsCenterX,2,2,2,2));
  sliderZoom -> Connect("PositionChanged()","Visual",this,"doZoom()");
  tVBtFrame->AddFrame(setSliders(tVBtFrame),new TGLayoutHints(kLHintsExpandX | kLHintsCenterX,2,2,2,2));

  AddFrame(tVBtFrame,new TGLayoutHints(kLHintsExpandY|kLHintsExpandX | kLHintsCenterX,2,2,2,2));
  myRe = nullptr;Re = false;
  myIm = nullptr;Im = false;
  myCI = nullptr;
  myObs = nullptr;
  myVisual = nullptr; 
  myPot = nullptr;
  tfIntegral = nullptr;
  
  SetMWMHints(kMWMDecorAll,
	      kMWMFuncAll,
	      kMWMInputModeless);

  ready(false);  
  MapSubwindows();    
  Resize(GetDefaultSize());
  MapWindow();
  Resize(800,600);
}

Visual::~Visual(){
  // ~TGMainFrame();
}


TGFrame * Visual::setCanvas(const TGWindow *p){
  TRootEmbeddedCanvas* ECanvas = new TRootEmbeddedCanvas(0,p,456,192);
  ECanvas->SetName("Canvas");
  int CanvasID = ECanvas->GetCanvasWindowId();
  showCanvas = new TCanvas("childCanvas", 10, 10, CanvasID);
  ECanvas->AdoptCanvas(showCanvas);
  return ECanvas;
}

TGFrame *Visual::setButtons(const TGWindow *p){
  TGVerticalFrame *tMainFrame =  new TGVerticalFrame(p);
  //hints per le labels:
  TGLayoutHints *btLayout = new TGLayoutHints(kLHintsExpandX | kLHintsTop , 2, 2, 2, 2);
  //  TGLayoutHints *elementsHints =  new TGLayoutHints(kLHintsExpandY | kLHintsExpandX | kLHintsCenterX,2,2,2,2);

  tbOpen = new TGTextButton(tMainFrame, "Apri un file");
  tbOpen->SetToolTipText("Carica un file .dat contente i dati di una simulazione");
  tMainFrame->AddFrame(tbOpen,btLayout);
  tbPot = new TGTextButton(tMainFrame,  "Visualizza un\nPotenziale");
  tbPot->SetToolTipText("Carica un file di un potenziale\ne ne visualizza la forma sulla canvas");
  tMainFrame->AddFrame(tbPot,btLayout);
  tbFit = new TGTextButton(tMainFrame, "Fitta la\nGaussiana");
  tbFit->SetToolTipText("Fa un fit di una gaussiana sulla zona visualizzata");
  tMainFrame->AddFrame(tbFit,btLayout);
  tbDoThing = new TGTextButton(tMainFrame,"Esegui Fit\ne salva");
  tbDoThing->SetToolTipText("Fa diversi fit e salva una serie di immagini e un file con i dati  dei vari fit");  
  tMainFrame->AddFrame(tbDoThing,btLayout);
  tbDoNoImg = new TGTextButton(tMainFrame, "Esegui Fit\ne salva\nsolo dati");
  tbDoNoImg->SetToolTipText("Fa diversi fit e salva un file con i dati  dei vari fit"); 
  tMainFrame->AddFrame(tbDoNoImg,btLayout);
  tbSave = new TGTextButton(tMainFrame,"Salva la\nCanvas");
  tbSave->SetToolTipText("Salva un'immagine della canvas");
  tMainFrame->AddFrame(tbSave,btLayout);
  tbSequence = new TGTextButton(tMainFrame,"Salva \nsequenza");
  tbSequence->SetToolTipText("Salva una sequenza dell'evoluzione temporale in un'immagine");
  tMainFrame->AddFrame(tbSequence,btLayout);
  tbIntegral = new TGTextButton(tMainFrame,"Integrale");
  tbIntegral->SetToolTipText("");
  tMainFrame->AddFrame(tbIntegral,btLayout);
  //  TGCheckButton *cbIm, *cbRe;
  cbRe = new TGCheckButton(tMainFrame,"Re(F)");
  tMainFrame->AddFrame(cbRe,btLayout);
  cbIm = new TGCheckButton(tMainFrame,"Im(F)");
  tMainFrame->AddFrame(cbIm,btLayout);
  
  tbOpen    -> Connect("Clicked()","Visual",this,"OpenFile()");
  tbSave    -> Connect("Clicked()","Visual",this,"SaveFile()");
  tbDoThing -> Connect("Clicked()","Visual",this,"doData()");
  tbDoNoImg -> Connect("Clicked()","Visual",this,"doDataNoImg()");
  tbFit     -> Connect("Clicked()","Visual",this,"DoFit()");
  tbPot     -> Connect("Clicked()","Visual",this,"ShowPot()");
  tbIntegral-> Connect("Clicked()","Visual",this,"callIntegral()");
  tbSequence-> Connect("Clicked()","Visual",this,"doSequence()");
  
  return tMainFrame;
}

TGFrame *Visual::setSliders(const TGWindow *p){
  TGHorizontalFrame *tMainFrame =  new TGHorizontalFrame(p);
  //hints per le labels:
  TGLayoutHints *btLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
  TGLayoutHints *elementsHints =  new TGLayoutHints(kLHintsExpandY | kLHintsExpandX | kLHintsCenterX,2,2,2,2);
  
  tMainFrame->AddFrame(new TGTextButton(tMainFrame, ""),btLayout);//estetica
  sliderT = new TGHSlider(tMainFrame);
  tMainFrame->AddFrame(sliderT,elementsHints);
  lbTime = new TGLabel(tMainFrame,"tempo");
  lbTime->SetWidth(30);
  tMainFrame->AddFrame(lbTime,btLayout);
  tbEaster = new TGTextButton(tMainFrame, "");
  tMainFrame->AddFrame(tbEaster,btLayout);
  
  tbEaster-> Connect("Clicked()","Visual",this,"makeGif()");
  
  sliderT -> Connect("PositionChanged (Int_t)","Visual",this,"SetObs(int)");
  
  sliderT->SetPosition(1);
  return tMainFrame;
}

void Visual::ready(bool bt){
  sliderT->SetEnabled(bt);
  tbFit->SetEnabled(bt);
  tbPot->SetEnabled(bt);
  tbEaster->SetEnabled(bt);
  tbDoThing->SetEnabled(bt);
  tbDoNoImg->SetEnabled(bt);
  tbSave->SetEnabled(bt);
  tbSequence->SetEnabled(bt);
  //
  tbIntegral->SetEnabled(false);
  //
  sliderZoom->Activate(bt);
}

//slots

void Visual::exit(){
  gApplication->Terminate(0);
}

void Visual::callIntegral(){
  if(tfIntegral==nullptr)
    constructInt();
  tfIntegral->MapWindow();
}

void Visual::constructInt(){
  tfIntegral = new TGTransientFrame (gClient->GetRoot(), this,200 , 60);
  sliderLine = new TGHSlider(tfIntegral);
  //TGLayoutHints *btLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
  TGLayoutHints *elementsHints =  new TGLayoutHints(kLHintsExpandY | kLHintsExpandX | kLHintsCenterX,2,2,2,2);
  
  tfIntegral->AddFrame(sliderLine,elementsHints);
  
  tfIntegral->MapSubwindows();
  tfIntegral->Resize(); 
}

const char *filetypes[] = {"File dat",    "*.[dD][aA][tT]",
			   "File nfo",    "*.[nN][fF][oO]",
			   0,               0 };

void Visual::OpenFile(){
  //  static TString dir(".");
  static TString dir("./Experiment/definitive/grandemassa/results/");//temporaneo
  TGFileInfo fi;
  fi.fFileTypes = filetypes;
  fi.fIniDir    = StrDup(dir);
  new TGFileDialog(gClient->GetRoot(), this, kFDOpen, &fi);
  if(fi.fFilename == 0)
    cout << "File non aperto" << endl;
  else{
    cout << "Apro il file: " << fi.fFilename  <<endl;
    //<<"(dir: "<<fi.fIniDir<<")\n";
    loadFile(fi.fFilename);
  }
  // printf("Open file: %s (dir: %s)\n", fi.fFilename, fi.fIniDir);
  dir = fi.fIniDir;
}

const char *savefiletypes[] = {"PNG",    "*.png",
			       "PDF",    "*.pdf",
			       0,               0 };

void Visual::doData(){
  //  static TString dir(".");
  ready(false);
  static TString mdir("./TesinaPDF/IMG/");//temporaneo
  TGFileInfo fi;
  fi.fFileTypes = savefiletypes;
  fi.fIniDir    = StrDup(mdir);
  new TGFileDialog(gClient->GetRoot(), this, kFDSave, &fi);
  if(fi.fFilename == 0)
    cout << "File non aperto" << endl;
  else{
    string fname = fi.fFilename;
    bool pdf=false;
    if(fname.rfind(".pdf")!=string::npos){
      pdf=true;
      fname = fname.substr(0,fname.size()-4);
    }else if(fname.rfind(".png")!=string::npos){
      pdf=false;
      fname = fname.substr(0,fname.size()-4);
    }
    ofstream datafile(fname+"_data.nfo");
    int step = Nt/10;
    for(int i=0;i<=10;i++){
      int T = step*i;
      if(T>Nt)
	T=Nt;
      sliderT->SetPosition(T);
      SetObs(T);
      DoFit();
      char f[256];
      if(pdf)
	sprintf(f,"%s_%g.pdf",fname.c_str(),T*tstep);
      else
	sprintf(f,"%s_%g.png",fname.c_str(),T*tstep);
      showCanvas->SaveAs(f);
      datafile << T*tstep <<"\t";
      datafile << myNorm <<"\t" << myMid<<"\t" << mySigma << endl;
    }
  }
  // printf("Open file: %s (dir: %s)\n", fi.fFilename, fi.fIniDir);
  mdir = fi.fIniDir;
  ready(true);
}

void Visual::doSequence(){
  //  static TString dir(".");
  ready(false);
  static TString mdir("./TesinaPDF/IMG/");//temporaneo
  TGFileInfo fi;
  fi.fFileTypes = savefiletypes;
  fi.fIniDir    = StrDup(mdir);
  new TGFileDialog(gClient->GetRoot(), this, kFDSave, &fi);
  if(fi.fFilename == 0)
    cout << "File non aperto" << endl;
  else{
    string fname = fi.fFilename;
    bool pdf=false;
    if(fname.rfind(".pdf")!=string::npos){
      pdf=true;
      fname = fname.substr(0,fname.size()-4);
    }else if(fname.rfind(".png")!=string::npos){
      pdf=false;
      fname = fname.substr(0,fname.size()-4);
    }
    TGraph *TObs;
    TMultiGraph *TVisual = new TMultiGraph("Sequenza",""/* ("Sequenza per "+fname).c_str()*/);
    int C[10]={1,2,3,4,5,6,7,8,9,11};
    int step = Nt/10;
    for(int i=0;i<=10;i++){
      int T = step*i;
      if(T>Nt)
	T=Nt;
      TObs = new TGraph(Nl);
      for(int j=0;j<Nl;j++){
	double z = abs(Z.at(j+T*Nl));
	TObs->SetPoint(j,j*sstep,z);
      }
      TObs->SetLineColor(C[i]);
      //TObs->SetMarkerColor(C[i]);
      TVisual->Add(TObs);
    }

    showCanvas->cd();
    TVisual->Draw("al");
    gStyle->SetOptFit(false);
    showCanvas->Modified();
    showCanvas->Update();
    
    char f[256];
    if(pdf)
      sprintf(f,"%s.pdf",fname.c_str());
    else
      sprintf(f,"%s.png",fname.c_str());
    showCanvas->SaveAs(f);
    showCanvas->cd();
    myVisual->Draw("apl");
    //    TVisual->Clear();
    delete TVisual;
    showCanvas->Modified();
    showCanvas->Update();
    // printf("Open file: %s (dir: %s)\n", fi.fFilename, fi.fIniDir);
  }
  mdir = fi.fIniDir;
  ready(true);
}


void Visual::doDataNoImg(){
  //  static TString dir(".");
  ready(false);
  static TString mdir("./TesinaPDF/IMG/");//temporaneo
  TGFileInfo fi;
  fi.fFileTypes = savefiletypes;
  fi.fIniDir    = StrDup(mdir);
  new TGFileDialog(gClient->GetRoot(), this, kFDSave, &fi);
  if(fi.fFilename == 0)
    cout << "File non aperto" << endl;
  else{
    string fname = fi.fFilename;
    if(fname.rfind(".pdf")!=string::npos){
      fname = fname.substr(0,fname.size()-4);
    }else if(fname.rfind(".png")!=string::npos){
      fname = fname.substr(0,fname.size()-4);
    }
    ofstream datafile(fname+"_data.nfo");
    int step = Nt/20;
    for(int i=0;i<=20;i++){
      int T = step*i;
      if(T>Nt)
	T=Nt;
      sliderT->SetPosition(T);
      SetObs(T);
      DoFit();
      datafile << T*tstep <<"\t";
      datafile << myNorm <<"\t" << myMid<<"\t" << mySigma << endl;
    }
  }
  // printf("Open file: %s (dir: %s)\n", fi.fFilename, fi.fIniDir);
  mdir = fi.fIniDir;
  ready(true);
}


void Visual::SaveFile(){
  //  static TString dir(".");
  ready(false);
  static TString sdir("./TesinaPDF/IMG/");//temporaneo
  TGFileInfo fi;
  fi.fFileTypes = savefiletypes;
  fi.fIniDir    = StrDup(sdir);
  new TGFileDialog(gClient->GetRoot(), this, kFDSave, &fi);
  if(fi.fFilename == 0)
    cout << "File non aperto" << endl;
  else{
    cout << "Salvo l file il file: "<< fi.fFilename  <<endl;//<<"(dir: "<<fi.fIniDir<<")\n";
    showCanvas->SaveAs(fi.fFilename);
  }
  // printf("Open file: %s (dir: %s)\n", fi.fFilename, fi.fIniDir);
  sdir = fi.fIniDir;
  ready(true);
}


const char *filetypespot[] = {"File set",    "*.set",
			      0,               0 };
void Visual::ShowPot(){
  //  static TString dir(".");
  static TString dirp("./Experiment/definitive/grandemassa");//temporaneo
  TGFileInfo fi;
  fi.fFileTypes = filetypespot;
  fi.fIniDir    = StrDup(dirp);
  new TGFileDialog(gClient->GetRoot(), this, kFDOpen, &fi);
  if(fi.fFilename == 0)
    cout << "File non aperto" << endl;
  else{
    cout << "Apro il file: "<< fi.fFilename  <<endl;//<<"(dir: "<<fi.fIniDir<<")\n";
    loadPot(fi.fFilename);
  }
  // printf("Open file: %s (dir: %s)\n", fi.fFilename, fi.fIniDir);
  dirp = fi.fIniDir;
}

const char *dogif[] = {"gif",    "*.gif",
		       0,               0 };
void Visual::makeGif(){
  //  static TString dir(".");
  ready(false);
  static TString mdir("./TesinaPDF/IMG/");//temporaneo
  TGFileInfo fi;
  fi.fFileTypes = dogif;
  fi.fIniDir    = StrDup(mdir);
  new TGFileDialog(gClient->GetRoot(), this, kFDSave, &fi);
  if(fi.fFilename == 0)
    cout << "File non aperto" << endl;
  else{
    string fname = fi.fFilename;
    if(fname.rfind(".gif")!=string::npos)
      fname = fname.substr(0,fname.size()-4);
    sliderT->SetPosition(0);
    SetObs(0);
    char f[256];
    sprintf(f,"%s.gif",fname.c_str());
    showCanvas->SaveAs(f);
    for(int i=1;i<Nt;i++){
      sliderT->SetPosition(i);
      SetObs(i);
      if(i<Nt-1)
	sprintf(f,"%s.gif+10",fname.c_str());
      else
	sprintf(f,"%s.gif++100++",fname.c_str());
      showCanvas->SaveAs(f);
    }
  }
  // printf("Open file: %s (dir: %s)\n", fi.fFilename, fi.fIniDir);
  mdir = fi.fIniDir;
  ready(true);
}
//funzioni
void Visual::loadFile(string dat){
  /*
  //preparo i dati dall'nfo
  string nfo = dat;
  nfo.resize(nfo.size()-3);
  nfo+="nfo";*
  */
  ready(false);
  Re=Im=false;
  ifstream f(dat);
  int sskip, tskip;
  double atstep;
  f >> sskip >> Nl >> sstep >> tskip >> atstep;
  f >> tstep;//tstep tra le righe
  Nl/=sskip;
  sstep*=sskip;
  Z.clear();
  cout << "Carico l'onda" << endl;
  gStyle->SetOptFit(false);
  for(int j=0;f.good();j++){
    for(int i=0;i<Nl&&f.good();i++){
      Var z;
      f >> z;
      if(f.good()){
	Z.push_back(z);
      }
    }
  }

  f.close();

  Nt = Z.size()/Nl;
  cout  << "Punti caricati: " << Z.size() << ", per un totale di "<< Nt
	<< " passi temporali da " << Nl << " passi spaziali"<<endl;
  cout << "NB: sono comprese le CI in questo conto\n";
  //setto i grafici
  if(myVisual!=nullptr){
    myObs -> Clear();
    myCI  -> Clear();
    if(myRe!=nullptr)
      myRe -> Clear();
    if(myIm!=nullptr)
      myIm -> Clear();
    if(myPot!=nullptr)
      myPot -> Clear();
    delete myVisual;
    myObs = nullptr;
    myCI = nullptr;
    myRe = nullptr;
    myIm = nullptr;
    myPot = nullptr;
  }
  myVisual = new TMultiGraph("mG","");
  sliderT->SetRange(1,Nt-1);
  sliderT->SetPosition(1);
  sliderZoom->SetRange(0,sstep*Nl);
  sliderZoom->SetPosition(0,sstep*Nl);
  ready(true);
    
  SetCI();
  SetObs(1);
}

void Visual::SetObs(int T){
  gStyle->SetOptFit(false);
  double thismax = -9999999;
  if(myObs==nullptr){
    myObs = new TGraph(Nl);
    myVisual->Add(myObs);    
  }
  if(cbRe->IsOn()){
    if(myRe==nullptr){
      myRe = new TGraph(Nl);
      myRe->SetLineColor(2);
      myRe->SetMarkerColor(2);
    }
    if(!Re){
      myVisual->Add(myRe);
      Re = true;
    }
  }else if(Re){
    Re = false;
    myVisual->GetListOfGraphs()->Remove(myRe);
  }
  if(cbIm->IsOn()){
    if(myIm==nullptr){
      myIm = new TGraph(Nl);
      myIm->SetLineColor(4);
      myIm->SetMarkerColor(4);
    }
    if(!Im){
      myVisual->Add(myIm);
      Im = true;
    }
  }else if(Im){
    Im = false;
    myVisual->RecursiveRemove(myIm);
  }
  for(int i=0;i<Nl;i++){
    Var z = Z.at(i+T*Nl);
    double zabs = abs(z);
    myObs->SetPoint(i,i*sstep,zabs);
    if(Re){
      myRe->SetPoint(i,i*sstep,z.real());
    }
    if(Im){
      myIm->SetPoint(i,i*sstep,z.imag());
    }
    if(zabs>thismax){
      thismax=zabs;
      maxpos = i*sstep;
    }
  }
  double t = T*tstep;
  char num[50];
  sprintf(num,"%g",t);
  lbTime->SetText(num);
  showCanvas->cd();
  myVisual->Draw("apl");
  showCanvas->Modified();
  showCanvas->Update();
}

void Visual::SetCI(){
  if(myCI==nullptr){
    myCI = new TGraph(Nl);
    myVisual->Add(myCI);    
  }else{
    myCI->Clear();
    myCI->Set(Nl);
  }
  
  for(int i=0;i<Nl;i++)
    myCI->SetPoint(i,i*sstep,abs(Z.at(i)));
  myCI->SetLineColor(3);
  myCI->SetMarkerColor(3);
}

void Visual::DoFit(){

  TF1 myFit("doFit","gaus(0)",sliderZoom->GetMinPosition(),
	    sliderZoom->GetMaxPosition());
  //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0.
  myFit.SetParNames("#alpha","#bar{x}","#sigma");
  myFit.SetParameters(1,maxpos,1);

  myObs->Fit(&myFit,"QR");

  myNorm  = myFit.GetParameter(0);
  myMid   = myFit.GetParameter(1);
  mySigma = myFit.GetParameter(2);

  gStyle->SetOptFit(true);
  showCanvas->Modified();
  showCanvas->Update();
}

		     
void Visual::loadPot(string dat){
  ready(false);
  cout << "Carico il potenziale" << endl;  
  ifstream f(dat);
  string dummy;
  char type;
  double Vpos, Vpar, Vval;
  f >> dummy >> type;
  f >> dummy >> Vval;
  f >> Vpos >> Vpar;
  f.close();
  pot = nullptr;
  switch(type){//gli switch non mi piacciono, ma non fanno dimenticare gli else
  case 'b':
  case 'B':
    pot = &bump;
    break;
  case 'g':
  case 'G':
    pot = &gauss;
    break;
  case 'm':
  case 'M':
    //converto centro+larghezza in salita+discesa
    Vpos -= Vpar/2.;
    Vpar += Vpos;
    pot = &barrier;
    break;
  default:
    pot = &H;
  }
  if(myPot==nullptr){
    myPot = new TGraph(Nl);
    myVisual->Add(myPot);    
  }else{
    myPot->Clear();
    myPot->Set(Nl);
  }
  for(int i=0;i<Nl;i++)
    myPot->SetPoint(i,i*sstep,pot(i*sstep,Vpos,Vpar));
  myPot->SetLineColor(7);
  myPot->SetMarkerColor(7);
  
  myVisual->Draw("apl");
  showCanvas->Modified();
  showCanvas->Update();
  
  ready(true);
}

void Visual::doZoom(){
  if(myVisual!=nullptr){
    //myVisual->GetXaxis()->SetLimits(sliderZoom->GetMinPosition(),
    myVisual->GetXaxis()->SetRangeUser(sliderZoom->GetMinPosition(),
				       sliderZoom->GetMaxPosition());
    
    showCanvas->Modified();
    showCanvas->Update();
  }
}
