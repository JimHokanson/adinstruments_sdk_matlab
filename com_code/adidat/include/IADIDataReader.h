

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

#ifndef __IADIDataReader_midl_h__
#define __IADIDataReader_midl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Utility/ADIIDLStuff.h"

/* Forward Declarations */ 

#ifndef __IADIDataReader_FWD_DEFINED__
#define __IADIDataReader_FWD_DEFINED__
typedef COMINTERFACE IADIDataReader IADIDataReader;
#endif 	/* __IADIDataReader_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "IADIData.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IADIDataReader_INTERFACE_DEFINED__
#define __IADIDataReader_INTERFACE_DEFINED__

/* interface IADIDataReader */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IADIDataReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("01C46A60-60EE-4c83-B53C-3B3357DBF4A6")
    IADIDataReader : public IUnknown
    {
    static const IID& uuidof() {return IID_IADIDataReader;} //Inserted by ADIIDL post-processor

    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpenFileForRead( 
            /* [in] */ CONST_BSTR fileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetADIData( 
            /* [retval][out] */ IADIData **retval) const = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADIDataReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IADIDataReader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IADIDataReader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IADIDataReader * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpenFileForRead )( 
            IADIDataReader * This,
            /* [in] */ CONST_BSTR fileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetADIData )( 
            IADIDataReader * This,
            /* [retval][out] */ IADIData **retval);
        
        END_INTERFACE
    } IADIDataReaderVtbl;

    interface IADIDataReader
    {
        CONST_VTBL struct IADIDataReaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADIDataReader_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IADIDataReader_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IADIDataReader_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IADIDataReader_OpenFileForRead(This,fileName)	\
    ( (This)->lpVtbl -> OpenFileForRead(This,fileName) ) 

#define IADIDataReader_GetADIData(This,retval)	\
    ( (This)->lpVtbl -> GetADIData(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IADIDataReader_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


