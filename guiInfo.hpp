#ifndef _GUIINFO
#define _GUIINFO
struct guiInfo{
  double val0, weight0;//CC in 0
  double valN, weightN;//CC in N
  int CC0, CCN;//0,1,2 Dirichlet, Neumann, Robin in 0, N
  bool setCC0, setCCN;
  guiInfo(){setCC0 = setCCN = false;}
};
#endif //_GUIINFO
