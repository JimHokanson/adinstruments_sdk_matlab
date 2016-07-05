

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

#ifndef __IADIDataSinkSource_midl_h__
#define __IADIDataSinkSource_midl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Utility/ADIIDLStuff.h"

/* Forward Declarations */ 

#ifndef __IADIChannelDataSource_FWD_DEFINED__
#define __IADIChannelDataSource_FWD_DEFINED__
typedef COMINTERFACE IADIChannelDataSource IADIChannelDataSource;
#endif 	/* __IADIChannelDataSource_FWD_DEFINED__ */


#ifndef __IADIDataSink_FWD_DEFINED__
#define __IADIDataSink_FWD_DEFINED__
typedef COMINTERFACE IADIDataSink IADIDataSink;
#endif 	/* __IADIDataSink_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "IADIDataTypes.h"
#include "IADIEnums.h"
#include "IADIComment.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IADIChannelDataSource_INTERFACE_DEFINED__
#define __IADIChannelDataSource_INTERFACE_DEFINED__

/* interface IADIChannelDataSource */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IADIChannelDataSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("994F05AB-520E-47de-8F17-7FF5C2046286")
    IADIChannelDataSource : public IUnknown
    {
    static const IID& uuidof() {return IID_IADIChannelDataSource;} //Inserted by ADIIDL post-processor

    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetChannelEnumShort( 
            TGenericFlags inputType,
            /* [in] */ TChanIndex chanIndex,
            /* [retval][out] */ IEnumShortEx **shortOut) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetChannelEnumFloat( 
            TGenericFlags inputType,
            /* [in] */ TChanIndex chanIndex,
            /* [retval][out] */ IEnumFloatEx **floatOut) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDataStreamEnum( 
            TGenericFlags inputType,
            /* [in] */ TChanIndex chanIndex,
            /* [in] */ REFIID iid,
            /* [retval][out] */ IUnknown **enumOut) const = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADIChannelDataSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IADIChannelDataSource * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IADIChannelDataSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IADIChannelDataSource * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetChannelEnumShort )( 
            IADIChannelDataSource * This,
            TGenericFlags inputType,
            /* [in] */ TChanIndex chanIndex,
            /* [retval][out] */ IEnumShortEx **shortOut);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetChannelEnumFloat )( 
            IADIChannelDataSource * This,
            TGenericFlags inputType,
            /* [in] */ TChanIndex chanIndex,
            /* [retval][out] */ IEnumFloatEx **floatOut);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDataStreamEnum )( 
            IADIChannelDataSource * This,
            TGenericFlags inputType,
            /* [in] */ TChanIndex chanIndex,
            /* [in] */ REFIID iid,
            /* [retval][out] */ IUnknown **enumOut);
        
        END_INTERFACE
    } IADIChannelDataSourceVtbl;

    COMINTERFACE IADIChannelDataSource
    {
        CONST_VTBL struct IADIChannelDataSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADIChannelDataSource_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IADIChannelDataSource_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IADIChannelDataSource_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IADIChannelDataSource_GetChannelEnumShort(This,inputType,chanIndex,shortOut)	\
    ( (This)->lpVtbl -> GetChannelEnumShort(This,inputType,chanIndex,shortOut) ) 

#define IADIChannelDataSource_GetChannelEnumFloat(This,inputType,chanIndex,floatOut)	\
    ( (This)->lpVtbl -> GetChannelEnumFloat(This,inputType,chanIndex,floatOut) ) 

#define IADIChannelDataSource_GetDataStreamEnum(This,inputType,chanIndex,iid,enumOut)	\
    ( (This)->lpVtbl -> GetDataStreamEnum(This,inputType,chanIndex,iid,enumOut) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IADIChannelDataSource_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_IADIDataSinkSource_0000_0001 */
/* [local] */ 

typedef 
enum ADIRecordFlags
    {	kADIRecordFlagsNil	= 0,
	kADIRecordFlagsFirstRecordedRecordInSamplingSession	= 0x20000000
    } 	ADIRecordFlags;



extern RPC_IF_HANDLE __MIDL_itf_IADIDataSinkSource_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IADIDataSinkSource_0000_0001_v0_0_s_ifspec;

#ifndef __IADIDataSink_INTERFACE_DEFINED__
#define __IADIDataSink_INTERFACE_DEFINED__

/* interface IADIDataSink */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IADIDataSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C594A482-908C-46fc-A106-F0E9417E75F3")
    IADIDataSink : public IUnknown
    {
    static const IID& uuidof() {return IID_IADIDataSink;} //Inserted by ADIIDL post-processor

    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetChannelName( 
            /* [in] */ ADIChannelId chanId,
            /* [in] */ CONST_BSTR name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetupChannel( 
            /* [in] */ ADIChannelId chanId,
            /* [in] */ AutoBool enabled,
            /* [in] */ double secsPerSample,
            /* [in] */ ADIDataValueId valueType,
            /* [in] */ CONST_BSTR baseUnitsName,
            /* [defaultvalue][in] */ const BaseUnitsInfo *baseInfo = 0,
            /* [defaultvalue][in] */ const UserUnitsInfo *userInfo = 0,
            /* [defaultvalue][in] */ CONST_BSTR userUnitsName = 0,
            /* [defaultvalue][in] */ const IUnknown *extraSettings = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLastErrorMsg( 
            TGenericFlags __MIDL__IADIDataSink0000,
            /* [out] */ HRESULT *lastErrorHr,
            /* [out] */ IAutoADIString **msg,
            /* [retval][out] */ IAutoADIString **caption) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CanSample( 
            /* [out] */ IAutoADIString **whyNot,
            /* [retval][out] */ AutoBool *canSample) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PrepareForSampling( 
            /* [in] */ TGenericFlags flags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnRecordStart( 
            /* [in] */ ADIRecordFlags recordFlags,
            /* [in] */ IUnknown *dataSrc,
            /* [in] */ ADITimeDate triggerTickTime,
            /* [in] */ hyper samplingTickAtRecordStart,
            /* [in] */ TTickIndex triggerMinusRecordStartTicks,
            /* [in] */ AutoBool recordMode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Update( 
            /* [in] */ TTickIndex newTicks) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnRecordEnd( 
            /* [in] */ TGenericFlags flags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CleanUpAfterSampling( 
            /* [in] */ AutoBool repaintData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnEvent( 
            /* [in] */ TCAFId eventId,
            /* [in] */ IUnknown *eventInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddComment( 
            ADIChannelId chanId,
            CONST_BSTR text,
            /* [defaultvalue][in] */ const ADIPosition *tickPos = 0,
            /* [defaultvalue][in] */ TCAFId cafid = 0,
            /* [defaultvalue][in] */ IADIComment **addedCommentOut = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveComment( 
            IADIComment *comment) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADIDataSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IADIDataSink * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IADIDataSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IADIDataSink * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetChannelName )( 
            IADIDataSink * This,
            /* [in] */ ADIChannelId chanId,
            /* [in] */ CONST_BSTR name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetupChannel )( 
            IADIDataSink * This,
            /* [in] */ ADIChannelId chanId,
            /* [in] */ AutoBool enabled,
            /* [in] */ double secsPerSample,
            /* [in] */ ADIDataValueId valueType,
            /* [in] */ CONST_BSTR baseUnitsName,
            /* [defaultvalue][in] */ const BaseUnitsInfo *baseInfo,
            /* [defaultvalue][in] */ const UserUnitsInfo *userInfo,
            /* [defaultvalue][in] */ CONST_BSTR userUnitsName,
            /* [defaultvalue][in] */ const IUnknown *extraSettings);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLastErrorMsg )( 
            IADIDataSink * This,
            TGenericFlags __MIDL__IADIDataSink0000,
            /* [out] */ HRESULT *lastErrorHr,
            /* [out] */ IAutoADIString **msg,
            /* [retval][out] */ IAutoADIString **caption);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CanSample )( 
            IADIDataSink * This,
            /* [out] */ IAutoADIString **whyNot,
            /* [retval][out] */ AutoBool *canSample);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PrepareForSampling )( 
            IADIDataSink * This,
            /* [in] */ TGenericFlags flags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnRecordStart )( 
            IADIDataSink * This,
            /* [in] */ ADIRecordFlags recordFlags,
            /* [in] */ IUnknown *dataSrc,
            /* [in] */ ADITimeDate triggerTickTime,
            /* [in] */ hyper samplingTickAtRecordStart,
            /* [in] */ TTickIndex triggerMinusRecordStartTicks,
            /* [in] */ AutoBool recordMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IADIDataSink * This,
            /* [in] */ TTickIndex newTicks);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnRecordEnd )( 
            IADIDataSink * This,
            /* [in] */ TGenericFlags flags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CleanUpAfterSampling )( 
            IADIDataSink * This,
            /* [in] */ AutoBool repaintData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnEvent )( 
            IADIDataSink * This,
            /* [in] */ TCAFId eventId,
            /* [in] */ IUnknown *eventInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddComment )( 
            IADIDataSink * This,
            ADIChannelId chanId,
            CONST_BSTR text,
            /* [defaultvalue][in] */ const ADIPosition *tickPos,
            /* [defaultvalue][in] */ TCAFId cafid,
            /* [defaultvalue][in] */ IADIComment **addedCommentOut);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveComment )( 
            IADIDataSink * This,
            IADIComment *comment);
        
        END_INTERFACE
    } IADIDataSinkVtbl;

    interface IADIDataSink
    {
        CONST_VTBL struct IADIDataSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADIDataSink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IADIDataSink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IADIDataSink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IADIDataSink_SetChannelName(This,chanId,name)	\
    ( (This)->lpVtbl -> SetChannelName(This,chanId,name) ) 

#define IADIDataSink_SetupChannel(This,chanId,enabled,secsPerSample,valueType,baseUnitsName,baseInfo,userInfo,userUnitsName,extraSettings)	\
    ( (This)->lpVtbl -> SetupChannel(This,chanId,enabled,secsPerSample,valueType,baseUnitsName,baseInfo,userInfo,userUnitsName,extraSettings) ) 

#define IADIDataSink_GetLastErrorMsg(This,__MIDL__IADIDataSink0000,lastErrorHr,msg,caption)	\
    ( (This)->lpVtbl -> GetLastErrorMsg(This,__MIDL__IADIDataSink0000,lastErrorHr,msg,caption) ) 

#define IADIDataSink_CanSample(This,whyNot,canSample)	\
    ( (This)->lpVtbl -> CanSample(This,whyNot,canSample) ) 

#define IADIDataSink_PrepareForSampling(This,flags)	\
    ( (This)->lpVtbl -> PrepareForSampling(This,flags) ) 

#define IADIDataSink_OnRecordStart(This,recordFlags,dataSrc,triggerTickTime,samplingTickAtRecordStart,triggerMinusRecordStartTicks,recordMode)	\
    ( (This)->lpVtbl -> OnRecordStart(This,recordFlags,dataSrc,triggerTickTime,samplingTickAtRecordStart,triggerMinusRecordStartTicks,recordMode) ) 

#define IADIDataSink_Update(This,newTicks)	\
    ( (This)->lpVtbl -> Update(This,newTicks) ) 

#define IADIDataSink_OnRecordEnd(This,flags)	\
    ( (This)->lpVtbl -> OnRecordEnd(This,flags) ) 

#define IADIDataSink_CleanUpAfterSampling(This,repaintData)	\
    ( (This)->lpVtbl -> CleanUpAfterSampling(This,repaintData) ) 

#define IADIDataSink_OnEvent(This,eventId,eventInfo)	\
    ( (This)->lpVtbl -> OnEvent(This,eventId,eventInfo) ) 

#define IADIDataSink_AddComment(This,chanId,text,tickPos,cafid,addedCommentOut)	\
    ( (This)->lpVtbl -> AddComment(This,chanId,text,tickPos,cafid,addedCommentOut) ) 

#define IADIDataSink_RemoveComment(This,comment)	\
    ( (This)->lpVtbl -> RemoveComment(This,comment) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IADIDataSink_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


