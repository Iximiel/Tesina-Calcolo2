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
  //se il layout non mi piace spostare questi tre blocchi si rivlea estremamente veloce
  TGFrame* setConditions(const TGWindow *p);
  TGFrame* setCanvas(const TGWindow *p);
  TGFrame* setAlgorithm(const TGWindow *p);
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
