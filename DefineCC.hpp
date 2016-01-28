#ifndef _DefineCC
#define _DefineCC
#include "guiInfo.hpp"

class DefineCC : public TGTransientFrame{
  RQ_OBJECT("DefineCC")
  ClassDef(DefineCC,1)
  public:
  DefineCC(const TGWindow *p, const char* title, guiInfo *holder, bool isFirst);
  //  ~DefineCC()
  //slots
  void doUndo();
  void doOK();
  //signals
  void CCsets(bool);//*SIGNAL*
  private:
  //dati
  guiInfo* info;
  bool first;
  //componenti
  TGTab *mainTab;
  TGNumberEntry *numRobWeigh, *numRobVal, *numDiFunc, *numNeuDer;
  //costruzione
  
  TGFrame *buttons(const TGWindow *p);
  TGFrame *tabs(const TGWindow *p, int w, int h);
  TGCompositeFrame *tabDirichlet(const TGWindow *p);
  TGCompositeFrame *tabNeumann(const TGWindow *p);
  TGCompositeFrame *tabRobin(const TGWindow *p);

};
#endif //_DefineCC
