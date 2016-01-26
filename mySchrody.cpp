#include "mySchrody.hpp"

void mySchrody(){//prootipo per vecoceutilizzo con root
  new Schrody(gClient->GetRoot(),490,372);
}
  

Schrody::Schrody(const TGWindow *p,int w,int h)
  :TGMainFrame(p,w,h,kMainFrame | kVerticalFrame){
  SetName("Risoluzione equazione di Schrodinger");
    
  SetMWMHints(kMWMDecorAll,
	      kMWMFuncAll,
	      kMWMInputModeless);
  MapSubwindows();
  
  Resize(GetDefaultSize());
  MapWindow();
  Resize(800,600);
}
