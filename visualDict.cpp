// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME visualDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
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
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "visual.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_Visual(void *p);
   static void deleteArray_Visual(void *p);
   static void destruct_Visual(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Visual*)
   {
      ::Visual *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Visual >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Visual", ::Visual::Class_Version(), "visual.hpp", 20,
                  typeid(::Visual), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Visual::Dictionary, isa_proxy, 4,
                  sizeof(::Visual) );
      instance.SetDelete(&delete_Visual);
      instance.SetDeleteArray(&deleteArray_Visual);
      instance.SetDestructor(&destruct_Visual);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Visual*)
   {
      return GenerateInitInstanceLocal((::Visual*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Visual*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Visual::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Visual::Class_Name()
{
   return "Visual";
}

//______________________________________________________________________________
const char *Visual::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Visual*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Visual::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Visual*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Visual::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Visual*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Visual::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Visual*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Visual::Streamer(TBuffer &R__b)
{
   // Stream an object of class Visual.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Visual::Class(),this);
   } else {
      R__b.WriteClassBuffer(Visual::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Visual(void *p) {
      delete ((::Visual*)p);
   }
   static void deleteArray_Visual(void *p) {
      delete [] ((::Visual*)p);
   }
   static void destruct_Visual(void *p) {
      typedef ::Visual current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Visual

namespace ROOT {
   static TClass *vectorlEcomplexlEdoublegRsPgR_Dictionary();
   static void vectorlEcomplexlEdoublegRsPgR_TClassManip(TClass*);
   static void *new_vectorlEcomplexlEdoublegRsPgR(void *p = 0);
   static void *newArray_vectorlEcomplexlEdoublegRsPgR(Long_t size, void *p);
   static void delete_vectorlEcomplexlEdoublegRsPgR(void *p);
   static void deleteArray_vectorlEcomplexlEdoublegRsPgR(void *p);
   static void destruct_vectorlEcomplexlEdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<complex<double> >*)
   {
      vector<complex<double> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<complex<double> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<complex<double> >", -2, "vector", 214,
                  typeid(vector<complex<double> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEcomplexlEdoublegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<complex<double> >) );
      instance.SetNew(&new_vectorlEcomplexlEdoublegRsPgR);
      instance.SetNewArray(&newArray_vectorlEcomplexlEdoublegRsPgR);
      instance.SetDelete(&delete_vectorlEcomplexlEdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEcomplexlEdoublegRsPgR);
      instance.SetDestructor(&destruct_vectorlEcomplexlEdoublegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<complex<double> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<complex<double> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEcomplexlEdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<complex<double> >*)0x0)->GetClass();
      vectorlEcomplexlEdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEcomplexlEdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEcomplexlEdoublegRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<complex<double> > : new vector<complex<double> >;
   }
   static void *newArray_vectorlEcomplexlEdoublegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<complex<double> >[nElements] : new vector<complex<double> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEcomplexlEdoublegRsPgR(void *p) {
      delete ((vector<complex<double> >*)p);
   }
   static void deleteArray_vectorlEcomplexlEdoublegRsPgR(void *p) {
      delete [] ((vector<complex<double> >*)p);
   }
   static void destruct_vectorlEcomplexlEdoublegRsPgR(void *p) {
      typedef vector<complex<double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<complex<double> >

namespace {
  void TriggerDictionaryInitialization_visualDict_Impl() {
    static const char* headers[] = {
"visual.hpp",
0
    };
    static const char* includePaths[] = {
"/home/iximiel/root/include",
"/home/iximiel/Documents/Computazionale2/Tesina-Calcolo2/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "visualDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$visual.hpp")))  Visual;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "visualDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "visual.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Visual", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("visualDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_visualDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_visualDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_visualDict() {
  TriggerDictionaryInitialization_visualDict_Impl();
}
