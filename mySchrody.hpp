#ifndef _CLASSSCHRODY
#define _CLASSSCHRODY

class Schrody : public TGMainFrame{
  ClassDef(Schrody,1)
public:
  Schrody(const TGWindow *p,int w,int h);
  //slots
 void exit();
  // void doCalc();
private:
  void SetConditions();
  TGNumberEntry *numNorm;
  TGComboBox *comboPotentials;
  /* void SetCanvas();//spazio superiore
  void SetData();//spazio centrale
  void SetStatus();//spazio inferiore e pulsanti
  */
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
