#include <TApplication.h>
#include <TROOT.h>
#include <TGFrame.h>

void guitest()
{
   new TGMainFrame(gClient->GetRoot(), 400, 220);
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

   guitest();

   theApp.Run();

   return 0;
}
#endif
