#ifndef _CLASSSCHRODY
#define _CLASSSCHRODY

#include "DefineCC.hpp"

class Schrody : public TGMainFrame{
  ClassDef(Schrody,1)
  public:
  Schrody(const TGWindow *p,int w,int h);
  //slots
  void exit();
  void launchCC0();
  void launchCCN();
  void CCset(bool);
  void controlReady();
private:
  //dati
  guiInfo* info;
  bool CC;
  //se il layout non mi piace spostare questi tre blocchi si rivlea estremamente veloce
  TGFrame* setConditions(const TGWindow *p);
  TGFrame* setCanvas(const TGWindow *p);
  TGFrame* setAlgorithm(const TGWindow *p);
  
  DefineCC *CC0, *CCN;
  TGNumberEntry *numNorm, *numSpaceStep, *numTimeStep, *numSpaceStep, *numTimeStep;
  TGComboBox *comboPotentials;

  /*
  //
  PDECond *myPDE;
  //
  TGraph2D *grafo;
  //
  TRootEmbeddedCanvas *ECanvas;
  TCanvas *childCanvas;
  TGButtonGroup *GroupMetodo;
  //  TGGroupFrame  *GroupVar;
  TGRadioButton **Methods;
  TGTextButton *BtStart, *BtExit;
  TGNumberEntry *numPowPrec, *numPlateDist, *numPlateLenght;
  TGNumberEntry *numH, *numW, *numSOR, *numHmm, *numWmm;
  TGStatusBar *StatusBar;
  TGVProgressBar *PBprecision;
  */
};
#endif //_CLASSSCHRODY
