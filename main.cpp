#include <TApplication.h>
#include <TROOT.h>
#include <TGFrame.h>
#include "Schrody.hpp"

//---- Main program ------------------------------------------------------------
#ifdef STANDALONE
int main(int argc, char **argv)
{
   TApplication theApp("App", &argc, argv);

   if (gROOT->IsBatch()) {
      fprintf(stderr, "%s: cannot run in batch mode\n", argv[0]);
      return 1;
   }


   new Schrody(gClient->GetRoot(),490,372);

   theApp.Run();

   return 0;
}
#endif
