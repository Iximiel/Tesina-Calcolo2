#include "DefineCC.hpp"

DefineCC::DefineCC(const TGWindow *p, const char* title/*,*/)
  : TGTransientFrame(p){
  SetName("CC");//title);
  AddFrame(buttons(this),new TGLayoutHints(kLHintsBottom | kLHintsRight,2,2,5,1));
  AddFrame(tabs(this,300,300),new TGLayoutHints(kLHintsBottom | kLHintsExpandX | kLHintsExpandY,2,2,5,1));
  SetMWMHints(kMWMDecorAll,
	      kMWMFuncAll,
	      kMWMInputModeless);
  MapSubwindows();
  Connect("CloseWindow()","DefineCC",this,"doUndo()");
  DontCallClose();
  Resize(GetDefaultSize());
  MapWindow();
  //  Resize(800,600);
}
/*
DefineCC::~DefineCC(){

}
*/
TGFrame DefineCC::*buttons(const TGWindow *p){
  TGHorizontalFrame *tHMainFrame =  new TGHorizontalFrame(p,150,20,kFixedWidth);
  TGLayoutHints *ButtonsLayout = new TGLayoutHints(kLHintsTop/*CenterY*/ | kLHintsRight | kLHintsExpandX, 2, 2, 2, 2);
  TGTextButton *tbOK, *tbUndo;
  tbOk = new TGTextButton(tHMainFrame,"Ok");
  tbUndo = new TGTextButton(tHMainFrame,"Annulla");
  tHMainFrame->AddFrame(tbOk,ButtonsLayout);
  tHMainFrame->AddFrame(tbUndo,ButtonsLayout);
  tbUndo -> Connect("Clicked()","DefineCC",this,"doUndo()");
  tbOk -> Connect("Clicked()","DefineCC",this,"doOK()");
  Resize(150,tbOk -> GetDefaultHeight());
  return tHMainFrame;
}

TGFrame DefineCC::*tabs(const TGWindow *p, int w, int h){
  mainTab = new TGTab(p,w,h);
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
  tHFrame->AddFrame(numDiFunc = new TGNumberEntry (tHFrame,0,5,-1,TGNumberFormat::kNESRealTwo, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, -100,100));
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
  tHFrame->AddFrame(numNeuDer = new TGNumberEntry (tHFrame,0,5,-1,TGNumberFormat::kNESRealTwo, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, -100,100));
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
  tHFrame->AddFrame(numRobWeigh = new TGNumberEntry (tHFrame,-1,5,-1,TGNumberFormat::kNESRealTwo, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,40));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Peso Funzione"),LabelLayout);
  tVFrame->AddFrame(tHFrame = new TGHorizontalFrame(tVFrame));
  tHFrame->AddFrame(numRobVal = new TGNumberEntry (tHFrame,0,5,-1,TGNumberFormat::kNESRealTwo, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,40));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Valore combinazione"),LabelLayout);
  tVFrame;
}

//slots
void DefineCC::doUndo(){
  didUndo();
  SendCloseMessage();
}

void DefineCC::doOK(){
  int tabsel =  mainTab -> GetCurrent();
  switch(tabsel){
  case 0:{
    double Dval = numDiFunc->GetNumber();
    Dirichlet(Dval);
  }
    break;
  case 1:{
    double Nval = numDiFunc->GetNumber();
    Neumann(Nval);    
  }
    break;
  case 2:{
    double f = numRobWeigh->GetNumber();
    double Rval = numRobVal->GetNumber();
    Robin(f,Rval);    
  }
    break;
  }
  SendCloseMessage();
}
//signals
void DefineCC::Dirichlet(double val){
  Emit("Dirichlet(double)",val);
}
void DefineCC::Neumann(double val){
  Emit("Neumann(double)",val);
}
void DefineCC::Robin(double f,double val){
  long arg[2] = {f,val};
  Emit("Dirichlet(double)",arg);
}
void DefineCC::didUndo(){
  Emit("didUndo()");
}

