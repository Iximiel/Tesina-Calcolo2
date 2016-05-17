//
// File generated by rootcint at Thu Dec 24 20:07:50 2015

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME GuiPDEDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "GuiPDEDict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"

// Direct notice to TROOT of the dictionary's loading.
namespace {
   static struct DictInit {
      DictInit() {
         ROOT::RegisterModule();
      }
   } __TheDictionaryInitializer;
}

// START OF SHADOWS

namespace ROOTShadow {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOTShadow
// END OF SHADOWS

namespace ROOTDict {
   void PDEGui_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void delete_PDEGui(void *p);
   static void deleteArray_PDEGui(void *p);
   static void destruct_PDEGui(void *p);

   // Function generating the singleton type initializer
   static ROOT::TGenericClassInfo *GenerateInitInstanceLocal(const ::PDEGui*)
   {
      ::PDEGui *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PDEGui >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PDEGui", ::PDEGui::Class_Version(), "./GuiPDE.hpp", 23,
                  typeid(::PDEGui), ::ROOT::DefineBehavior(ptr, ptr),
                  &::PDEGui::Dictionary, isa_proxy, 4,
                  sizeof(::PDEGui) );
      instance.SetDelete(&delete_PDEGui);
      instance.SetDeleteArray(&deleteArray_PDEGui);
      instance.SetDestructor(&destruct_PDEGui);
      return &instance;
   }
   ROOT::TGenericClassInfo *GenerateInitInstance(const ::PDEGui*)
   {
      return GenerateInitInstanceLocal((::PDEGui*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PDEGui*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOTDict

//______________________________________________________________________________
atomic_TClass_ptr PDEGui::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEGui::Class_Name()
{
   return "PDEGui";
}

//______________________________________________________________________________
const char *PDEGui::ImplFileName()
{
   return ::ROOTDict::GenerateInitInstanceLocal((const ::PDEGui*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEGui::ImplFileLine()
{
   return ::ROOTDict::GenerateInitInstanceLocal((const ::PDEGui*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void PDEGui::Dictionary()
{
   fgIsA = ::ROOTDict::GenerateInitInstanceLocal((const ::PDEGui*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *PDEGui::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gCINTMutex); if(!fgIsA) {fgIsA = ::ROOTDict::GenerateInitInstanceLocal((const ::PDEGui*)0x0)->GetClass();} }
   return fgIsA;
}

//______________________________________________________________________________
void PDEGui::Streamer(TBuffer &R__b)
{
   // Stream an object of class PDEGui.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PDEGui::Class(),this);
   } else {
      R__b.WriteClassBuffer(PDEGui::Class(),this);
   }
}

//______________________________________________________________________________
void PDEGui::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class PDEGui.
      TClass *R__cl = ::PDEGui::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*myPDE", &myPDE);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*grafo", &grafo);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*ECanvas", &ECanvas);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*childCanvas", &childCanvas);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*GroupMetodo", &GroupMetodo);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*Methods", &Methods);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*BtStart", &BtStart);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*BtExit", &BtExit);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*numPowPrec", &numPowPrec);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*numPlateDist", &numPlateDist);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*numPlateLenght", &numPlateLenght);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*numH", &numH);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*numW", &numW);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*numSOR", &numSOR);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*numHmm", &numHmm);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*numWmm", &numWmm);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*StatusBar", &StatusBar);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*PBprecision", &PBprecision);
      TGMainFrame::ShowMembers(R__insp);
}

namespace ROOTDict {
   // Wrapper around operator delete
   static void delete_PDEGui(void *p) {
      delete ((::PDEGui*)p);
   }
   static void deleteArray_PDEGui(void *p) {
      delete [] ((::PDEGui*)p);
   }
   static void destruct_PDEGui(void *p) {
      typedef ::PDEGui current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOTDict for class ::PDEGui

/********************************************************
* GuiPDEDict.cpp
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableGuiPDEDict();

extern "C" void G__set_cpp_environmentGuiPDEDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("GuiPDE.hpp");
  G__cpp_reset_tagtableGuiPDEDict();
}
#include <new>
extern "C" int G__cpp_dllrevGuiPDEDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* PDEGui */
static int G__GuiPDEDict_386_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) PDEGui::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GuiPDEDict_386_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) PDEGui::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GuiPDEDict_386_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) PDEGui::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GuiPDEDict_386_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      PDEGui::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GuiPDEDict_386_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((PDEGui*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GuiPDEDict_386_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) PDEGui::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GuiPDEDict_386_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) PDEGui::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GuiPDEDict_386_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) PDEGui::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GuiPDEDict_386_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) PDEGui::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GuiPDEDict_386_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   PDEGui* p = NULL;
   char* gvp = (char*) G__getgvp();
   //m: 4
   if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
     p = new PDEGui(
(TGWindow*) G__int(libp->para[0]), (int) G__int(libp->para[1])
, (int) G__int(libp->para[2]), (PDECond*) G__int(libp->para[3]));
   } else {
     p = new((void*) gvp) PDEGui(
(TGWindow*) G__int(libp->para[0]), (int) G__int(libp->para[1])
, (int) G__int(libp->para[2]), (PDECond*) G__int(libp->para[3]));
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GuiPDEDict_386_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((PDEGui*) G__getstructoffset())->exit();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GuiPDEDict_386_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((PDEGui*) G__getstructoffset())->doCalc();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef PDEGui G__TPDEGui;
static int G__GuiPDEDict_386_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 1
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (PDEGui*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((PDEGui*) (soff+(sizeof(PDEGui)*i)))->~G__TPDEGui();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (PDEGui*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((PDEGui*) (soff))->~G__TPDEGui();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* PDEGui */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncGuiPDEDict {
 public:
  G__Sizep2memfuncGuiPDEDict(): p(&G__Sizep2memfuncGuiPDEDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncGuiPDEDict::*p)();
};

size_t G__get_sizep2memfuncGuiPDEDict()
{
  G__Sizep2memfuncGuiPDEDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceGuiPDEDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui))) {
     PDEGui *G__Lderived;
     G__Lderived=(PDEGui*)0x1000;
     {
       TGMainFrame *G__Lpbase=(TGMainFrame*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui),G__get_linked_tagnum(&G__GuiPDEDictLN_TGMainFrame),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
     {
       TGCompositeFrame *G__Lpbase=(TGCompositeFrame*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui),G__get_linked_tagnum(&G__GuiPDEDictLN_TGCompositeFrame),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
     {
       TGFrame *G__Lpbase=(TGFrame*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui),G__get_linked_tagnum(&G__GuiPDEDictLN_TGFrame),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
     {
       TGWindow *G__Lpbase=(TGWindow*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui),G__get_linked_tagnum(&G__GuiPDEDictLN_TGWindow),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
     {
       TGObject *G__Lpbase=(TGObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui),G__get_linked_tagnum(&G__GuiPDEDictLN_TGObject),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui),G__get_linked_tagnum(&G__GuiPDEDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
     {
       TQObject *G__Lpbase=(TQObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui),G__get_linked_tagnum(&G__GuiPDEDictLN_TQObject),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableGuiPDEDict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GuiPDEDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GuiPDEDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GuiPDEDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GuiPDEDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("pair<UInt_t,Int_t>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_pairlEunsignedsPintcOintgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<std::pair<UInt_t,Int_t> >",117,G__get_linked_tagnum(&G__GuiPDEDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<pair<UInt_t,Int_t> >",117,G__get_linked_tagnum(&G__GuiPDEDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GuiPDEDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GuiPDEDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<pair<unsigned int,int> >",117,G__get_linked_tagnum(&G__GuiPDEDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<std::bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long,const TObject**>",117,G__get_linked_tagnum(&G__GuiPDEDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* PDEGui */
static void G__setup_memvarPDEGui(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui));
   { PDEGui *p; p=(PDEGui*)0x1000; if (p) { }
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TClass),G__defined_typename("atomic_TClass_ptr"),-2,4,"fgIsA=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_PDECond),-1,-1,4,"myPDE=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGraph2D),-1,-1,4,"grafo=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TRootEmbeddedCanvas),-1,-1,4,"ECanvas=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TCanvas),-1,-1,4,"childCanvas=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGButtonGroup),-1,-1,4,"GroupMetodo=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,2,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGRadioButton),-1,-1,4,"Methods=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGTextButton),-1,-1,4,"BtStart=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGTextButton),-1,-1,4,"BtExit=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGNumberEntry),-1,-1,4,"numPowPrec=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGNumberEntry),-1,-1,4,"numPlateDist=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGNumberEntry),-1,-1,4,"numPlateLenght=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGNumberEntry),-1,-1,4,"numH=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGNumberEntry),-1,-1,4,"numW=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGNumberEntry),-1,-1,4,"numSOR=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGNumberEntry),-1,-1,4,"numHmm=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGNumberEntry),-1,-1,4,"numWmm=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGStatusBar),-1,-1,4,"StatusBar=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GuiPDEDictLN_TGVProgressBar),-1,-1,4,"PBprecision=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarGuiPDEDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncPDEGui(void) {
   /* PDEGui */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui));
   G__memfunc_setup("Class",502,G__GuiPDEDict_386_0_1, 85, G__get_linked_tagnum(&G__GuiPDEDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&PDEGui::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__GuiPDEDict_386_0_2, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&PDEGui::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__GuiPDEDict_386_0_3, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&PDEGui::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__GuiPDEDict_386_0_4, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&PDEGui::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__GuiPDEDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__GuiPDEDict_386_0_8, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - ClassDef_StreamerNVirtual_b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__GuiPDEDict_386_0_9, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&PDEGui::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__GuiPDEDict_386_0_10, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&PDEGui::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__GuiPDEDict_386_0_11, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&PDEGui::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__GuiPDEDict_386_0_12, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&PDEGui::DeclFileLine) ), 0);
   G__memfunc_setup("PDEGui",510,G__GuiPDEDict_386_0_13, 105, G__get_linked_tagnum(&G__GuiPDEDictLN_PDEGui), -1, 0, 4, 1, 1, 0, 
"U 'TGWindow' - 10 - p i - - 0 - w "
"i - - 0 - h U 'PDECond' - 0 - -", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("exit",442,G__GuiPDEDict_386_0_14, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("doCalc",582,G__GuiPDEDict_386_0_15, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetCanvas",904,(G__InterfaceMethod) NULL, 121, -1, -1, 0, 0, 1, 4, 0, "", "spazio superiore", (void*) NULL, 0);
   G__memfunc_setup("SetData",678,(G__InterfaceMethod) NULL, 121, -1, -1, 0, 0, 1, 4, 0, "", "spazio centrale", (void*) NULL, 0);
   G__memfunc_setup("SetStatus",944,(G__InterfaceMethod) NULL, 121, -1, -1, 0, 0, 1, 4, 0, "", "spazio inferiore e pulsanti", (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~PDEGui", 636, G__GuiPDEDict_386_0_19, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncGuiPDEDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {
}

static void G__cpp_setup_global2() {
}

static void G__cpp_setup_global3() {
}

static void G__cpp_setup_global4() {
}

static void G__cpp_setup_global5() {
}

static void G__cpp_setup_global6() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalGuiPDEDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
  G__cpp_setup_global2();
  G__cpp_setup_global3();
  G__cpp_setup_global4();
  G__cpp_setup_global5();
  G__cpp_setup_global6();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {
}

static void G__cpp_setup_func13() {
}

static void G__cpp_setup_func14() {
}

static void G__cpp_setup_func15() {
}

static void G__cpp_setup_func16() {
}

static void G__cpp_setup_func17() {
}

static void G__cpp_setup_func18() {
}

static void G__cpp_setup_func19() {
}

static void G__cpp_setup_func20() {
}

static void G__cpp_setup_func21() {
}

static void G__cpp_setup_func22() {
}

static void G__cpp_setup_func23() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcGuiPDEDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
  G__cpp_setup_func13();
  G__cpp_setup_func14();
  G__cpp_setup_func15();
  G__cpp_setup_func16();
  G__cpp_setup_func17();
  G__cpp_setup_func18();
  G__cpp_setup_func19();
  G__cpp_setup_func20();
  G__cpp_setup_func21();
  G__cpp_setup_func22();
  G__cpp_setup_func23();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__GuiPDEDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGObject = { "TGObject" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TQObject = { "TQObject" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGWindow = { "TGWindow" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_pairlEunsignedsPintcOintgR = { "pair<unsigned int,int>" , 115 , -1 };
G__linked_taginfo G__GuiPDEDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR = { "vector<pair<unsigned int,int>,allocator<pair<unsigned int,int> > >" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<pair<unsigned int,int>,allocator<pair<unsigned int,int> > >::iterator>" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGFrame = { "TGFrame" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGCompositeFrame = { "TGCompositeFrame" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR = { "iterator<bidirectional_iterator_tag,TObject*,long,const TObject**,const TObject*&>" , 115 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGTextButton = { "TGTextButton" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGMainFrame = { "TGMainFrame" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGButtonGroup = { "TGButtonGroup" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGRadioButton = { "TGRadioButton" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGNumberEntry = { "TGNumberEntry" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TCanvas = { "TCanvas" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TRootEmbeddedCanvas = { "TRootEmbeddedCanvas" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGVProgressBar = { "TGVProgressBar" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_PDECond = { "PDECond" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGStatusBar = { "TGStatusBar" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_TGraph2D = { "TGraph2D" , 99 , -1 };
G__linked_taginfo G__GuiPDEDictLN_PDEGui = { "PDEGui" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableGuiPDEDict() {
  G__GuiPDEDictLN_TClass.tagnum = -1 ;
  G__GuiPDEDictLN_TBuffer.tagnum = -1 ;
  G__GuiPDEDictLN_TMemberInspector.tagnum = -1 ;
  G__GuiPDEDictLN_TObject.tagnum = -1 ;
  G__GuiPDEDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__GuiPDEDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GuiPDEDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__GuiPDEDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GuiPDEDictLN_TGObject.tagnum = -1 ;
  G__GuiPDEDictLN_TQObject.tagnum = -1 ;
  G__GuiPDEDictLN_TGWindow.tagnum = -1 ;
  G__GuiPDEDictLN_pairlEunsignedsPintcOintgR.tagnum = -1 ;
  G__GuiPDEDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR.tagnum = -1 ;
  G__GuiPDEDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GuiPDEDictLN_TGFrame.tagnum = -1 ;
  G__GuiPDEDictLN_TGCompositeFrame.tagnum = -1 ;
  G__GuiPDEDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR.tagnum = -1 ;
  G__GuiPDEDictLN_TGTextButton.tagnum = -1 ;
  G__GuiPDEDictLN_TGMainFrame.tagnum = -1 ;
  G__GuiPDEDictLN_TGButtonGroup.tagnum = -1 ;
  G__GuiPDEDictLN_TGRadioButton.tagnum = -1 ;
  G__GuiPDEDictLN_TGNumberEntry.tagnum = -1 ;
  G__GuiPDEDictLN_TCanvas.tagnum = -1 ;
  G__GuiPDEDictLN_TRootEmbeddedCanvas.tagnum = -1 ;
  G__GuiPDEDictLN_TGVProgressBar.tagnum = -1 ;
  G__GuiPDEDictLN_PDECond.tagnum = -1 ;
  G__GuiPDEDictLN_TGStatusBar.tagnum = -1 ;
  G__GuiPDEDictLN_TGraph2D.tagnum = -1 ;
  G__GuiPDEDictLN_PDEGui.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableGuiPDEDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGObject);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TQObject);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGWindow);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_pairlEunsignedsPintcOintgR);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGFrame);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGCompositeFrame);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGTextButton);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGMainFrame);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGButtonGroup);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGRadioButton);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGNumberEntry);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TCanvas);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TRootEmbeddedCanvas);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGVProgressBar);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_PDECond);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGStatusBar);
   G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_TGraph2D);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__GuiPDEDictLN_PDEGui),sizeof(PDEGui),-1,323584,(char*)NULL,G__setup_memvarPDEGui,G__setup_memfuncPDEGui);
}
extern "C" void G__cpp_setupGuiPDEDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupGuiPDEDict()");
  G__set_cpp_environmentGuiPDEDict();
  G__cpp_setup_tagtableGuiPDEDict();

  G__cpp_setup_inheritanceGuiPDEDict();

  G__cpp_setup_typetableGuiPDEDict();

  G__cpp_setup_memvarGuiPDEDict();

  G__cpp_setup_memfuncGuiPDEDict();
  G__cpp_setup_globalGuiPDEDict();
  G__cpp_setup_funcGuiPDEDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncGuiPDEDict();
  return;
}
class G__cpp_setup_initGuiPDEDict {
  public:
    G__cpp_setup_initGuiPDEDict() { G__add_setup_func("GuiPDEDict",(G__incsetup)(&G__cpp_setupGuiPDEDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initGuiPDEDict() { G__remove_setup_func("GuiPDEDict"); }
};
G__cpp_setup_initGuiPDEDict G__cpp_setup_initializerGuiPDEDict;
