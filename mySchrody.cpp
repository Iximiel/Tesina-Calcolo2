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
  TGGroupFrame *gfPotenziale = new TGGroupFrame(tVMainFrame,"Potenziale");
  //dichiaro due dummy per comodita`
  TGHorizontalFrame *tHFrame; 
  TGLabel *tLabel;
  //hints per le labels:
  TGLayoutHints *LabelLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
  //esempio di come voglio fare(placeholders)
    gfPotenziale->AddFrame(tHFrame = new TGHorizontalFrame(gfPotenziale));
    tHFrame->AddFrame(/*numpar[0] = */new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"[0]"),LabelLayout);
  //Distanza Piastre
  gfPotenziale->AddFrame(tHFrame = new TGHorizontalFrame(gfPotenziale));
  tHFrame->AddFrame(/*numpar[1] = */new TGNumberEntry (tHFrame,0.5,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"[1]"),LabelLayout);
  
  tVMainFrame -> AddFrame(gfPotenziale, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
  AddFrame(tVMainFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX|kLHintsExpandY,2,2,2,2));
}

void Schrody::exit(){
  gApplication->Terminate(0);
}
