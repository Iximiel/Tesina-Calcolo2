#ifndef _DefineCC
#define _DefineCC
class DefineCC : public TGTransientFrame{
  ClassDef(DefineCC,1)
  public:
  DefineCC(const TGWindow *p/*,*/);
  private:
  TGFrame *buttons(const TGWindow *p);
  TGFrame *tabs(const TGWindow *p, int w, int h);
  TGCompositeFrame *tabDirichlet(const TGWindow *p);
  TGCompositeFrame *tabNeumann(const TGWindow *p);
  TGCompositeFrame *tabRobin(const TGWindow *p);
};
#endif //_DefineCC
