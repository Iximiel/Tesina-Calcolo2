#ifndef _CLASSVisual
#define _CLASSVisual
//rootgui
#include <TGFrame.h>
#include <TGComboBox.h>
#include <TGButton.h>
#include <TGSlider.h>
#include <TGLabel.h>
#include <TGButtonGroup.h>
#include <TGDoubleSlider.h>
//root
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
//
#include <vector>
#include <complex>
typedef std::complex<double> Var;

class Visual : public TGMainFrame{
  ClassDef(Visual,1)
  public:
  Visual(const TGWindow *p,int w,int h);
  ~Visual();
  void loadFile(std::string fanme);
  void loadPot(std::string fanme);
  void constructInt();
  //slots
  void exit();
  void OpenFile();
  void SaveFile();
  void SetObs(int);
  void ShowPot();
  void SetCI();
  void DoFit();
  void doData();
  void doSequence();
  void doDataNoImg();
  void makeGif();
  void doZoom();
  void callIntegral();
private:
  //se il layout non mi piace spostare questi tre blocchi si rivlea estremamente veloce
  TGFrame* setButtons(const TGWindow *p);
  TGFrame* setSliders(const TGWindow *p);
  TGFrame* setCanvas(const TGWindow *p);
  
  void ready(bool);
  //  std::vector<double> Z;
  std::vector<Var> Z;
  double tstep,sstep,maxpos;
  double myNorm, myMid, mySigma;
  TGraph *myCI,*myObs, *myPot;
  TGraph *myIm,*myRe;
  TMultiGraph *myVisual;
  
  int Nl, Nt;//Nl passi spaziali, Nt temporali
  bool Im,Re;
  TGComboBox *cbLine;
  TGHSlider *sliderT, *sliderLine;
  TGDoubleHSlider *sliderZoom;//per integrale
  TGCheckButton *cbIm, *cbRe;
  TGTextButton *tbOpen, *tbPot, *tbIntegral, *tbSequence;
  TGTextButton *tbSave, *tbDoThing, *tbDoNoImg, *tbFit, *tbEaster;
  TGButtonGroup *bgSetSteps;
  TGLabel *lbTime;
  TCanvas *showCanvas;
  
  //TGCheckButton
  TGTransientFrame *tfIntegral;//impostazioni per l'integrale
  
  double (*pot)(double,double,double);
};
#endif //_CLASSVisual
