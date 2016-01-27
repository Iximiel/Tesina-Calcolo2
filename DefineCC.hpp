#ifndef _DefineCC
#define _DefineCC
class DefineCC : public TGTransientFrame{
  RQ_OBJECT("DefineCC")
  ClassDef(DefineCC,1)
  public:
  DefineCC(const TGWindow *p, const char* title/*,*/);
  //  ~DefineCC()
  //slots
  void doUndo();
  void doOK();
  //signals
  void Dirichlet(double);//*SIGNAL*
  void Neumann(double);//*SIGNAL*
  void RobinW(double);//*SIGNAL*
  void RobinV(double);//*SIGNAL*
  void didUndo();//*SIGNAL*
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
