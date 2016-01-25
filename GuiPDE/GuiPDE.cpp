#include "GuiPDE.hpp"
//#include "PDE.cpp"//serve a lanciare in root
#include <iostream>//debug
#ifndef ROOT_TGLabel
#include "TGLabel.h"
#endif
#ifndef ROOT_TGButtonGroup
#include "TGButtonGroup.h"
#endif
#include "TApplication.h"
/*
  #ifndef ROOT_TGDockableFrame
  #include "TGDockableFrame.h"
  #endif
  #ifndef ROOT_TGMenu
  #include "TGMenu.h"
  #endif
  #ifndef ROOT_TGMdiDecorFrame
  #include "TGMdiDecorFrame.h"
  #endif
  #ifndef ROOT_TG3DLine
  #include "TG3DLine.h"
  #endif
  #ifndef ROOT_TGMdiFrame
  #include "TGMdiFrame.h"
  #endif
  #ifndef ROOT_TGMdiMainFrame
  #include "TGMdiMainFrame.h"
  #endif
  #ifndef ROOT_TGMdiMenu
  #include "TGMdiMenu.h"
  #endif
  #ifndef ROOT_TGListBox
  #include "TGListBox.h"
  #endif
  #ifndef ROOT_TGScrollBar
  #include "TGScrollBar.h"
  #endif
  #ifndef ROOT_TGComboBox
  #include "TGComboBox.h"
  #endif
  #ifndef ROOT_TGuiBldHintsEditor
  #include "TGuiBldHintsEditor.h"
  #endif
  #ifndef ROOT_TGuiBldNameFrame
  #include "TGuiBldNameFrame.h"
  #endif
  #ifndef ROOT_TGFrame
  #include "TGFrame.h"
  #endif
  #ifndef ROOT_TGFileDialog
  #include "TGFileDialog.h"
  #endif
  #ifndef ROOT_TGShutter
  #include "TGShutter.h"
  #endif
  #ifndef ROOT_TGCanvas
  #include "TGCanvas.h"
  #endif
  #ifndef ROOT_TGFSContainer
  #include "TGFSContainer.h"
  #endif
  #ifndef ROOT_TGFontDialog
  #include "TGFontDialog.h"
  #endif
  #ifndef ROOT_TGuiBldEditor
  #include "TGuiBldEditor.h"
  #endif
  #ifndef ROOT_TGColorSelect
  #include "TGColorSelect.h"
  #endif
  #ifndef ROOT_TGButton
  #include "TGButton.h"
  #endif
  #ifndef ROOT_TGFSComboBox
  #include "TGFSComboBox.h"
  #endif
  #ifndef ROOT_TGMsgBox
  #include "TGMsgBox.h"
  #endif
  #ifndef ROOT_TRootGuiBuilder
  #include "TRootGuiBuilder.h"
  #endif
  #ifndef ROOT_TGTab
  #include "TGTab.h"
  #endif
  #ifndef ROOT_TGListView
  #include "TGListView.h"
  #endif
  #ifndef ROOT_TGSplitter
  #include "TGSplitter.h"
  #endif
  #ifndef ROOT_TRootCanvas
  #include "TRootCanvas.h"
  #endif
  #ifndef ROOT_TGListTree
  #include "TGListTree.h"
  #endif
  #ifndef ROOT_TGuiBldGeometryFrame
  #include "TGuiBldGeometryFrame.h"
  #endif
  #ifndef ROOT_TGToolTip
  #include "TGToolTip.h"
  #endif
  #ifndef ROOT_TGToolBar
  #include "TGToolBar.h"
  #endif
  #ifndef ROOT_TGuiBldDragManager
  #include "TGuiBldDragManager.h"
  #endif
  #include "Riostream.h"
*/
/*
  void Gui_PDE()
  {

  // main frame
  TGMainFrame *fMainFrame1600 = new TGMainFrame(gClient->GetRoot(),10,10,kMainFrame | kVerticalFrame);
  fMainFrame1600->SetName("fMainFrame1600");
  fMainFrame1600->SetLayoutBroken(kTRUE);
  TGTextButton *fTextButton560 = new TGTextButton(fMainFrame1600,"fTextButton560");
  fTextButton560->SetTextJustify(36);
  fTextButton560->SetMargins(0,0,0,0);
  fTextButton560->SetWrapLength(-1);
  fTextButton560->Resize(94,24);
  fMainFrame1600->AddFrame(fTextButton560, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  fTextButton560->MoveResize(16,336,94,24);
  TGTextButton *fTextButton565 = new TGTextButton(fMainFrame1600,"fTextButton565");
  fTextButton565->SetTextJustify(36);
  fTextButton565->SetMargins(0,0,0,0);
  fTextButton565->SetWrapLength(-1);
  fTextButton565->Resize(112,24);
  fMainFrame1600->AddFrame(fTextButton565, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  fTextButton565->MoveResize(144,336,112,24);

  TGFont *ufont;         // will reflect user font changes
  ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

  TGGC   *uGC;           // will reflect user GC changes
  // graphics context changes
  GCValues_t valo;
  valo.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
  gClient->GetColorByName("#000000",valo.fForeground);
  gClient->GetColorByName("#e8e8e8",valo.fBackground);
  valo.fFillStyle = kFillSolid;
  valo.fFont = ufont->GetFontHandle();
  valo.fGraphicsExposures = kFALSE;
  uGC = gClient->GetGC(&valo, kTRUE);

  // "fGroupFrame570" group frame
 
  // "fGroupFrame880" group frame
  TGGroupFrame *Dati = new TGGroupFrame(fMainFrame1600,"fGroupFrame880");

  Dati->SetLayoutManager(new TGVerticalLayout(Dati));
  Dati->Resize(143,72);
  fMainFrame1600->AddFrame(Dati, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  Dati->MoveResize(16,232,143,72);


  TGHProgressBar *fHProgressBar1337 = new TGHProgressBar(fMainFrame1600 ,176);
  fHProgressBar1337->SetName("fHProgressBar1337")
  fHProgressBar1337->SetFillType(TGProgressBar::kBlockFill);
  fHProgressBar1337->ChangeOptions(kSunkenFrame | kDoubleBorder | kOwnBackground);

  ULong_t ucolor;        // will reflect user color changes
  gClient->GetColorByName("#ffffff",ucolor);
  fHProgressBar1337->SetBackgroundColor(ucolor);
  fHProgressBar1337->SetPosition(25);
  fMainFrame1600->AddFrame(fHProgressBar1337, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  fHProgressBar1337->MoveResize(288,336,176,24);

  fMainFrame1600->SetMWMHints(kMWMDecorAll,
  kMWMFuncAll,
  kMWMInputModeless);
  fMainFrame1600->MapSubwindows();

  fMainFrame1600->Resize(fMainFrame1600->GetDefaultSize());
  fMainFrame1600->MapWindow();
  fMainFrame1600->Resize(490,372);
  }  
*/
PDEGui::PDEGui(const TGWindow *p,int w,int h, PDECond* included)
  :TGMainFrame(p,w,h,kMainFrame | kVerticalFrame){
  myPDE = included;
  grafo = new TGraph2D(1);
  SetName("PDEGui");
  //SetLayoutBroken(kTRUE);
 
  SetCanvas();
  SetData();
  SetStatus();
  
  SetMWMHints(kMWMDecorAll,
	      kMWMFuncAll,
	      kMWMInputModeless);
  MapSubwindows();
  
  Resize(GetDefaultSize());
  MapWindow();
  Resize(800,600);
}


void PDEGui::SetCanvas(){
  ECanvas = new TRootEmbeddedCanvas(0,this,456,192);
  ECanvas->SetName("Canvas");
  int CanvasID = ECanvas->GetCanvasWindowId();
  childCanvas = new TCanvas("childCanvas", 10, 10, CanvasID);
  ECanvas->AdoptCanvas(childCanvas);
  AddFrame(ECanvas, new TGLayoutHints(kLHintsLeft | kLHintsTop|kLHintsExpandX|kLHintsExpandY,2,2,2,2));
}

void PDEGui::SetData(){
  TGHorizontalFrame *tHMainFrame =  new TGHorizontalFrame(this); 
  //Selezionare Metodo
  GroupMetodo = new TGButtonGroup(tHMainFrame,"Metodo");//,kVerticalFrame);//,uGC->GetGC());
  Methods = new TGRadioButton*[3];
  Methods[0] = new TGRadioButton(GroupMetodo,"Jacobi");
  Methods[1] = new TGRadioButton(GroupMetodo,"Gauss-Seidel");
  Methods[2] = new TGRadioButton(GroupMetodo,"Sovrarilassamento");

  Methods[2]->SetState(kButtonDown);
  /*
    for(int i=0;i<3;i++){
    Methods[i]->SetTextJustify(36);
    Methods[i]->SetMargins(0,0,0,0);
    Methods[i]->SetWrapLength(-1);
    }
  */
  //GroupMetodo->SetLayoutManager(new TGVerticalLayout(GroupMetodo));
  TGGroupFrame *Piastre = new TGGroupFrame(tHMainFrame,"Piastre");
  TGHorizontalFrame *tHFrame; 
  TGLabel *tLabel;
  TGLayoutHints *LabelLayout = new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 2, 2, 2, 2);
    //Lunghezza Piastre
  Piastre->AddFrame(tHFrame = new TGHorizontalFrame(Piastre));
  tHFrame->AddFrame(numPlateLenght = new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Lunghezza Piastre"),LabelLayout);
  //Distanza Piastre
  Piastre->AddFrame(tHFrame = new TGHorizontalFrame(Piastre));
  tHFrame->AddFrame(numPlateDist = new TGNumberEntry (tHFrame,0.5,5,-1,TGNumberFormat::kNESReal, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Distanza Piastre"),LabelLayout);
  
  TGGroupFrame *Dati = new TGGroupFrame(tHMainFrame,"Campo");
  //dimensione Verticale
  Dati->AddFrame(tHFrame = new TGHorizontalFrame(Dati));
  tHFrame->AddFrame(numHmm = new TGNumberEntry (tHFrame,10,5,-1,TGNumberFormat::kNESReal,
						TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 3,30));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Lunghezza(mm)"),LabelLayout);
  //dimensione Orizzontale
  Dati->AddFrame(tHFrame = new TGHorizontalFrame(Dati));
  tHFrame->AddFrame(numWmm = new TGNumberEntry (tHFrame,10,5,-1,TGNumberFormat::kNESReal,
						TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 3,30));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Larghezza(mm)"),LabelLayout);
  
  TGGroupFrame *Calcolo = new TGGroupFrame(tHMainFrame,"Calcolo");
  //Precisione
  Calcolo->AddFrame(tHFrame = new TGHorizontalFrame(Calcolo));
  tHFrame->AddFrame(numPowPrec = new TGNumberEntry (tHFrame,6,5,-1,TGNumberFormat::kNESInteger,
						    TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 1,10));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Pot. Precisione"),LabelLayout);
  //PassoH
  Calcolo->AddFrame(tHFrame = new TGHorizontalFrame(Calcolo));
  tHFrame->AddFrame(numH = new TGNumberEntry (tHFrame,10,5,-1,TGNumberFormat::kNESInteger,
					      TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 1,1000));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Passo H(x100)"),LabelLayout);
  //PassoW
  Calcolo->AddFrame(tHFrame = new TGHorizontalFrame(Calcolo));
  tHFrame->AddFrame(numW = new TGNumberEntry (tHFrame,10,5,-1,TGNumberFormat::kNESInteger,
					      TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 1,1000));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Passo W(x100)"),LabelLayout);
  //parametro SOR
  Calcolo->AddFrame(tHFrame = new TGHorizontalFrame(Calcolo));
  tHFrame->AddFrame(numSOR = new TGNumberEntry (tHFrame,1.75,5,-1,TGNumberFormat::kNESRealTwo,
  						TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 1,2));
  tHFrame->AddFrame(tLabel = new TGLabel(tHFrame,"Par. SOR"),LabelLayout);
  
  PBprecision = new TGVProgressBar(tHMainFrame,TGProgressBar::kFancy,20);
  PBprecision->SetRange(0,1);
  PBprecision->Reset();
  //metto tutte le frame dove vanno
  tHMainFrame -> AddFrame(GroupMetodo, new TGLayoutHints(kLHintsLeft | kLHintsCenterY,2,2,2,2));
  tHMainFrame -> AddFrame(Piastre, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
  tHMainFrame -> AddFrame(Dati, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
  tHMainFrame -> AddFrame(Calcolo, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
  tHMainFrame -> AddFrame(PBprecision, new TGLayoutHints(kLHintsRight | kLHintsCenterY | kLHintsExpandY,2,2,2,2));
  AddFrame(tHMainFrame, new TGLayoutHints(kLHintsExpandX,2,2,2,2));
}

void PDEGui::SetStatus(){
  TGLayoutHints *ButtonLayout = new TGLayoutHints(kLHintsCenterY | kLHintsRight, 2, 2, 2, 2);
  TGHorizontalFrame *GroupVar = new TGHorizontalFrame(this);
  
  GroupVar->AddFrame(BtExit = new TGTextButton(GroupVar,"Esci"),ButtonLayout);
  BtExit -> Connect("Clicked()","PDEGui",this,"exit()");
  GroupVar->AddFrame(BtStart = new TGTextButton(GroupVar,"Avvia"),ButtonLayout);
  BtStart -> Connect("Clicked()","PDEGui",this,"doCalc()");
  
  StatusBar = new TGStatusBar(this,50,10,kHorizontalFrame);
  int parts[] = {33, 10, 10, 47};
  StatusBar->SetParts(parts,4);
  AddFrame(StatusBar, new TGLayoutHints(kLHintsBottom| kLHintsLeft| kLHintsExpandX, 0, 0, 2, 0));
  AddFrame(GroupVar, new TGLayoutHints(kLHintsRight | kLHintsBottom|kLHintsExpandX,2,2,2,2));
    
  //progressbar
  /* TGHProgressBar *fHProgressBar1337 = new TGHProgressBar(this ,176);
     fHProgressBar1337->SetName("fHProgressBar1337");
     fHProgressBar1337->SetFillType(TGProgressBar::kBlockFill);
     fHProgressBar1337->ChangeOptions(kSunkenFrame | kDoubleBorder | kOwnBackground);

     ULong_t ucolor;        // will reflect user color changes
     gClient->GetColorByName("#ffffff",ucolor);
     fHProgressBar1337->SetBackgroundColor(ucolor);
     fHProgressBar1337->SetPosition(25);
     AddFrame(fHProgressBar1337, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
     fHProgressBar1337->MoveResize(288,336,176,24);
  */
}


void PDEGui::exit(){
  gApplication->Terminate(0);
}

void PDEGui::doCalc(){
  PBprecision->Reset();
  int x = 100*numW -> GetNumber();
  int y = 100*numH -> GetNumber();
  double xdim = numWmm -> GetNumber();
  double ydim = numHmm -> GetNumber();
  double xdist = numPlateDist -> GetNumber();
  double ylenght = numPlateLenght -> GetNumber();
  double sor = numSOR -> GetNumber();
  double precision = pow(10,- numPowPrec -> GetNumber());
  // cout << precision << endl;
  int m = PDECond::mSOR;

  myPDE -> SetMethod(m, sor);
  //  myPDE -> SetPrecisionOnErrMax(0.02);
  myPDE -> SetCI(0.001);
  myPDE -> SetXY(x,y,xdim,ydim);
  myPDE -> SetCC(ylenght,xdist);//distanze dal centro
  //myPDE -> SetCC(double lenght, double dist);
  double error;
  do{
    error = myPDE -> Passo();
    PBprecision->SetPosition(precision/error);
    //std::cout << error << std::endl;
  }while(error > precision);
  grafo -> Clear();
  grafo -> Set(myPDE->GetNum());
  int k = 0;
  double  passox = myPDE->GetPassoX();
  double  passoy = myPDE->GetPassoY();
  for(int i=0; i<x;i++){
    for(int j=0; j<y;j++){
      grafo->SetPoint(k++, i * passox, j * passoy,myPDE -> GetData(i,j));
    }
  }
  childCanvas->cd();
  grafo->Draw("PCOL");
    childCanvas->Modified();
  childCanvas->Update();
}

void GuiPDE(){
  PDECond* a = new PDECond();
  new PDEGui(gClient->GetRoot(),490,372,a);
}
