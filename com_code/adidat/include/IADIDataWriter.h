

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

#ifndef __IADIDataWriter_midl_h__
#define __IADIDataWriter_midl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Utility/ADIIDLStuff.h"

/* Forward Declarations */ 

#ifndef __IADIDataWriter_FWD_DEFINED__
#define __IADIDataWriter_FWD_DEFINED__
typedef COMINTERFACE IADIDataWriter IADIDataWriter;
#endif 	/* __IADIDataWriter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "IADIDataSinkSource.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_IADIDataWriter_0000_0000 */
/* [local] */ 

typedef 
enum ADIFileOpenFlags
    {	kADIOpenFileForReadOnly	= 0,
	kADIOpenFileForReadAndWrite	= 1,
	kADIWriteInADIDATFormat	= 0x80000000
    } 	ADIFileOpenFlags;




extern RPC_IF_HANDLE __MIDL_itf_IADIDataWriter_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IADIDataWriter_0000_0000_v0_0_s_ifspec;

#ifndef __IADIDataWriter_INTERFACE_DEFINED__
#define __IADIDataWriter_INTERFACE_DEFINED__

/* interface IADIDataWriter */
/* [unique][helpstring][uuid][oleautomation][local][object] */ 


EXTERN_C const IID IID_IADIDataWriter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F25E99EE-3AC0-4b3c-8CBD-7DF69A25280C")
    IADIDataWriter : public IUnknown
    {
    static const IID& uuidof() {return IID_IADIDataWriter;} //Inserted by ADIIDL post-processor

    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateADIFile( 
            /* [in] */ CONST_BSTR fileName,
            /* [in] */ ADIFileOpenFlags flags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetADIDataSink( 
            /* [retval][out] */ IADIDataSink **dataSink) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CommitFile( 
            /* [in] */ TGenericFlags flags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADIDataWriterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IADIDataWriter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IADIDataWriter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IADIDataWriter * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateADIFile )( 
            IADIDataWriter * This,
            /* [in] */ CONST_BSTR fileName,
            /* [in] */ ADIFileOpenFlags flags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetADIDataSink )( 
            IADIDataWriter * This,
            /* [retval][out] */ IADIDataSink **dataSink);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CommitFile )( 
            IADIDataWriter * This,
            /* [in] */ TGenericFlags flags);
        
        END_INTERFACE
    } IADIDataWriterVtbl;

    interface IADIDataWriter
    {
        CONST_VTBL struct IADIDataWriterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADIDataWriter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IADIDataWriter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IADIDataWriter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IADIDataWriter_CreateADIFile(This,fileName,flags)	\
    ( (This)->lpVtbl -> CreateADIFile(This,fileName,flags) ) 

#define IADIDataWriter_GetADIDataSink(This,dataSink)	\
    ( (This)->lpVtbl -> GetADIDataSink(This,dataSink) ) 

#define IADIDataWriter_CommitFile(This,flags)	\
    ( (This)->lpVtbl -> CommitFile(This,flags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IADIDataWriter_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


