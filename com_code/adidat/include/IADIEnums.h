

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* Compiler settings:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

//#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __IADIEnums_midl_h__
#define __IADIEnums_midl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Utility/ADIIDLStuff.h"

/* Forward Declarations */ 

#ifndef __IEnumExBase_FWD_DEFINED__
#define __IEnumExBase_FWD_DEFINED__
typedef COMINTERFACE IEnumExBase IEnumExBase;
#endif 	/* __IEnumExBase_FWD_DEFINED__ */


#ifndef __IEnumShortEx_FWD_DEFINED__
#define __IEnumShortEx_FWD_DEFINED__
typedef COMINTERFACE IEnumShortEx IEnumShortEx;
#endif 	/* __IEnumShortEx_FWD_DEFINED__ */


#ifndef __IEnumFloatEx_FWD_DEFINED__
#define __IEnumFloatEx_FWD_DEFINED__
typedef COMINTERFACE IEnumFloatEx IEnumFloatEx;
#endif 	/* __IEnumFloatEx_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ADIBaseTypes.h"
#include "IADIDataTypes.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_IADIEnums_0000_0000 */
/* [local] */ 

typedef ADIRational TChanRateType;

#if defined(PUBLIC_OEM_UTIL) || !defined(__cplusplus)
#if !defined(__cplusplus)
typedef struct TTickToSample
    {
    TChanRateType mSamplesPerTick;
    double mSampleAtTickZero;
    } 	TTickToSample;

#else
struct TTickToSample  //This version does not depend on boost
{
TChanRateType mSamplesPerTick;
double mSampleAtTickZero;
explicit TTickToSample(TChanRateType samplesPerTick = 1, double sampleAtTickZero = 0) :
 mSamplesPerTick(samplesPerTick), mSampleAtTickZero(sampleAtTickZero) {}
double TickToSample(double tick) const
   {
   return tick*(static_cast<double>(mSamplesPerTick.num)/mSamplesPerTick.den)+mSampleAtTickZero;
   }
double SampleToTick(double sample) const
   {
   return (sample-mSampleAtTickZero)/(static_cast<double>(mSamplesPerTick.num)/mSamplesPerTick.den);
   }
};
#endif
#else
struct TTickToSample
{
TChanRateType mSamplesPerTick;
double mSampleAtTickZero;
explicit TTickToSample(TChanRateType samplesPerTick = 1, double sampleAtTickZero = 0) :
 mSamplesPerTick(samplesPerTick), mSampleAtTickZero(sampleAtTickZero) {}
double TickToSample(double tick) const
   {
   return tick*rational_cast<double>(mSamplesPerTick)+mSampleAtTickZero;
   }
double SampleToTick(double sample) const
   {
   return (sample-mSampleAtTickZero)/rational_cast<double>(mSamplesPerTick);
   }
void Resample(const TTickToSample &other)
   {
   mSamplesPerTick *= other.mSamplesPerTick;
   mSampleAtTickZero = mSampleAtTickZero * rational_cast<double>(other.mSamplesPerTick) + other.mSampleAtTickZero;
   }
void Resample(TChanRateType outSamplesPerInSample)
   {
   mSamplesPerTick *= outSamplesPerInSample;
   mSampleAtTickZero *= rational_cast<double>(outSamplesPerInSample);
   }
void Resample(double outSamplesPerInSample)
   {
   Resample(::ADI::gDoubleToTChanRateType(outSamplesPerInSample));
   }
};
#endif
typedef int32 Int32;

typedef uint64 UInt64;



extern RPC_IF_HANDLE __MIDL_itf_IADIEnums_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IADIEnums_0000_0000_v0_0_s_ifspec;

#ifndef __IEnumExBase_INTERFACE_DEFINED__
#define __IEnumExBase_INTERFACE_DEFINED__

/* interface IEnumExBase */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumExBase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F28FCF13-679E-444f-A6D2-F9BB2827B9F5")
    IEnumExBase : public IUnknown
    {
    static const IID& uuidof() {return IID_IEnumExBase;} //Inserted by ADIIDL post-processor

    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SkipEx( 
            /* [in] */ TTickIndex nToSkip,
            /* [retval][out] */ TTickIndex *nSkipped) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [retval][out] */ TTickIndex *nPos) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsFilling( 
            /* [retval][out] */ AutoBool *isFilling) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTickToSample( 
            /* [in] */ TTickToSample *tickToSample) const = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumExBaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumExBase * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumExBase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumExBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SkipEx )( 
            IEnumExBase * This,
            /* [in] */ TTickIndex nToSkip,
            /* [retval][out] */ TTickIndex *nSkipped);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumExBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPosition )( 
            IEnumExBase * This,
            /* [retval][out] */ TTickIndex *nPos);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsFilling )( 
            IEnumExBase * This,
            /* [retval][out] */ AutoBool *isFilling);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTickToSample )( 
            IEnumExBase * This,
            /* [in] */ TTickToSample *tickToSample);
        
        END_INTERFACE
    } IEnumExBaseVtbl;

    COMINTERFACE IEnumExBase
    {
        CONST_VTBL struct IEnumExBaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumExBase_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumExBase_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumExBase_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumExBase_SkipEx(This,nToSkip,nSkipped)	\
    ( (This)->lpVtbl -> SkipEx(This,nToSkip,nSkipped) ) 

#define IEnumExBase_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumExBase_GetPosition(This,nPos)	\
    ( (This)->lpVtbl -> GetPosition(This,nPos) ) 

#define IEnumExBase_IsFilling(This,isFilling)	\
    ( (This)->lpVtbl -> IsFilling(This,isFilling) ) 

#define IEnumExBase_GetTickToSample(This,tickToSample)	\
    ( (This)->lpVtbl -> GetTickToSample(This,tickToSample) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumExBase_INTERFACE_DEFINED__ */


#ifndef __IEnumShortEx_INTERFACE_DEFINED__
#define __IEnumShortEx_INTERFACE_DEFINED__

/* interface IEnumShortEx */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumShortEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B3D79151-302B-4597-AE36-79DF1E5ADA5F")
    IEnumShortEx : public IEnumExBase
    {
    static const IID& uuidof() {return IID_IEnumShortEx;} //Inserted by ADIIDL post-processor

    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ TEnumCount n,
            /* [length_is][size_is][out] */ short *out,
            /* [retval][out] */ TEnumCount *nRetd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumShortEx **retval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumShortExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumShortEx * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumShortEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumShortEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SkipEx )( 
            IEnumShortEx * This,
            /* [in] */ TTickIndex nToSkip,
            /* [retval][out] */ TTickIndex *nSkipped);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumShortEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPosition )( 
            IEnumShortEx * This,
            /* [retval][out] */ TTickIndex *nPos);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsFilling )( 
            IEnumShortEx * This,
            /* [retval][out] */ AutoBool *isFilling);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTickToSample )( 
            IEnumShortEx * This,
            /* [in] */ TTickToSample *tickToSample);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumShortEx * This,
            /* [in] */ TEnumCount n,
            /* [length_is][size_is][out] */ short *out,
            /* [retval][out] */ TEnumCount *nRetd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumShortEx * This,
            /* [retval][out] */ IEnumShortEx **retval);
        
        END_INTERFACE
    } IEnumShortExVtbl;

    COMINTERFACE IEnumShortEx
    {
        CONST_VTBL struct IEnumShortExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumShortEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumShortEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumShortEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumShortEx_SkipEx(This,nToSkip,nSkipped)	\
    ( (This)->lpVtbl -> SkipEx(This,nToSkip,nSkipped) ) 

#define IEnumShortEx_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumShortEx_GetPosition(This,nPos)	\
    ( (This)->lpVtbl -> GetPosition(This,nPos) ) 

#define IEnumShortEx_IsFilling(This,isFilling)	\
    ( (This)->lpVtbl -> IsFilling(This,isFilling) ) 

#define IEnumShortEx_GetTickToSample(This,tickToSample)	\
    ( (This)->lpVtbl -> GetTickToSample(This,tickToSample) ) 


#define IEnumShortEx_Next(This,n,out,nRetd)	\
    ( (This)->lpVtbl -> Next(This,n,out,nRetd) ) 

#define IEnumShortEx_Clone(This,retval)	\
    ( (This)->lpVtbl -> Clone(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumShortEx_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_IADIEnums_0000_0002 */
/* [local] */ 

 DEFINE_ENUMXXXEXTYPE2(IEnumShortEx,short) 


extern RPC_IF_HANDLE __MIDL_itf_IADIEnums_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IADIEnums_0000_0002_v0_0_s_ifspec;

#ifndef __IEnumFloatEx_INTERFACE_DEFINED__
#define __IEnumFloatEx_INTERFACE_DEFINED__

/* interface IEnumFloatEx */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumFloatEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4236EDC0-23A0-11d3-80CA-00A0C9E26433")
    IEnumFloatEx : public IEnumExBase
    {
    static const IID& uuidof() {return IID_IEnumFloatEx;} //Inserted by ADIIDL post-processor

    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ TEnumCount n,
            /* [length_is][size_is][out] */ float *out,
            /* [retval][out] */ TEnumCount *nRetd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumFloatEx **retval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumFloatExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumFloatEx * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumFloatEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumFloatEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SkipEx )( 
            IEnumFloatEx * This,
            /* [in] */ TTickIndex nToSkip,
            /* [retval][out] */ TTickIndex *nSkipped);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumFloatEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPosition )( 
            IEnumFloatEx * This,
            /* [retval][out] */ TTickIndex *nPos);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsFilling )( 
            IEnumFloatEx * This,
            /* [retval][out] */ AutoBool *isFilling);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTickToSample )( 
            IEnumFloatEx * This,
            /* [in] */ TTickToSample *tickToSample);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumFloatEx * This,
            /* [in] */ TEnumCount n,
            /* [length_is][size_is][out] */ float *out,
            /* [retval][out] */ TEnumCount *nRetd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumFloatEx * This,
            /* [retval][out] */ IEnumFloatEx **retval);
        
        END_INTERFACE
    } IEnumFloatExVtbl;

    interface IEnumFloatEx
    {
        CONST_VTBL struct IEnumFloatExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumFloatEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumFloatEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumFloatEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumFloatEx_SkipEx(This,nToSkip,nSkipped)	\
    ( (This)->lpVtbl -> SkipEx(This,nToSkip,nSkipped) ) 

#define IEnumFloatEx_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumFloatEx_GetPosition(This,nPos)	\
    ( (This)->lpVtbl -> GetPosition(This,nPos) ) 

#define IEnumFloatEx_IsFilling(This,isFilling)	\
    ( (This)->lpVtbl -> IsFilling(This,isFilling) ) 

#define IEnumFloatEx_GetTickToSample(This,tickToSample)	\
    ( (This)->lpVtbl -> GetTickToSample(This,tickToSample) ) 


#define IEnumFloatEx_Next(This,n,out,nRetd)	\
    ( (This)->lpVtbl -> Next(This,n,out,nRetd) ) 

#define IEnumFloatEx_Clone(This,retval)	\
    ( (This)->lpVtbl -> Clone(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumFloatEx_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_IADIEnums_0000_0003 */
/* [local] */ 

 DEFINE_ENUMXXXEXTYPE2(IEnumFloatEx,float) 


extern RPC_IF_HANDLE __MIDL_itf_IADIEnums_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IADIEnums_0000_0003_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


