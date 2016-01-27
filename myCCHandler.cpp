#include "myCCHandler.hpp"

void myCCHandler(){
 new DefineCC(gClient->GetRoot());
}

DefineCC::DefineCC(const TGWindow *p/*,*/)
  : TGTransientFrame(p){
  AddFrame(buttons(this),new TGLayoutHints(kLHintsBottom | kLHintsRight,2,2,5,1));
  AddFrame(tabs(this,300,300),new TGLayoutHints(kLHintsBottom | kLHintsExpandX | kLHintsExpandY,2,2,5,1));
    SetMWMHints(kMWMDecorAll,
	      kMWMFuncAll,
	      kMWMInputModeless);
  MapSubwindows();
  
  Resize(GetDefaultSize());
  MapWindow();
  //  Resize(800,600);
}


TGFrame DefineCC::*buttons(const TGWindow *p){
  TGHorizontalFrame *tHMainFrame =  new TGHorizontalFrame(p,150,20,kFixedWidth);
  TGLayoutHints *ButtonsLayout = new TGLayoutHints(kLHintsTop/*CenterY*/ | kLHintsRight | kLHintsExpandX, 2, 2, 2, 2);
  TGTextButton *tbOK, *tbUndo;
  tbOk = new TGTextButton(tHMainFrame,"Ok");
  tbUndo = new TGTextButton(tHMainFrame,"Annulla");
  tHMainFrame->AddFrame(tbOk,ButtonsLayout);
  tHMainFrame->AddFrame(tbUndo,ButtonsLayout);
  Resize(150,tbOk -> GetDefaultHeight());
  return tHMainFrame;
}

TGFrame DefineCC::*tabs(const TGWindow *p, int w, int h){
  TGTab *mainTab = new TGTab(p,w,h);
  mainTab->AddTab("Dirichlet",tabDirichlet(mainTab));
  mainTab->AddTab("Neumann",tabNeumann(mainTab));
  mainTab->AddTab("Robin",tabRobin(mainTab));
  return mainTab;
}

TGCompositeFrame DefineCC::*tabDirichlet(const TGWindow *p){
  TGVerticalFrame* tVFrame = new TGVerticalFrame(p);
  TGHorizontalFrame *tHFrame;
  TGLayoutHints *LabelLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
  TGLabel *tLabel;
  tVFrame->AddFrame(tLabel = new TGLabel(tVFrame,"Indica il valore della funzione"),LabelLayout);
  tVFrame->AddFrame(tHFrame = new TGHorizontalFrame(tVFrame));
  tHFrame->AddFrame(/*numDiFunc = */new TGNumberEntry (tHFrame,10,5,-1,TGNumberFormat::kNESRealTwo, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, -100,100));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Valore Funzione"),LabelLayout);
  return tVFrame;
}

TGCompositeFrame DefineCC::*tabNeumann(const TGWindow *p){
  TGVerticalFrame* tVFrame = new TGVerticalFrame(p);
  TGHorizontalFrame *tHFrame;
  TGLayoutHints *LabelLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
  TGLabel *tLabel;
  tVFrame->AddFrame(tLabel = new TGLabel(tVFrame,"Indica il valore della derivata"),LabelLayout);
  tVFrame->AddFrame(tHFrame = new TGHorizontalFrame(tVFrame));
  tHFrame->AddFrame(/*numNeuDer = */new TGNumberEntry (tHFrame,10,5,-1,TGNumberFormat::kNESRealTwo, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, -100,100));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Valore Derivata"),LabelLayout);
  tVFrame;
}

TGCompositeFrame DefineCC::*tabRobin(const TGWindow *p){
  TGVerticalFrame* tVFrame = new TGVerticalFrame(p);
  TGHorizontalFrame *tHFrame;
  TGLayoutHints *LabelLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
  TGLabel *tLabel;
  tVFrame->AddFrame(tLabel = new TGLabel(tVFrame,"Indica il valore della combinazione lineare\ntra derivata e valore della funzione"),LabelLayout);
  tVFrame->AddFrame(tHFrame = new TGHorizontalFrame(tVFrame));
  tHFrame->AddFrame(/*numRobWeigh = */new TGNumberEntry (tHFrame,10,5,-1,TGNumberFormat::kNESRealTwo, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,40));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Peso Funzione"),LabelLayout);
    tVFrame->AddFrame(tHFrame = new TGHorizontalFrame(tVFrame));
  tHFrame->AddFrame(/*numRobVal = */new TGNumberEntry (tHFrame,10,5,-1,TGNumberFormat::kNESRealTwo, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,40));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Valore combinazione"),LabelLayout);
  tVFrame;
}
