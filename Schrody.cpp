#include "Schrody.hpp"
#include "TGLabel.h"
#include "TRootEmbeddedCanvas.h"
#include "TCanvas.h"
#include "TApplication.h"


#define USECOMPLEX//cosi` includo complex e la variabile Var e` un "Complex<double>" -std=c++11 e` raccomandato
#include "CrankSolver.hpp"

#include <iostream>
using namespace std;


Schrody::Schrody(const TGWindow *p,int w,int h)
  :TGMainFrame(p,w,h,kMainFrame | kHorizontalFrame){
  SetName("Risoluzione equazione di Schrodinger");
  info = new guiInfo();
  CC = false;
  Connect("CloseWindow()","Schrody",this,"exit()");//con questo schiacciando la x chiudo il programma e non solo la finestra
  DontCallClose();
  AddFrame(setConditions(this), new TGLayoutHints(kLHintsLeft | kLHintsTop|/*kLHintsExpandX|*/kLHintsExpandY,2,2,2,2));
  TGVerticalFrame *tVMainFrame =  new TGVerticalFrame(this);
  AddFrame(tVMainFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX|kLHintsExpandY,2,2,2,2));
  tVMainFrame->AddFrame(setCanvas(tVMainFrame), new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX|kLHintsExpandY,2,2,2,2));
  tVMainFrame->AddFrame(setAlgorithm(tVMainFrame), new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX/*|kLHintsExpandY*/,2,2,2,2));

  SetMWMHints(kMWMDecorAll,
	      kMWMFuncAll,
	      kMWMInputModeless);

  //connessione controllo passi valori
  numSpaceLim -> Connect("ValueSet(Long_t)","Schrody",this,"HandleNumbers()");
  numTimeLim -> Connect("ValueSet(Long_t)","Schrody",this,"HandleNumbers()");
  numSpaceStep -> Connect("ValueSet(Long_t)","Schrody",this,"HandleNumbers()");
  numTimeStep -> Connect("ValueSet(Long_t)","Schrody",this,"HandleNumbers()");
  numSpaceSteps -> Connect("ValueSet(Long_t)","Schrody",this,"HandleNumbers()");
  numTimeSteps -> Connect("ValueSet(Long_t)","Schrody",this,"HandleNumbers()");
  bgSetSteps -> Connect("Clicked(Int_t)","Schrody",this,"HandleNumbers()");
  tbStart -> Connect("Clicked()","Schrody",this,"doTheThing()");

  HandleNumbers();
  Potenziale = nullptr;
  PreviewPotenziale();
  
  MapSubwindows();    
  Resize(GetDefaultSize());
  MapWindow();
  Resize(800,600);
}

TGFrame* Schrody::setConditions(const TGWindow *p){
  TGVerticalFrame *tVMainFrame =  new TGVerticalFrame(p);
  //  TGButtonGroup  GroupMetodo = new TGButtonGroup(tHMainFrame,"Metodo");
  //dichiaro due dummy per comodita`
  TGHorizontalFrame *tHFrame; 
  TGLabel *tLabel;
  //hints per le labels:
  TGLayoutHints *LabelLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
  //hits per le frame
  TGLayoutHints *frameHints = new TGLayoutHints(kLHintsExpandX | kLHintsTop,2,2,2,2);
  //Impostazioni potenziale (magari aggiorno realtime la canvas)

  tVMainFrame->AddFrame(tHFrame = new TGHorizontalFrame(tVMainFrame),frameHints);
  tHFrame->AddFrame(tbStart  =  new TGTextButton(tVMainFrame,"Avvia"),
		    new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,2,2,2,2));
  tbStart->SetEnabled(false);
  tHFrame->Resize(200,200);
  
  TGGroupFrame *gfPotenziale = new TGGroupFrame(tVMainFrame,"Potenziale");
  //forma potenziale
  gfPotenziale->AddFrame(comboPotentials = new TGComboBox (gfPotenziale),
			 new TGLayoutHints(kLHintsLeft | kLHintsTop,5,5,5,5));
  //			 new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX/*|kLHintsExpandY*/,2,2,2,2));//da aggiustare
  //roba moooolto temporanea
  comboPotentials->NewEntry("[0]+x*[1]");
  comboPotentials->NewEntry("[0]*H(x-[1])");
  comboPotentials->NewEntry("[0]*H(x-[1])*H([2]-x)");
  comboPotentials->NewEntry("gauss(x,[0],[1])");
  comboPotentials->Select(3,false);
  comboPotentials->Resize(150,20);
  //parametri
  numpar = new TGNumberEntry*[2];
  gfPotenziale->AddFrame(tHFrame = new TGHorizontalFrame(gfPotenziale));
  tHFrame->AddFrame(numpar[0] = new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"[0]"),LabelLayout);
  //Distanza Piastre
  gfPotenziale->AddFrame(tHFrame = new TGHorizontalFrame(gfPotenziale));
  tHFrame->AddFrame(numpar[1] = new TGNumberEntry (tHFrame,0.5,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"[1]"),LabelLayout);
  
  //Impostazioni pacchetto d'onda (magari aggiorno realtime la canvas)
  TGGroupFrame *gfPacchetto = new TGGroupFrame(tVMainFrame,"Pacchetto Iniziale");
  //Altezza
  gfPacchetto->AddFrame(tHFrame = new TGHorizontalFrame(gfPacchetto));
  tHFrame->AddFrame(numNorm = new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  numNorm->GetNumberEntry()->SetToolTipText("\"Norma\" moltiplica la gaussiana, che e` gia` normalizzata, se messo  a 0 fa si` che l'altezza massiam sia 1");
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"\"Norma\""),LabelLayout);
  //larghezza
  gfPacchetto->AddFrame(tHFrame = new TGHorizontalFrame(gfPacchetto));
  tHFrame->AddFrame(numLarg = new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Larghezza"),LabelLayout);
  //energia
  gfPacchetto->AddFrame(tHFrame = new TGHorizontalFrame(gfPacchetto));
  tHFrame->AddFrame(numEne = new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Energia"),LabelLayout);
  //massa
  gfPacchetto->AddFrame(tHFrame = new TGHorizontalFrame(gfPacchetto));
  tHFrame->AddFrame(numMass = new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Massa"),LabelLayout);
  //condizioni al contorno
  TGButtonGroup *bgCC = new TGButtonGroup(tVMainFrame,"Condizioni al contorno");//decidere se buttogroup o groupframe
  TGTextButton *CCin = new TGTextButton(bgCC,"In 0");
  TGTextButton *CCfin = new TGTextButton(bgCC,"In N");
  CCin->Connect("Clicked()","Schrody",this,"launchCC0()");
  CCfin->Connect("Clicked()","Schrody",this,"launchCCN()");
  
  bgCC->SetLayoutHints(frameHints);
  
  tVMainFrame -> AddFrame(gfPotenziale, frameHints);
  tVMainFrame -> AddFrame(gfPacchetto, frameHints);
  tVMainFrame -> AddFrame(bgCC, frameHints);
  return tVMainFrame;
}

TGFrame * Schrody::setCanvas(const TGWindow *p){
  TRootEmbeddedCanvas* ECanvas = new TRootEmbeddedCanvas(0,p,456,192);
  ECanvas->SetName("Canvas");
  int CanvasID = ECanvas->GetCanvasWindowId();
  TCanvas *childCanvas = new TCanvas("childCanvas", 10, 10, CanvasID);
  ECanvas->AdoptCanvas(childCanvas);
  return ECanvas;
}
TGFrame *Schrody::setAlgorithm(const TGWindow *p){
  TGHorizontalFrame *tHMainFrame =  new TGHorizontalFrame(p);
  //dichiaro due dummy per comodita`
  TGHorizontalFrame *tHFrame; 
  TGLabel *tLabel;
  //hints per le labels:
  TGLayoutHints *LabelLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
  TGLayoutHints *elementsHints =  new TGLayoutHints(kLHintsExpandY | kLHintsCenterX,2,2,2,2);
  //Limiti superiori
  TGGroupFrame *gfLimits = new TGGroupFrame(tHMainFrame,"Limiti Superiori");
  //Spazio
  gfLimits->AddFrame(tHFrame = new TGHorizontalFrame(gfLimits));
  tHFrame->AddFrame(numSpaceLim = new TGNumberEntry (tHFrame,10,5,-1,TGNumberFormat::kNESRealOne, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,40));//40 come max e` troppo per la mia macchina, ma puo` andare su un mezzo un po' piu` potente
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Spazio"),LabelLayout);
  //Tempo
  gfLimits->AddFrame(tHFrame = new TGHorizontalFrame(gfLimits));
  tHFrame->AddFrame(numTimeLim = new TGNumberEntry (tHFrame,3.5,5,-1,TGNumberFormat::kNESRealOne, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,40));//40 come max e` troppo per la mia macchina
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Tempo"),LabelLayout);
  //scelta su come calcolare i passi
  bgSetSteps = new TGButtonGroup(tHMainFrame,"Calcolo passi");//,kVerticalFrame);//,uGC->GetGC());
  TGRadioButton **StepMethods = new TGRadioButton*[2];
  StepMethods[0] = new TGRadioButton(bgSetSteps,"Da passo a N",100);
  StepMethods[1] = new TGRadioButton(bgSetSteps,"Da N a Passo",101);

  StepMethods[0]->SetState(kButtonDown);

  //quantifico i Passi
  TGGroupFrame *gfStep = new TGGroupFrame(tHMainFrame,"Impostazioni Passi");
  gfStep->AddFrame(tHFrame = new TGHorizontalFrame(gfStep));
  //passi
  tHFrame->AddFrame(numSpaceStep = new TGNumberEntry (tHFrame,0.0001,5,-1,TGNumberFormat::kNESRealFour, TGNumberFormat::kNEAPositive, TGNumberFormat::kNELLimitMinMax, 0,1));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"#delta S"),LabelLayout);
  gfStep->AddFrame(tHFrame = new TGHorizontalFrame(gfStep));
  tHFrame->AddFrame(numTimeStep = new TGNumberEntry (tHFrame,0.0001,5,-1,TGNumberFormat::kNESRealFour, TGNumberFormat::kNEAPositive, TGNumberFormat::kNELLimitMinMax, 0.000000,1));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"#delta T"),LabelLayout);
  //numero
  TGGroupFrame *gfSteps = new TGGroupFrame(tHMainFrame,"Numero Passi");
  gfSteps->AddFrame(tHFrame = new TGHorizontalFrame(gfSteps));
  tHFrame->AddFrame(numSpaceSteps = new TGNumberEntry (tHFrame,1,5,-1,TGNumberFormat::kNESInteger, TGNumberFormat::kNEAPositive, TGNumberFormat::kNELLimitMin, 0));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Passi S"),LabelLayout);
  gfSteps->AddFrame(tHFrame = new TGHorizontalFrame(gfSteps));
  tHFrame->AddFrame(numTimeSteps = new TGNumberEntry (tHFrame,1,5,-1,TGNumberFormat::kNESInteger, TGNumberFormat::kNEAPositive, TGNumberFormat::kNELLimitMin, 0));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Passi T"),LabelLayout);

  tHMainFrame -> AddFrame(gfLimits, elementsHints);
  tHMainFrame -> AddFrame(bgSetSteps, elementsHints);
  tHMainFrame -> AddFrame(gfStep, elementsHints);
  tHMainFrame -> AddFrame(gfSteps, elementsHints);
  return tHMainFrame;
}

//slots
void Schrody::exit(){
  gApplication->Terminate(0);
}

void Schrody::launchCC0(){
  DefineCC *CC0 = new DefineCC(this, "Condizioni in 0", info, true);
  CC0->Connect("CCsets(bool)","Schrody",this,"CCset(bool)");
}

void Schrody::launchCCN(){
  DefineCC *CCN = new DefineCC(this, "Condizioni in N", info, false);
  CCN->Connect("CCsets(bool)","Schrody",this,"CCset(bool)");
}

void Schrody::CCset(bool CCok){
  //impostare la possibilita` di partire
  cout << CCok<<endl;
  CC = CCok;
  controlReady();
}
void Schrody::controlReady(){
  if(CC)
    tbStart->SetEnabled(true);
}
#include <iostream>
void Schrody::HandleNumbers(){
  //NB: al momento di calcolare l'algoritmo il passo verra` calcolato con la precisione dovuta, le entries servono solo come anteptrime
  //potrei essere piu` fine nell'attivare/disattivare le enrty, ma non affligge la performance della simulazione
  std::cout << "HandleNumbers" <<"\n";
  if(bgSetSteps->GetButton(100)->IsOn()){
    double Sstep = numSpaceStep -> GetNumber();
    double Tstep = numTimeStep -> GetNumber();
    double Slim = numSpaceLim -> GetNumber();
    double Tlim = numTimeLim -> GetNumber();
    int NS = Slim/Sstep;
    int NT = Tlim/Tstep;
    numSpaceSteps -> SetIntNumber(NS);
    numTimeSteps -> SetIntNumber(NT);
    //imposta/conferma gli stati
    numSpaceStep -> SetState(true);
    numTimeStep -> SetState(true);    
    numSpaceSteps -> SetState(false);
    numTimeSteps -> SetState(false);
  }else{
    int NS = numSpaceSteps -> GetIntNumber();
    int NT = numTimeSteps -> GetIntNumber();
    double Slim = numSpaceLim -> GetNumber();
    double Tlim = numTimeLim -> GetNumber();
    double Sstep = Slim/NS;
    double Tstep = Tlim/NT;
    numSpaceStep -> SetNumber(Sstep);
    numTimeStep -> SetNumber(Tstep);
    //imposta/conferma gli stati
    numSpaceSteps -> SetState(true);
    numTimeSteps -> SetState(true);
    numSpaceStep -> SetState(false);
    numTimeStep -> SetState(false);
  }
}
void Schrody::SetPotenziale(){
}
void Schrody::PreviewPotenziale(){
  SetPotenziale();
}

void Schrody::doTheThing(){
  double Sstep, Tstep, Slim, Tlim;
  int NS, NT;
  static const Var I(0,1);// mi serve solo qui
  static const char lazyCC[3] = {'D','N','R'};
  double hbar = 1, mass = 1;// valori temporanei
  char infoCC[2] = {lazyCC[info->CC0],lazyCC[info->CCN]};
  //per prima cosa imposto i passi
  if(bgSetSteps->GetButton(100)->IsOn()){
    Sstep = numSpaceStep -> GetNumber();
    Tstep = numTimeStep -> GetNumber();
    Slim = numSpaceLim -> GetNumber();
    Tlim = numTimeLim -> GetNumber();
    NS = Slim/Sstep;
    NT = Tlim/Tstep;
  }else{
    NS = numSpaceSteps -> GetIntNumber();
    NT = numTimeSteps -> GetIntNumber();
    Slim = numSpaceLim -> GetNumber();
    Tlim = numTimeLim -> GetNumber();
    Sstep = Slim/NS;
    Tstep = Tlim/NT;
  }
  //definisco il potenziale
  //quindi imposto le condizioni iniziali
  // e imposto la trimatrice
  tridiagM mat(NS);
  Var eta = I * (hbar/(2*mass))*(Tstep/(Sstep*Sstep));
  Var *initial = new Var[NS];
  //imposto gli a d c generici
  Var a = -1., d = 2./eta+2., c = -1.;
  Var ak = 1., dk = 2./eta-2., ck = 1.;
  //  initial[0] = info.gauss(0);
  if(infoCC[0]=='D'){
  }else if(infoCC[0]=='N'){ 
  }else{//Robin
    mat.setUnknown(0,0,d+2.*a*Sstep*info->weight0 + 0.,a+c,0);
    mat.setKnown(0,0,dk+2.*ak*Sstep*info->weight0 + 0.,ak+ck,0);
  }
  for(int j = 1;j < NS-1;j++){
    /*    if(j==info.Vnum){
      d -= -I*info.Vval * timestep/eta;
      dk+= -I*info.Vval * timestep/eta;
    }*/

    /* if(j==3*info.Nl/4){
      d = 2./(eta*5)+2;
      dk = 2./(eta*5)-2;
      }*/
    //    initial[j] = info.gauss(j);//+j*5./info.Nl;
    mat.setUnknown(j,a,d,c,0);
    mat.setKnown(j,ak,dk,ck,0);
  }
  // int set =3*info.Nl/4;
  //  mat.setKnown(set,ak,dk,ck,0.1);
  //  initial[NS-1] = info.gauss(NS-1);
  mat.setUnknown(NS-1,a+c,d,0.,0.);
  mat.setKnown(NS-1,ak+ck,dk,0.,0.);

  //do in pasto le impostazioni al solver
  //CrankSolver
  //lancio una finestra con una progressbar e faccio le cose
  //salvo tutto su un file, poi creo un visualize piu` comodo
}

