#include "Schrody.hpp"

Schrody::Schrody(const TGWindow *p,int w,int h)
  :TGMainFrame(p,w,h,kMainFrame | kHorizontalFrame){
  SetName("Risoluzione equazione di Schrodinger");

  info = new guiInfo();
  CC = false;
  
  AddFrame(setConditions(this), new TGLayoutHints(kLHintsLeft | kLHintsTop|/*kLHintsExpandX|*/kLHintsExpandY,2,2,2,2));
  TGVerticalFrame *tVMainFrame =  new TGVerticalFrame(this);
  AddFrame(tVMainFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX|kLHintsExpandY,2,2,2,2));
  tVMainFrame->AddFrame(setCanvas(tVMainFrame), new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX|kLHintsExpandY,2,2,2,2));
  tVMainFrame->AddFrame(setAlgorithm(tVMainFrame), new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX/*|kLHintsExpandY*/,2,2,2,2));
  SetMWMHints(kMWMDecorAll,
	      kMWMFuncAll,
	      kMWMInputModeless);
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
  TGTextButton *tbStart;
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
  gfPotenziale->AddFrame(tHFrame = new TGHorizontalFrame(gfPotenziale));
  tHFrame->AddFrame(/*numpar[0] = */new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"[0]"),LabelLayout);
  //Distanza Piastre
  gfPotenziale->AddFrame(tHFrame = new TGHorizontalFrame(gfPotenziale));
  tHFrame->AddFrame(/*numpar[1] = */new TGNumberEntry (tHFrame,0.5,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
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
  tHFrame->AddFrame(/*numLarg = */new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Larghezza"),LabelLayout);
  //energia
  gfPacchetto->AddFrame(tHFrame = new TGHorizontalFrame(gfPacchetto));
  tHFrame->AddFrame(/*numEne = */new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Energia"),LabelLayout);
  //massa
  gfPacchetto->AddFrame(tHFrame = new TGHorizontalFrame(gfPacchetto));
  tHFrame->AddFrame(/*numEne = */new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
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
  tHFrame->AddFrame(/*numSpaceLim = */new TGNumberEntry (tHFrame,10,5,-1,TGNumberFormat::kNESRealOne, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,40));//40 come max e` troppo per la mia macchina, ma puo` andare su un mezzo un po' piu` potente
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Spazio"),LabelLayout);
  //Tempo
  gfLimits->AddFrame(tHFrame = new TGHorizontalFrame(gfLimits));
  tHFrame->AddFrame(/*numTimeLim = */new TGNumberEntry (tHFrame,3.5,5,-1,TGNumberFormat::kNESRealOne, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,40));//40 come max e` troppo per la mia macchina
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Tempo"),LabelLayout);
  //scelta su come calcolare i passi
  TGButtonGroup*  bgSetSteps = new TGButtonGroup(tHMainFrame,"Calcolo passi");//,kVerticalFrame);//,uGC->GetGC());
  TGRadioButton** StepMethods = new TGRadioButton*[3];
  StepMethods[0] = new TGRadioButton(bgSetSteps,"Da passo a N");
  StepMethods[1] = new TGRadioButton(bgSetSteps,"Da N a Passo");

  StepMethods[0]->SetState(kButtonDown);

  //quantifico i Passi
  TGGroupFrame *gfSteps = new TGGroupFrame(tHMainFrame,"Impostazioni Passi");
  gfSteps->AddFrame(tHFrame = new TGHorizontalFrame(gfSteps));
  //passi
  tHFrame->AddFrame(numSpaceStep = new TGNumberEntry (tHFrame,0.0001,5,-1,TGNumberFormat::kNESRealFour, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,1));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"#delta S"),LabelLayout);
  gfSteps->AddFrame(tHFrame = new TGHorizontalFrame(gfSteps));
  tHFrame->AddFrame(numTimeStep = new TGNumberEntry (tHFrame,0.0001,5,-1,TGNumberFormat::kNESRealFour, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,1));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"#delta T"),LabelLayout);
  //numero
  tHFrame->AddFrame(numSpaceStep = new TGNumberEntry (tHFrame,0.0001,5,-1,TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,1000000000));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Passi S"),LabelLayout);
  gfSteps->AddFrame(tHFrame = new TGHorizontalFrame(gfSteps));
  tHFrame->AddFrame(numTimeStep = new TGNumberEntry (tHFrame,0.0001,5,-1,TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,1000000000));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Passi T"),LabelLayout);

  tHMainFrame -> AddFrame(gfLimits, elementsHints);
  tHMainFrame -> AddFrame(bgSetSteps, elementsHints);
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
