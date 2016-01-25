#include <TApplication.h>
#include <TROOT.h>
#include <TGFrame.h>
#include "GuiPDE.hpp"

#ifndef STANDALONE
#include "PDE.cpp"
#include "GuiPDE.cpp"
#endif

void mainPDE()
{
  PDECond* a = new PDECond();
  new PDEGui(gClient->GetRoot(),490,372,a);
}

//---- Main program ------------------------------------------------------------
#ifdef STANDALONE
int main(int argc, char **argv)
{
   TApplication theApp("App", &argc, argv);

   if (gROOT->IsBatch()) {
      fprintf(stderr, "%s: cannot run in batch mode\n", argv[0]);
      return 1;
   }

   mainPDE();

   theApp.Run();

   return 0;
}
#endif
