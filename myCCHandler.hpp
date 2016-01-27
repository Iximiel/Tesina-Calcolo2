#ifndef _DefineCC
#define _DefineCC
class DefineCC : public TGTransientFrame{
  ClassDef(DefineCC,1)
  public:
  DefineCC(const TGWindow *p, const char* title/*,*/);
  //  ~DefineCC()
  //slots
  void doUndo();
  void doOK();
  //signals
  void Dirichlet(double val);//*SIGNAL*
  void Neumann(double val);//*SIGNAL*
  void Robin(double f,double val);//*SIGNAL*
  private:
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
