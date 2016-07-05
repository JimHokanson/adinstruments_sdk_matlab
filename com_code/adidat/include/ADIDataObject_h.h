

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Thu Mar 10 11:26:06 2016
 */
/* Compiler settings for .\ADIDataObject.idl:
    Oicf, W1, Zp8, env=Win64 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


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

#ifndef __ADIDataObject_h_h__
#define __ADIDataObject_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IADIDataClass_FWD_DEFINED__
#define __IADIDataClass_FWD_DEFINED__
typedef interface IADIDataClass IADIDataClass;
#endif 	/* __IADIDataClass_FWD_DEFINED__ */


#ifndef __ADIDataObject_FWD_DEFINED__
#define __ADIDataObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class ADIDataObject ADIDataObject;
#else
typedef struct ADIDataObject ADIDataObject;
#endif /* __cplusplus */

#endif 	/* __ADIDataObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "IADIDataSinkSource.h"
#include "IADIDataReader.h"
#include "IADIDataWriter.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IADIDataClass_INTERFACE_DEFINED__
#define __IADIDataClass_INTERFACE_DEFINED__

/* interface IADIDataClass */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IADIDataClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7747435B-9495-4ff0-958A-C3315300FB35")
    IADIDataClass : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ CONST_BSTR path,
            /* [retval][out] */ IADIDataReader **retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateNew( 
            /* [in] */ CONST_BSTR path,
            /* [in] */ long flags,
            /* [retval][out] */ IADIDataWriter **data) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetErrorMessage( 
            /* [in] */ HRESULT errorCode,
            /* [in] */ ADIReservedFlags flags,
            /* [retval][out] */ IAutoADIString **msg) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADIDataClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IADIDataClass * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IADIDataClass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IADIDataClass * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IADIDataClass * This,
            /* [in] */ CONST_BSTR path,
            /* [retval][out] */ IADIDataReader **retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateNew )( 
            IADIDataClass * This,
            /* [in] */ CONST_BSTR path,
            /* [in] */ long flags,
            /* [retval][out] */ IADIDataWriter **data);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetErrorMessage )( 
            IADIDataClass * This,
            /* [in] */ HRESULT errorCode,
            /* [in] */ ADIReservedFlags flags,
            /* [retval][out] */ IAutoADIString **msg);
        
        END_INTERFACE
    } IADIDataClassVtbl;

    interface IADIDataClass
    {
        CONST_VTBL struct IADIDataClassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADIDataClass_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IADIDataClass_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IADIDataClass_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IADIDataClass_Create(This,path,retval)	\
    ( (This)->lpVtbl -> Create(This,path,retval) ) 

#define IADIDataClass_CreateNew(This,path,flags,data)	\
    ( (This)->lpVtbl -> CreateNew(This,path,flags,data) ) 

#define IADIDataClass_GetErrorMessage(This,errorCode,flags,msg)	\
    ( (This)->lpVtbl -> GetErrorMessage(This,errorCode,flags,msg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IADIDataClass_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_ADIDataObject_0000_0001 */
/* [local] */ 

#ifdef __cplusplus
}
DEFINE_UUIDOF(IADIDataClass) //provide compiler independent uuidof() support
extern "C"{ 
#endif


extern RPC_IF_HANDLE __MIDL_itf_ADIDataObject_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ADIDataObject_0000_0001_v0_0_s_ifspec;


#ifndef __ADIDataLib_LIBRARY_DEFINED__
#define __ADIDataLib_LIBRARY_DEFINED__

/* library ADIDataLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ADIDataLib;

EXTERN_C const CLSID CLSID_ADIDataObject;

#ifdef __cplusplus

class DECLSPEC_UUID("90977FB0-D3B0-4e02-A549-1684E70C0B6A")
ADIDataObject;
#endif
#endif /* __ADIDataLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


