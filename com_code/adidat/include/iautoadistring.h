

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

#ifndef __iautoadistring_midl_h__
#define __iautoadistring_midl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Utility/ADIIDLStuff.h"

/* Forward Declarations */ 

#ifndef __IAutoADIString_FWD_DEFINED__
#define __IAutoADIString_FWD_DEFINED__
typedef COMINTERFACE IAutoADIString IAutoADIString;
#endif 	/* __IAutoADIString_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"
#include "ADIBaseTypes.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAutoADIString_INTERFACE_DEFINED__
#define __IAutoADIString_INTERFACE_DEFINED__

/* interface IAutoADIString */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IAutoADIString;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3904AA0E-3E8D-11D1-997F-00C0DF492697")
    IAutoADIString : public IUnknown
    {
    static const IID& uuidof() {return IID_IAutoADIString;} //Inserted by ADIIDL post-processor

    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetBStr( 
            /* [in] */ CONST_BSTR bStr) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBStr( 
            /* [retval][out] */ BSTR *retval) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsEmpty( 
            /* [retval][out] */ AutoBool *retval) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLength( 
            /* [retval][out] */ TCount *retval) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsEqual( 
            /* [in] */ const IAutoADIString *other,
            /* [retval][out] */ AutoBool *retval) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsShared( 
            /* [retval][out] */ AutoBool *retval) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsStringRep( void) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CopyBytesFromFirstChar( 
            /* [in] */ long bufSizeBytes,
            /* [size_is][out] */ BYTE buf[  ]) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LengthAndCharSize( 
            /* [out] */ long *nChars,
            /* [out] */ long *charSize) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCapacity( 
            /* [retval][out] */ long *nChars) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateNewString( 
            /* [in] */ long capacity,
            /* [retval][out] */ IAutoADIString **newStr) const = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAutoADIStringVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAutoADIString * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAutoADIString * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAutoADIString * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetBStr )( 
            IAutoADIString * This,
            /* [in] */ CONST_BSTR bStr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBStr )( 
            IAutoADIString * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsEmpty )( 
            IAutoADIString * This,
            /* [retval][out] */ AutoBool *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLength )( 
            IAutoADIString * This,
            /* [retval][out] */ TCount *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsEqual )( 
            IAutoADIString * This,
            /* [in] */ const IAutoADIString *other,
            /* [retval][out] */ AutoBool *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsShared )( 
            IAutoADIString * This,
            /* [retval][out] */ AutoBool *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsStringRep )( 
            IAutoADIString * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CopyBytesFromFirstChar )( 
            IAutoADIString * This,
            /* [in] */ long bufSizeBytes,
            /* [size_is][out] */ BYTE buf[  ]);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LengthAndCharSize )( 
            IAutoADIString * This,
            /* [out] */ long *nChars,
            /* [out] */ long *charSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCapacity )( 
            IAutoADIString * This,
            /* [retval][out] */ long *nChars);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateNewString )( 
            IAutoADIString * This,
            /* [in] */ long capacity,
            /* [retval][out] */ IAutoADIString **newStr);
        
        END_INTERFACE
    } IAutoADIStringVtbl;

    interface IAutoADIString
    {
        CONST_VTBL struct IAutoADIStringVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAutoADIString_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAutoADIString_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAutoADIString_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAutoADIString_SetBStr(This,bStr)	\
    ( (This)->lpVtbl -> SetBStr(This,bStr) ) 

#define IAutoADIString_GetBStr(This,retval)	\
    ( (This)->lpVtbl -> GetBStr(This,retval) ) 

#define IAutoADIString_IsEmpty(This,retval)	\
    ( (This)->lpVtbl -> IsEmpty(This,retval) ) 

#define IAutoADIString_GetLength(This,retval)	\
    ( (This)->lpVtbl -> GetLength(This,retval) ) 

#define IAutoADIString_IsEqual(This,other,retval)	\
    ( (This)->lpVtbl -> IsEqual(This,other,retval) ) 

#define IAutoADIString_IsShared(This,retval)	\
    ( (This)->lpVtbl -> IsShared(This,retval) ) 

#define IAutoADIString_IsStringRep(This)	\
    ( (This)->lpVtbl -> IsStringRep(This) ) 

#define IAutoADIString_CopyBytesFromFirstChar(This,bufSizeBytes,buf)	\
    ( (This)->lpVtbl -> CopyBytesFromFirstChar(This,bufSizeBytes,buf) ) 

#define IAutoADIString_LengthAndCharSize(This,nChars,charSize)	\
    ( (This)->lpVtbl -> LengthAndCharSize(This,nChars,charSize) ) 

#define IAutoADIString_GetCapacity(This,nChars)	\
    ( (This)->lpVtbl -> GetCapacity(This,nChars) ) 

#define IAutoADIString_CreateNewString(This,capacity,newStr)	\
    ( (This)->lpVtbl -> CreateNewString(This,capacity,newStr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAutoADIString_INTERFACE_DEFINED__ */


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


