#ifndef _CLASSVisual
#define _CLASSVisual
//rootgui
#include "TGFrame.h"
#include "TGComboBox.h"
#include <TGButton.h>
#include <TGSlider.h>
#include <TGLabel.h>
#include <TGButtonGroup.h>
//root
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
//
#include <vector>

class Visual : public TGMainFrame{
  ClassDef(Visual,1)
  public:
  Visual(const TGWindow *p,int w,int h);
  ~Visual();
  void loadFile(std::string fanme);
  //slots
  void exit();
  void OpenFile();
  void SaveFile();
  void SetObs(int);
  void SetCI();
  void DoFit();
  void doData();
  void doDataNoImg();
  void makeGif();
private:
  //se il layout non mi piace spostare questi tre blocchi si rivlea estremamente veloce
  void ready(bool);
  std::vector<double> Z;
  double tstep,sstep,maxpos;
  double myNorm, myMid, mySigma;
  TGraph *myCI,*myObs;
  TMultiGraph *myVisual;

  TGFrame* setButtons(const TGWindow *p);
  TGFrame* setCanvas(const TGWindow *p);
  int Nl, Nt;
  TGHSlider *sliderT;
  TGTextButton *tbOpen, *tbSave, *tbDoThing, *tbDoNoImg, *tbFit, *tbEaster;
  TGButtonGroup *bgSetSteps;
  TGLabel *lbTime;
  TCanvas *showCanvas;
};
#endif //_CLASSVisual
