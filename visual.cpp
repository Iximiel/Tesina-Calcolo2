#include "visual.hpp"

#include <TGLabel.h>
#include <TRootEmbeddedCanvas.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TGFileDialog.h>
#include <TF1.h>

#include <complex>
#include <fstream>
#include <iostream>
using namespace std;

typedef complex<double> Var;

Visual::Visual(const TGWindow *p,int w,int h)
  :TGMainFrame(p,w,h,kMainFrame | kVerticalFrame){
  SetWindowName("Visualizzatore risoluzione equazione di Schrodinger");
  Connect("CloseWindow()","Visual",this,"exit()");//con questo schiacciando la x chiudo il programma e non solo la finestra
  DontCallClose();

  AddFrame(setCanvas(this), new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX|kLHintsExpandY,2,2,2,2));
  AddFrame(setButtons(this), new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX/*|kLHintsExpandY*/,2,2,2,2));

  myCI = nullptr;
  myObs = nullptr;
  myVisual = nullptr; 
 
  SetMWMHints(kMWMDecorAll,
	      kMWMFuncAll,
	      kMWMInputModeless);

  
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
  TGHorizontalFrame *tHMainFrame =  new TGHorizontalFrame(p);
  TGVerticalFrame *tVBtFrame =  new TGVerticalFrame(tHMainFrame);

  //hints per le labels:
  TGLayoutHints *btLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
  TGLayoutHints *elementsHints =  new TGLayoutHints(kLHintsExpandY | kLHintsExpandX | kLHintsCenterX,2,2,2,2);
  
  tHMainFrame->AddFrame(new TGTextButton(tHMainFrame, ""),btLayout);//estetica
  
  tbDoThing = new TGTextButton(tVBtFrame, "Salva Dati");
  tbDoNoImg = new TGTextButton(tVBtFrame, "Salva Dati\nsenza Img");
  tVBtFrame->AddFrame(tbDoThing,btLayout);
  tVBtFrame->AddFrame(tbDoNoImg,btLayout);
  tHMainFrame->AddFrame(tVBtFrame,btLayout);
  tVBtFrame =  new TGVerticalFrame(tHMainFrame);
  tbOpen = new TGTextButton(tVBtFrame, "Apri un file");
  tbSave = new TGTextButton(tVBtFrame,"Salva la Canvas");
  tVBtFrame->AddFrame(tbOpen,btLayout);
  tVBtFrame->AddFrame(tbSave,btLayout);
  tHMainFrame->AddFrame(tVBtFrame,btLayout);
  sliderT = new TGHSlider(tHMainFrame);
  tHMainFrame->AddFrame(sliderT,elementsHints);
  lbTime = new TGLabel(tHMainFrame,"tempo");
  lbTime->SetWidth(30);
  tHMainFrame->AddFrame(lbTime,btLayout);
  tbFit = new TGTextButton(tHMainFrame, "Fitta la\nGaussiana");
  tHMainFrame->AddFrame(tbFit,btLayout);
  tbEaster = new TGTextButton(tHMainFrame, "");
  tHMainFrame->AddFrame(tbEaster,btLayout);
  
  tbOpen    -> Connect("Clicked()","Visual",this,"OpenFile()");
  tbSave    -> Connect("Clicked()","Visual",this,"SaveFile()");
  tbDoThing -> Connect("Clicked()","Visual",this,"doData()");
  tbDoNoImg -> Connect("Clicked()","Visual",this,"doDataNoImg()");
  tbFit     -> Connect("Clicked()","Visual",this,"DoFit()");
  tbEaster  -> Connect("Clicked()","Visual",this,"makeGif()");
  
  sliderT -> Connect("PositionChanged (Int_t)","Visual",this,"SetObs(int)");

  ready(false);
  
  sliderT->SetPosition(1);
  return tHMainFrame;
}

void Visual::ready(bool bt){
  sliderT->SetEnabled(bt);
  tbFit->SetEnabled(bt);
  tbEaster->SetEnabled(bt);
  tbDoThing->SetEnabled(bt);
  tbDoNoImg->SetEnabled(bt);
  tbSave->SetEnabled(bt);
}

//slots

void Visual::exit(){
  gApplication->Terminate(0);
}

const char *filetypes[] = {"File dat",    "*.[dD][aA][tT]",
			   "File nfo",    "*.[nN][fF][oO]",
			   0,               0 };

void Visual::OpenFile(){
  //  static TString dir(".");
  static TString dir("./Experiment/definitive/results/");//temporaneo
  TGFileInfo fi;
  fi.fFileTypes = filetypes;
  fi.fIniDir    = StrDup(dir);
  new TGFileDialog(gClient->GetRoot(), this, kFDOpen, &fi);
  if(fi.fFilename == 0)
    cout << "File non aperto" << endl;
  else{
    cout << "Apro il file: "<< fi.fFilename  <<endl;//<<"(dir: "<<fi.fIniDir<<")\n";
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
}

void Visual::doDataNoImg(){
  //  static TString dir(".");
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
}


void Visual::SaveFile(){
  //  static TString dir(".");
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
}

const char *dogif[] = {"gif",    "*.gif",
		       0,               0 };
void Visual::makeGif(){
  //  static TString dir(".");
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
}
//funzioni

void Visual::loadFile(string dat){
  /*
  //preparo i dati dall'nfo
  string nfo = dat;
  nfo.resize(nfo.size()-3);
  nfo+="nfo";*
  //cout <<   nfo <<endl << dat<<endl;
  */
  ready(false);
  
  ifstream f(dat);
  int sskip, tskip;
  double atstep;
  f >> sskip >> Nl >> sstep >> tskip >> atstep;
  f >> tstep;//tstep tra le righe
  sstep*=sskip;
  Z.clear();
  cout << "Carico l'onda" << endl;
  gStyle->SetOptFit(false);
  for(int j=0;f.good();j++){
    for(int i=0;i<Nl&&f.good();i++){
      Var z;
      f >> z;
      if(f.good()){
	Z.push_back(abs(z));
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
    delete myVisual;
    myObs = nullptr;
    myCI = nullptr;
  }
  myVisual = new TMultiGraph("mG","");
  sliderT->SetRange(1,Nt-1);
  sliderT->SetPosition(1);
  
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
      
  for(int i=0;i<Nl;i++){
    double z = Z.at(i+T*Nl);
    myObs->SetPoint(i,i*sstep,z);
    if(z>thismax){
      thismax=z;
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
  }
      
  for(int i=0;i<Nl;i++)
    myCI->SetPoint(i,i*sstep,Z.at(i));
  myCI->SetLineColor(3);
  myCI->SetMarkerColor(3);
}

void Visual::DoFit(){

  TF1 myFit("doFit","gaus(0)",0,sstep*Nl);
  //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0.
  myFit.SetParNames("#alpha","#bar{x}","#sigma");
  myFit.SetParameters(1,maxpos,1);

  myObs->Fit(&myFit,"Q");

  myNorm  = myFit.GetParameter(0);
  myMid   = myFit.GetParameter(1);
  mySigma = myFit.GetParameter(2);

  gStyle->SetOptFit(true);
  showCanvas->Modified();
  showCanvas->Update();
}

		     
