#include "mySchrody.hpp"

void mySchrody(){//prootipo per vecoceutilizzo con root
  new Schrody(gClient->GetRoot(),490,372);
}
  

Schrody::Schrody(const TGWindow *p,int w,int h)
  :TGMainFrame(p,w,h,kMainFrame | kHorizontalFrame){
  SetName("Risoluzione equazione di Schrodinger");
  SetConditions();
  SetMWMHints(kMWMDecorAll,
	      kMWMFuncAll,
	      kMWMInputModeless);
  MapSubwindows();
  
  Resize(GetDefaultSize());
  MapWindow();
  Resize(800,600);
}

void Schrody::SetConditions(){
  TGVerticalFrame *tVMainFrame =  new TGVerticalFrame(this);
  //  TGButtonGroup  GroupMetodo = new TGButtonGroup(tHMainFrame,"Metodo");
  //dichiaro due dummy per comodita`
  TGHorizontalFrame *tHFrame; 
  TGLabel *tLabel;
  //hints per le labels:
  TGLayoutHints *LabelLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
  
  //Impostazioni potenziale (magari aggiorno realtime la canvas)
  TGGroupFrame *gfPotenziale = new TGGroupFrame(tVMainFrame,"Potenziale");
  //forma potenziale
  gfPotenziale->AddFrame(comboPotentials = new TGComboBox (gfPotenziale),
			 new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX|kLHintsExpandY,2,2,2,2));//da aggiustare
  //roba moooolto temporanei
  comboPotentials->NewEntry("[0]+x*[1]");
  comboPotentials->NewEntry("[0]*H(x-[1])");
  comboPotentials->NewEntry("[0]*H(x-[1])*H([2]-x)");
  comboPotentials->NewEntry("gauss(x,[0],[1])");
  
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
  
  tVMainFrame -> AddFrame(gfPotenziale, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
  tVMainFrame -> AddFrame(gfPacchetto, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
  AddFrame(tVMainFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX|kLHintsExpandY,2,2,2,2));
}

void Schrody::exit(){
  gApplication->Terminate(0);
}
