#ifndef _CLASSSCHRODY
#define _CLASSSCHRODY
//#include "TGMainFrame.h"
#include "DefineCC.hpp"

#include "TGFrame.h"
#include "TGComboBox.h"
#include "TGButton.h"


class Schrody : public TGMainFrame{
  ClassDef(Schrody,1)
  public:
  Schrody(const TGWindow *p,int w,int h);
  //slots
  void exit();
  void doTheThing();
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
  TGNumberEntry *numNorm, *numLarg, *numEne, *numMass,
    *numSpaceStep, *numTimeStep, *numSpaceSteps, *numTimeSteps,
    *numSpaceLim, *numTimeLim;
  TGNumberEntry **numpar;
  TGComboBox *comboPotentials;
  TGTextButton *tbStart;

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
