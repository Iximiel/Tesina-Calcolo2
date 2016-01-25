// Mainframe macro generated from application: /usr/bin/root.exe
// By ROOT version 5.34/30 on 2015-12-23 08:33:20

#ifndef ROOT_TGDockableFrame
#include "TGDockableFrame.h"
#endif
#ifndef ROOT_TGMenu
#include "TGMenu.h"
#endif
#ifndef ROOT_TGMdiDecorFrame
#include "TGMdiDecorFrame.h"
#endif
#ifndef ROOT_TG3DLine
#include "TG3DLine.h"
#endif
#ifndef ROOT_TGMdiFrame
#include "TGMdiFrame.h"
#endif
#ifndef ROOT_TGMdiMainFrame
#include "TGMdiMainFrame.h"
#endif
#ifndef ROOT_TGMdiMenu
#include "TGMdiMenu.h"
#endif
#ifndef ROOT_TGListBox
#include "TGListBox.h"
#endif
#ifndef ROOT_TGNumberEntry
#include "TGNumberEntry.h"
#endif
#ifndef ROOT_TGScrollBar
#include "TGScrollBar.h"
#endif
#ifndef ROOT_TGComboBox
#include "TGComboBox.h"
#endif
/*
  #ifndef ROOT_TGuiBldHintsEditor
  #include "TGuiBldHintsEditor.h"
  #endif
  #ifndef ROOT_TGuiBldNameFrame
  #include "TGuiBldNameFrame.h"
  #endif
*/
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif
#ifndef ROOT_TGFileDialog
#include "TGFileDialog.h"
#endif
#ifndef ROOT_TGShutter
#include "TGShutter.h"
#endif
#ifndef ROOT_TGButtonGroup
#include "TGButtonGroup.h"
#endif
#ifndef ROOT_TGCanvas
#include "TGCanvas.h"
#endif
#ifndef ROOT_TGFSContainer
#include "TGFSContainer.h"
#endif
#ifndef ROOT_TGFontDialog
#include "TGFontDialog.h"
#endif
/*
  #ifndef ROOT_TGuiBldEditor
  #include "TGuiBldEditor.h"
  #endif
*/
#ifndef ROOT_TGColorSelect
#include "TGColorSelect.h"
#endif
#ifndef ROOT_TGButton
#include "TGButton.h"
#endif
#ifndef ROOT_TGFSComboBox
#include "TGFSComboBox.h"
#endif
#ifndef ROOT_TGLabel
#include "TGLabel.h"
#endif
#ifndef ROOT_TGProgressBar
#include "TGProgressBar.h"
#endif
#ifndef ROOT_TGMsgBox
#include "TGMsgBox.h"
#endif
/*
  #ifndef ROOT_TRootGuiBuilder
  #include "TRootGuiBuilder.h"
  #endif
*/
#ifndef ROOT_TGTab
#include "TGTab.h"
#endif
#ifndef ROOT_TGListView
#include "TGListView.h"
#endif
#ifndef ROOT_TGSplitter
#include "TGSplitter.h"
#endif
#ifndef ROOT_TRootCanvas
#include "TRootCanvas.h"
#endif
#ifndef ROOT_TGStatusBar
#include "TGStatusBar.h"
#endif
#ifndef ROOT_TGListTree
#include "TGListTree.h"
#endif
/*
  #ifndef ROOT_TGuiBldGeometryFrame
  #include "TGuiBldGeometryFrame.h"
  #endif
*/
#ifndef ROOT_TGToolTip
#include "TGToolTip.h"
#endif
#ifndef ROOT_TGToolBar
#include "TGToolBar.h"
#endif
#ifndef ROOT_TRootEmbeddedCanvas
#include "TRootEmbeddedCanvas.h"
#endif
#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif
/*
  #ifndef ROOT_TGuiBldDragManager
  #include "TGuiBldDragManager.h"
  #endif
*/

#include "Riostream.h"

void GuiPDE()
{

  // main frame
  TGMainFrame *fMainFrame1600 = new TGMainFrame(gClient->GetRoot(),10,10,kMainFrame | kVerticalFrame);
  fMainFrame1600->SetName("fMainFrame1600");
  fMainFrame1600->SetLayoutBroken(kTRUE);
  TGTextButton *fTextButton560 = new TGTextButton(fMainFrame1600,"fTextButton560");
  fTextButton560->SetTextJustify(36);
  fTextButton560->SetMargins(0,0,0,0);
  fTextButton560->SetWrapLength(-1);
  fTextButton560->Resize(94,24);
  fMainFrame1600->AddFrame(fTextButton560, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  fTextButton560->MoveResize(16,336,94,24);
  TGTextButton *fTextButton565 = new TGTextButton(fMainFrame1600,"fTextButton565");
  fTextButton565->SetTextJustify(36);
  fTextButton565->SetMargins(0,0,0,0);
  fTextButton565->SetWrapLength(-1);
  fTextButton565->Resize(112,24);
  fMainFrame1600->AddFrame(fTextButton565, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  fTextButton565->MoveResize(144,336,112,24);

  TGFont *ufont;         // will reflect user font changes
  ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

  TGGC   *uGC;           // will reflect user GC changes
  // graphics context changes
  GCValues_t valo;
  valo.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
  gClient->GetColorByName("#000000",valo.fForeground);
  gClient->GetColorByName("#e8e8e8",valo.fBackground);
  valo.fFillStyle = kFillSolid;
  valo.fFont = ufont->GetFontHandle();
  valo.fGraphicsExposures = kFALSE;
  uGC = gClient->GetGC(&valo, kTRUE);

  // "fGroupFrame570" group frame
  TGGroupFrame *Metodo = new TGGroupFrame(fMainFrame1600,"fGroupFrame570",kVerticalFrame,uGC->GetGC());
  TGRadioButton *Jacobi = new TGRadioButton(Metodo,"fTextButton704");
  Jacobi->SetTextJustify(36);
  Jacobi->SetMargins(0,0,0,0);
  Jacobi->SetWrapLength(-1);
  Metodo->AddFrame(Jacobi, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  TGRadioButton *GaussSeidel = new TGRadioButton(Metodo,"fTextButton711");
  GaussSeidel->SetTextJustify(36);
  GaussSeidel->SetMargins(0,0,0,0);
  GaussSeidel->SetWrapLength(-1);
  Metodo->AddFrame(GaussSeidel, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  TGRadioButton *SOR = new TGRadioButton(Metodo,"fTextButton739");
  SOR->SetTextJustify(36);
  SOR->SetMargins(0,0,0,0);
  SOR->SetWrapLength(-1);
  Metodo->AddFrame(SOR, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

  Metodo->SetLayoutManager(new TGVerticalLayout(Metodo));
  Metodo->Resize(128,88);
  fMainFrame1600->AddFrame(Metodo, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  Metodo->MoveResize(176,224,128,88);

  // "fGroupFrame880" group frame
  TGGroupFrame *Dati = new TGGroupFrame(fMainFrame1600,"fGroupFrame880");

  Dati->SetLayoutManager(new TGVerticalLayout(Dati));
  Dati->Resize(143,72);
  fMainFrame1600->AddFrame(Dati, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  Dati->MoveResize(16,232,143,72);

  // embedded canvas
  TRootEmbeddedCanvas *fRootEmbeddedCanvas1319 = new TRootEmbeddedCanvas(0,fMainFrame1600,456,192);
  fRootEmbeddedCanvas1319->SetName("fRootEmbeddedCanvas1319");
  Int_t wfRootEmbeddedCanvas1319 = fRootEmbeddedCanvas1319->GetCanvasWindowId();
  TCanvas *c124 = new TCanvas("c124", 10, 10, wfRootEmbeddedCanvas1319);
  fRootEmbeddedCanvas1319->AdoptCanvas(c124);
  fMainFrame1600->AddFrame(fRootEmbeddedCanvas1319, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  fRootEmbeddedCanvas1319->MoveResize(16,8,456,192);
  TGHProgressBar *fHProgressBar1337 = new TGHProgressBar(fMainFrame1600 ,176);
  fHProgressBar1337->SetName("fHProgressBar1337")
  fHProgressBar1337->SetFillType(TGProgressBar::kBlockFill);
  fHProgressBar1337->ChangeOptions(kSunkenFrame | kDoubleBorder | kOwnBackground);

  ULong_t ucolor;        // will reflect user color changes
  gClient->GetColorByName("#ffffff",ucolor);
  fHProgressBar1337->SetBackgroundColor(ucolor);
  fHProgressBar1337->SetPosition(25);
  fMainFrame1600->AddFrame(fHProgressBar1337, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  fHProgressBar1337->MoveResize(288,336,176,24);

  fMainFrame1600->SetMWMHints(kMWMDecorAll,
			      kMWMFuncAll,
			      kMWMInputModeless);
  fMainFrame1600->MapSubwindows();

  fMainFrame1600->Resize(fMainFrame1600->GetDefaultSize());
  fMainFrame1600->MapWindow();
  fMainFrame1600->Resize(490,372);
}  
