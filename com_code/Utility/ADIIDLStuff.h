//Mac shared
#ifndef ADIIDLSTUFF_H
#define ADIIDLSTUFF_H

//The ADIIDL IDL post-processor inserts this file at the start of every  MIDL
//generated .h file.


//LC7.3.2 pasted contents of "utility/compiler.h" into "globalsettings\pcheaders\globaldefinesnowin.h"
//#ifndef ADI_compiler_h
//#include "compiler.h"
//#endif

#include "unknwn.h"
#include "ocidl.h"

//We use std::numeric_limits<>::max() below, so old C style #defines of max are bad!
#undef max
#undef min

#include <limits> //for std::numeric_limits<PosType>::max()


#define _IFUNC STDMETHODCALLTYPE
#define _ICLASS

#if ( __BORLANDC__ && __BORLANDC__ < 0x540)
#define DECLSPEC_UUID(x)
#define EXTERN_GUID(itf,l1,s1,s2,c1,c2,c3,c4,c5,c6,c7,c8) EXTERN_C const IID itf
#endif

// Microsoft define a macro for "interface" in ObjBase.h and BaseTyps.h. Objective-C has "interface" as 
// a reserved word, and it is very painful to work with mixed Objective-C and COM code. It is attractive
// to avoid used of a macro and have a typedef for (say) Interface, but that fails in two ways:
//    typedef struct Interface;
//    typedef Interface IBinInStream IBinInStream; // Can work around this breakage in MIDL generated files
//    Interface IFoo;// Does not compile in gcc and no sensible work-around
// We could use a macro for Interface, but that is close to where we started and clashes with
// code in at least COMIArray.h, so bite the bullet and make it UGLY like macros should be!
// (A simple work-around for ALLCAPS is to simply use struct in code!)
#define COMINTERFACE struct

#if defined(__cplusplus) 


//these are used by ADI::COMPtr<>
//template <class I> const IID& uuidof(I*)  { return I::uuidof();}
//template <class I> const IID& uuidof(I**) { return I::uuidof();}

template <typename I> struct COMType
{
static const IID& uuidof() { return I::uuidof();}
};

template <typename I> const IID& uuidof(I*) { return COMType<I>::uuidof();}

template <typename I> const IID& uuidof(I**) { return COMType<I>::uuidof();}

#define DEFINE_UUIDOF(Interface) template<> \
struct COMType<Interface>{ static const IID& uuidof() {return IID_##Interface;} };
#define DEFINE_UUIDOFMSC(Interface) template<> \
struct COMType<Interface>{ static const IID& uuidof() {return __uuidof(Interface);} };

DEFINE_UUIDOF(IUnknown)
#if !defined (ADI_DISABLE_WIN32)	// Do not want/need these on Mac at moment
DEFINE_UUIDOF(IDispatch)
DEFINE_UUIDOF(IConnectionPoint)
DEFINE_UUIDOF(IConnectionPointContainer)
DEFINE_UUIDOF(IClassFactory)
#endif

#include "Utility/GlobalDefinesPortable.h"  //portable
#include "Utility/CrossTypes.h" //pure
#include "ADIBaseTypes.h"
#include "ADICOMPtr.h"


namespace ADI 
{ 
template <typename IEnum> 
struct EnumXXXTraits
{
typedef int32 PosType; //default position type
};

namespace EnumImpl
   {
   template<typename T> 
   inline void copyPOD(T *start, T *end, T *dest)
      {
      memcpy(dest, start, (end-start)*sizeof(T));
      }
   template<typename T> 
   inline void releasePOD(T * /*start*/, T * /*end*/) {};
   
   
   template<typename I>
   inline void copyCOM(I **start, I **end, I **dest)
      {
      for(;start!=end;++start)
         {
         *dest = *start;
         (*dest++)->AddRef();
         }
      }
   template<typename I>   
   inline void releaseCOM(I **start, I **end)
      {
      for(;start!=end;++start)
         (*start)->Release();
      } 
   }
} //namespace


#endif   //defined(__cplusplus) 

#if defined(__cplusplus) 
#define DEFINE_ENUMXXXTYPE(xxx) } \
namespace ADI { template<> struct EnumXXXTraits<IEnum##xxx> { \
typedef IEnum##xxx IEnum;\
typedef IEnum TCloneBase;\
typedef xxx XXXType; \
typedef int32 PosType; \
static void release(XXXType *start, XXXType *end){EnumImpl::releasePOD(start,end);} \
static void copy(XXXType *start, XXXType *end, XXXType *dest) {EnumImpl::copyPOD(start,end,dest);} \
static bool IsEnumEx() { return false;} \
static HRESULT GetPosition(IEnum *, PosType *pos){*pos = 0; ; return E_NOTIMPL;} \
static HRESULT Next(IEnum *enumI,TEnumCount nReq,XXXType *buf,TEnumCount *nRet){return enumI->Next(nReq,buf,nRet);}\
}; } extern "C" {
#else
#define DEFINE_ENUMXXXTYPE(xxx)
#endif

#if defined(__cplusplus) 
#define DEFINE_ENUMXXXPTRTYPE(xxx) } \
namespace ADI { template<> struct EnumXXXTraits<IEnum##xxx> { \
typedef IEnum##xxx IEnum;\
typedef IEnum TCloneBase;\
typedef xxx* XXXType; \
typedef int32 PosType; \
static void release(XXXType* start, XXXType* end){EnumImpl::releaseCOM(start,end);} \
static void copy(XXXType *start, XXXType *end, XXXType *dest){EnumImpl::copyCOM(start,end,dest);} \
static bool IsEnumEx() { return false;} \
static HRESULT GetPosition(IEnum *, PosType *pos){*pos = 0; ; return E_NOTIMPL;} \
static HRESULT Next(IEnum *enumI,TEnumCount nReq,XXXType *buf,TEnumCount *nRet){return enumI->Next(nReq,buf,nRet);}\
}; } extern "C" {
#else
#define DEFINE_ENUMXXXPTRTYPE(xxx)
#endif

#if defined(__cplusplus) 
#define DEFINE_ENUMXXXPTRTYPE2(ienum,ixxx) } \
namespace ADI { template<> struct EnumXXXTraits<ienum> { \
typedef ienum IEnum;\
typedef IEnum TCloneBase;\
typedef ixxx* XXXType; \
typedef int32 PosType; \
static void release(XXXType* start, XXXType* end){EnumImpl::releaseCOM(start,end);} \
static void copy(XXXType *start, XXXType *end, XXXType *dest){EnumImpl::copyCOM(start,end,dest);} \
static bool IsEnumEx() { return false;} \
static HRESULT GetPosition(IEnum *, PosType *pos){*pos = 0; ; return E_NOTIMPL;} \
static HRESULT Next(IEnum *enumI,TEnumCount nReq,XXXType *buf,TEnumCount *nRet){return enumI->Next(nReq,buf,nRet);}\
}; } extern "C" {
#else
#define DEFINE_ENUMXXXPTRTYPE2(ienum,ixxx)
#endif


#if defined(__cplusplus) 
#define DEFINE_ENUMXXXEXTYPE(xxx) } \
namespace ADI { template<> struct EnumXXXTraits<IEnum##xxx##Ex> { \
typedef IEnum##xxx##Ex IEnum;\
typedef IEnum TCloneBase;\
typedef xxx XXXType; \
typedef TTickIndex PosType; \
static void release(XXXType *start, XXXType *end){EnumImpl::releasePOD(start,end);} \
static void copy(XXXType *start, XXXType *end, XXXType *dest) {EnumImpl::copyPOD(start,end,dest);} \
static bool IsEnumEx() { return true;} \
static HRESULT GetPosition(IEnum *enumEx, PosType *pos){ return enumEx->GetPosition(pos);} \
static HRESULT Next(IEnum *enumI,TEnumCount nReq,XXXType *buf,TEnumCount *nRet){return enumI->Next(nReq,buf,nRet);}\
}; } extern "C" {
#else
#define DEFINE_ENUMXXXEXTYPE(xxx)
#endif

#if defined(__cplusplus) 
#define DEFINE_ENUMXXXEXTYPE2(ienum,xxx) } \
namespace ADI { template<> struct EnumXXXTraits<ienum> { \
typedef ienum IEnum;\
typedef IEnum TCloneBase;\
typedef xxx XXXType; \
typedef TTickIndex PosType; \
static void release(XXXType *start, XXXType *end){EnumImpl::releasePOD(start,end);} \
static void copy(XXXType *start, XXXType *end, XXXType *dest) {EnumImpl::copyPOD(start,end,dest);} \
static bool IsEnumEx() { return true;} \
static HRESULT GetPosition(IEnum *enumEx, PosType *pos){ return enumEx->GetPosition(pos);} \
static HRESULT Next(IEnum *enumI,TEnumCount nReq,XXXType *buf,TEnumCount *nRet){return enumI->Next(nReq,buf,nRet);}\
}; } extern "C" {
#else
#define DEFINE_ENUMXXXEXTYPE2(ienum,xxx)
#endif

#if defined(__cplusplus) 
#define DEFINE_ENUMXXXEXTYPE3(ienum,xxx,postype) } \
   namespace ADI { template<> struct EnumXXXTraits<ienum> { \
   typedef ienum IEnum;\
   typedef IEnumEx64Base TCloneBase;\
   typedef xxx XXXType; \
   typedef postype PosType; \
   static void release(XXXType *start, XXXType *end){EnumImpl::releasePOD(start,end);} \
   static void copy(XXXType *start, XXXType *end, XXXType *dest) {EnumImpl::copyPOD(start,end,dest);} \
   static bool IsEnumEx() { return true;} \
   static HRESULT GetPosition(IEnum *enumEx, PosType *pos){ return enumEx->GetPosition(pos);} \
   static HRESULT Next(IEnum *enumI,TEnumCount nReq,XXXType *buf,TEnumCount *nRet){return enumI->Next(nReq,buf,nRet);}\
   }; } extern "C" {
#else
#define DEFINE_ENUMXXXEXTYPE3(ienum,xxx,postype)
#endif


#if defined(__cplusplus) 
#define DEFINE_ENUMXXXPTREXTYPE(xxx) } \
namespace ADI { template<> struct EnumXXXTraits<IEnum##xxx##Ex> { \
typedef IEnum##xxx##Ex IEnum;\
typedef IEnum TCloneBase;\
typedef xxx* XXXType; \
typedef int32 PosType; \
static void release(XXXType* start, XXXType* end){EnumImpl::releaseCOM(start,end);} \
static void copy(XXXType *start, XXXType *end, XXXType *dest){EnumImpl::copyCOM(start,end,dest);} \
static bool IsEnumEx() { return true;} \
static HRESULT GetPosition(IEnum *enumEx, PosType *pos){ return enumEx->GetPosition(pos);} \
static HRESULT Next(IEnum *enumI,TEnumCount nReq,XXXType *buf,TEnumCount *nRet){return enumI->Next(nReq,buf,nRet);}\
}; } extern "C" {
#else
#define DEFINE_ENUMXXXPTREXTYPE(xxx)
#endif

#if defined(__cplusplus) 
#define DEFINE_ENUMXXXPTREXTYPE2(ienum,xxx) } \
namespace ADI { template<> struct EnumXXXTraits<ienum> { \
typedef ienum IEnum;\
typedef IEnum TCloneBase;\
typedef xxx* XXXType; \
typedef TTickIndex PosType; \
static void release(XXXType* start, XXXType* end){EnumImpl::releaseCOM(start,end);} \
static void copy(XXXType *start, XXXType *end, XXXType *dest){EnumImpl::copyCOM(start,end,dest);} \
static bool IsEnumEx() { return true;} \
static HRESULT GetPosition(IEnum *enumEx, PosType *pos){ return enumEx->GetPosition(pos);} \
static HRESULT Next(IEnum *enumI,TEnumCount nReq,XXXType *buf,TEnumCount *nRet){return enumI->Next(nReq,buf,nRet);}\
}; } extern "C" {
#else
#define DEFINE_ENUMXXXPTREXTYPE2(ienum,xxx)
#endif

#if defined(__cplusplus) 
#define DEFINE_ENUMXXXPIXEXTYPE(xxx,Xxx) } \
namespace ADI { template<> struct EnumXXXTraits<IEnum##Xxx##PixEx> { \
typedef IEnum##Xxx##PixEx IEnum;\
typedef IEnum TCloneBase;\
typedef xxx XXXType; \
typedef TPixIndex PosType; \
static void release(XXXType *start, XXXType *end){EnumImpl::releasePOD(start,end);} \
static void copy(XXXType *start, XXXType *end, XXXType *dest) {EnumImpl::copyPOD(start,end,dest);} \
static bool IsEnumEx() { return true;} \
static HRESULT GetPosition(IEnum *enumEx, PosType *pos){ return enumEx->GetPosition(pos);} \
static HRESULT Next(IEnum *enumI,TEnumCount nReq,XXXType *buf,TEnumCount *nRet){return enumI->Next(nReq,buf,nRet);}\
}; } extern "C" { 
#else
#define DEFINE_ENUMXXXPIXEXTYPE(xxx,Xxx)
#endif

#if defined(__cplusplus) 
#define DEFINE_ENUMCOMMENTPTRTYPE2(ienum,xxx) } \
namespace ADI { template<> struct EnumXXXTraits<ienum> {\
typedef ienum IEnum;\
typedef IEnum TCloneBase;\
typedef xxx* XXXType; \
typedef TTickIndex PosType; \
static void release(XXXType* start, XXXType* end){EnumImpl::releaseCOM(start,end);} \
static void copy(XXXType *start, XXXType *end, XXXType *dest){EnumImpl::copyCOM(start,end,dest);} \
static bool IsEnumEx() { return false;} \
static HRESULT GetPosition(IEnum *enumEx, PosType *pos){*pos = 0; ; return E_NOTIMPL;}\
HRESULT Next(IEnum *enumI,TEnumCount nReq,XXXType *buf,TEnumCount *nRet){return enumI->Next(nReq,mEndPos,buf,nRet);}\
EnumXXXTraits() : mEndPos(std::numeric_limits<PosType>::max()) {} \
void SetEndLimit(PosType endPos) { mEndPos = endPos;} \
protected: \
PosType mEndPos; \
}; } extern "C" {
#else
#define DEFINE_ENUMCOMMENTPTRTYPE2(ienum,xxx)
#endif



/* Additional suppression to avoid multiline comment warning when compiling with gcc -Wall
//#define DEFINE_ENUMXXXPIXEXTYPE(xxx,Xxx)  \
//typedef interface IEnum##Xxx##PixEx IEnum##Xxx##PixEx; \
//namespace ADI { template<> struct EnumXXXTraits<IEnum##Xxx##PixEx> { \
//typedef xxx XXXType; \
//}; }
*/


/* Additional suppression to avoid multiline comment warning when compiling with gcc -Wall
//namespace ADI { template <typename IEnum> struct EnumXXXTraits; }
////{
////typedef IEnum::XXXType XXXType;
////};
//
////template<> struct EnumXXXType<IEnumShort> { typedef short XXXType; };
////template<> struct EnumXXXType<IEnumLong> { typedef long XXXType; };
////template<> struct EnumXXXType<IEnumFloat> { typedef float XXXType; };
////template<> struct EnumXXXType<IEnumDouble> { typedef double XXXType; };
////
////template<> struct EnumXXXType<IEnumShortEx> { typedef short XXXType; };
////template<> struct EnumXXXType<IEnumLongEx> { typedef long XXXType; };
////template<> struct EnumXXXType<IEnumFloatEx> { typedef float XXXType; };
////template<> struct EnumXXXType<IEnumDoubleEx> { typedef double XXXType; };
//
//#define DEFINE_ENUMXXXTYPE(xxx) \
//typedef interface IEnum##xxx IEnum##xxx; \
//namespace ADI { template<> struct EnumXXXTraits<IEnum##xxx> { typedef xxx XXXType; }; }
//
//#define DEFINE_ENUMXXXPTRTYPE(xxx) \
//typedef interface IEnum##xxx IEnum##xxx; \
//namespace ADI { template<> struct EnumXXXTraits<IEnum##xxx> { typedef xxx##* XXXType; }; }
//
//#define DEFINE_ENUMXXXEXTYPE(xxx)  \
//typedef interface IEnum##xxx##Ex IEnum##xxx##Ex; \
//namespace ADI { template<> struct EnumXXXTraits<IEnum##xxx##Ex> { typedef xxx XXXType; }; }
//
//#define DEFINE_ENUMXXXPTREXTYPE(xxx)  \
//typedef interface IEnum##xxx##Ex IEnum##xxx##Ex; \
//namespace ADI { template<> struct EnumXXXTraits<IEnum##xxx##Ex> { typedef xxx##* XXXType; }; }
*/



//Usage:
//DEFINE_ENUMXXXTYPE(FORMATETC)


#endif
