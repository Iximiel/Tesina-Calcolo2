#include "DefineCC.hpp"
#include "TGLabel.h"
#include "TGButton.h"



DefineCC::DefineCC(const TGWindow *p, const char* title, guiInfo *holder, bool isFirst)
  : TGTransientFrame(gClient->GetRoot(),p){
  SetName("CC");//title);
  info = holder;
  first = isFirst;
  
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
TGFrame* DefineCC::buttons(const TGWindow *p){
  TGHorizontalFrame *tHMainFrame =  new TGHorizontalFrame(p,150,20,kFixedWidth);
  TGLayoutHints *ButtonsLayout = new TGLayoutHints(kLHintsTop/*CenterY*/ | kLHintsRight | kLHintsExpandX, 2, 2, 2, 2);
  TGTextButton *tbOK, *tbUndo;
  tbOK = new TGTextButton(tHMainFrame,"Ok");
  tbUndo = new TGTextButton(tHMainFrame,"Annulla");
  tHMainFrame->AddFrame(tbOK,ButtonsLayout);
  tHMainFrame->AddFrame(tbUndo,ButtonsLayout);
  tbUndo -> Connect("Clicked()","DefineCC",this,"doUndo()");
  tbOK -> Connect("Clicked()","DefineCC",this,"doOK()");
  tHMainFrame->Resize(150,tbOK -> GetDefaultHeight());
  return tHMainFrame;
}

TGFrame* DefineCC::tabs(const TGWindow *p, int w, int h){
  mainTab = new TGTab(p,w,h);
  mainTab->AddTab("Dirichlet",tabDirichlet(mainTab));
  mainTab->AddTab("Neumann",tabNeumann(mainTab));
  mainTab->AddTab("Robin",tabRobin(mainTab));
  return mainTab;
}

TGCompositeFrame* DefineCC::tabDirichlet(const TGWindow *p){
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

TGCompositeFrame* DefineCC::tabNeumann(const TGWindow *p){
  TGVerticalFrame* tVFrame = new TGVerticalFrame(p);
  TGHorizontalFrame *tHFrame;
  TGLayoutHints *LabelLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
  TGLabel *tLabel;
  tVFrame->AddFrame(tLabel = new TGLabel(tVFrame,"Indica il valore della derivata"),LabelLayout);
  tVFrame->AddFrame(tHFrame = new TGHorizontalFrame(tVFrame));
  tHFrame->AddFrame(numNeuDer = new TGNumberEntry (tHFrame,0,5,-1,TGNumberFormat::kNESRealTwo, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, -100,100));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Valore Derivata"),LabelLayout);
  return tVFrame;
}



TGCompositeFrame* DefineCC::tabRobin(const TGWindow *p){
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
  return tVFrame;
}

//slots
void DefineCC::doUndo(){
  Emit("didUndo()");
  CloseWindow();
}

void DefineCC::doOK(){  
  if(first){
    info->setCC0 = true;
    info->CC0 = mainTab -> GetCurrent();
    switch(info->CC0){
    case 0:{
      info->val0 = numDiFunc->GetNumber();
    }
      break;
    case 1:{
      info->val0 = numDiFunc->GetNumber();
    }
      break;
    case 2:{
      info->weight0 = numRobWeigh->GetNumber();
      info->val0 = numRobVal->GetNumber();
    }
      break;
    }
  }else{
    info->setCCN = true;
    info->CCN = mainTab -> GetCurrent();
    switch(info->CCN){
    case 0:{
      info->valN = numDiFunc->GetNumber();
    }
      break;
    case 1:{
      info->valN = numDiFunc->GetNumber();
    }
      break;
    case 2:{
      info->weightN = numRobWeigh->GetNumber();
      info->valN = numRobVal->GetNumber();
    }
      break;
    }
  }
  Emit("CCsets(bool)",info->setCC0&&info->setCCN);
  CloseWindow();
}
void DefineCC::CCsets(bool t){  
  Emit("CCsets(bool)",t);
}
