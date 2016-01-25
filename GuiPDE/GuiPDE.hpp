#ifndef myPDEGui
#ifndef ROOT_TGNumberEntry
#include "TGNumberEntry.h"
#endif
#ifndef ROOT_TRootEmbeddedCanvas
#include "TRootEmbeddedCanvas.h"
#endif
#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif
#ifndef ROOT_TGProgressBar
#include "TGProgressBar.h"
#endif
#ifndef myPDECond
#include "PDE.hpp"
#endif
#ifndef ROOT_TGStatusBar
#include "TGStatusBar.h"
#endif
#include "TGraph2D.h"
#define myPDEGui

class PDEGui : public TGMainFrame{
  ClassDef(PDEGui,1)
public:
  PDEGui(const TGWindow *p,int w,int h, PDECond*);
  //slots
  void exit();
  void doCalc();
private:
  void SetCanvas();//spazio superiore
  void SetData();//spazio centrale
  void SetStatus();//spazio inferiore e pulsanti
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
};

#endif//myPDEGui


