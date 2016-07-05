

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

#ifndef __IADIComment_midl_h__
#define __IADIComment_midl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Utility/ADIIDLStuff.h"

/* Forward Declarations */ 

#ifndef __IADIComment_FWD_DEFINED__
#define __IADIComment_FWD_DEFINED__
typedef COMINTERFACE IADIComment IADIComment;
#endif 	/* __IADIComment_FWD_DEFINED__ */


#ifndef __IEnumADIComment_FWD_DEFINED__
#define __IEnumADIComment_FWD_DEFINED__
typedef COMINTERFACE IEnumADIComment IEnumADIComment;
#endif 	/* __IEnumADIComment_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "IADIDataTypes.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_IADIComment_0000_0000 */
/* [local] */ 

typedef 
enum ADICommentFlags
    {	kCommentFlagChartDataPersist	= 0x80000000,
	kCommentFlagVisibleInCommentView	= 0x40000000,
	kCommentFlagVisibleToFindComment	= 0x20000000,
	kCommentFlagVisibleInTextOutput	= 0x10000000,
	kCommentFlagVisibleInPrintText	= 0x4000000,
	kCommentFlagCommentsDifferInShape	= 0x2000000,
	kCommentFlagNotAnEvent	= 0x1000000,
	kCommentFlagShowText	= 0x800000,
	kCommentFlagDraggable	= 0x400000,
	kCommentFlagDragHandle	= 0x200000,
	kCommentFlagTwoStageDrag	= 0x100000,
	kCommentFlagSuppressPopup	= 0x80000,
	kCommentFlagHasContextMenu	= 0x40000,
	kCommentFlagDefaultForEventComment	= 0,
	kCommentFlagDefaultForStdComment	= ( ( ( ( ( ( ( ( ( ( ( kCommentFlagChartDataPersist | kCommentFlagVisibleInCommentView )  | kCommentFlagVisibleToFindComment )  | kCommentFlagVisibleInTextOutput )  | kCommentFlagVisibleInPrintText )  | kCommentFlagCommentsDifferInShape )  | kCommentFlagNotAnEvent )  | kCommentFlagShowText )  | kCommentFlagDraggable )  | kCommentFlagDragHandle )  | kCommentFlagTwoStageDrag )  | kCommentFlagHasContextMenu ) 
    } 	ADICommentFlags;

typedef 
enum EnumCommentFlags
    {	kEnumCommentIncludeEventComments	= 0x80000000,
	kEnumCommentEventCommentsOnly	= 0x40000000,
	kEnumCommentFilterUsingCAFId	= 0x20000000,
	kEnumCommentSearchTypeMask	= 0xff,
	kSearchSpecificChannelOnly	= 0,
	kSearchAlsoAllChanComment	= 1,
	kSearchAnyChannel	= 2
    } 	EnumCommentFlags;

typedef EnumCommentFlags CommentSearchType;

typedef ulong TCommentIndex;

typedef struct ChartCommentPos
    {
    TTickIndex mPos;
    TCommentIndex mIndexOnTick;
    } 	ChartCommentPos;



extern RPC_IF_HANDLE __MIDL_itf_IADIComment_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IADIComment_0000_0000_v0_0_s_ifspec;

#ifndef __IADIComment_INTERFACE_DEFINED__
#define __IADIComment_INTERFACE_DEFINED__

/* interface IADIComment */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IADIComment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C58850BE-1FB1-4e11-B39E-8B1B3A36C58B")
    IADIComment : public IUnknown
    {
    static const IID& uuidof() {return IID_IADIComment;} //Inserted by ADIIDL post-processor

    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCommentInfo( 
            /* [out] */ TTickIndex *offsetInRecord,
            /* [out] */ TChanIndex *chanIndex,
            /* [out] */ TCommentNum *num,
            /* [retval][out] */ IAutoADIString **text) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetChannelIndex( 
            /* [retval][out] */ TChanIndex *channel) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRecordOffset( 
            /* [out] */ TTickIndex *offsetInRecord) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCommentNumber( 
            /* [retval][out] */ TCommentNum *number) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTypeId( 
            /* [retval][out] */ TCAFId *id) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFlags( 
            /* [retval][out] */ ADICommentFlags *flags) const = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADICommentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IADIComment * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IADIComment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IADIComment * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCommentInfo )( 
            IADIComment * This,
            /* [out] */ TTickIndex *offsetInRecord,
            /* [out] */ TChanIndex *chanIndex,
            /* [out] */ TCommentNum *num,
            /* [retval][out] */ IAutoADIString **text);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetChannelIndex )( 
            IADIComment * This,
            /* [retval][out] */ TChanIndex *channel);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRecordOffset )( 
            IADIComment * This,
            /* [out] */ TTickIndex *offsetInRecord);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCommentNumber )( 
            IADIComment * This,
            /* [retval][out] */ TCommentNum *number);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTypeId )( 
            IADIComment * This,
            /* [retval][out] */ TCAFId *id);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFlags )( 
            IADIComment * This,
            /* [retval][out] */ ADICommentFlags *flags);
        
        END_INTERFACE
    } IADICommentVtbl;

    COMINTERFACE IADIComment
    {
        CONST_VTBL struct IADICommentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADIComment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IADIComment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IADIComment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IADIComment_GetCommentInfo(This,offsetInRecord,chanIndex,num,text)	\
    ( (This)->lpVtbl -> GetCommentInfo(This,offsetInRecord,chanIndex,num,text) ) 

#define IADIComment_GetChannelIndex(This,channel)	\
    ( (This)->lpVtbl -> GetChannelIndex(This,channel) ) 

#define IADIComment_GetRecordOffset(This,offsetInRecord)	\
    ( (This)->lpVtbl -> GetRecordOffset(This,offsetInRecord) ) 

#define IADIComment_GetCommentNumber(This,number)	\
    ( (This)->lpVtbl -> GetCommentNumber(This,number) ) 

#define IADIComment_GetTypeId(This,id)	\
    ( (This)->lpVtbl -> GetTypeId(This,id) ) 

#define IADIComment_GetFlags(This,flags)	\
    ( (This)->lpVtbl -> GetFlags(This,flags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IADIComment_INTERFACE_DEFINED__ */


#ifndef __IEnumADIComment_INTERFACE_DEFINED__
#define __IEnumADIComment_INTERFACE_DEFINED__

/* interface IEnumADIComment */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumADIComment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("39AC0A31-FEC0-420c-8A1B-4E147B29F6F5")
    IEnumADIComment : public IUnknown
    {
    static const IID& uuidof() {return IID_IEnumADIComment;} //Inserted by ADIIDL post-processor

    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ TEnumCount n,
            /* [in] */ TTickIndex endTick,
            /* [length_is][length_is][size_is][size_is][out] */ IADIComment **iCmt,
            /* [retval][out] */ TEnumCount *nRetd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumADIComment **retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            EventFindTypes findType,
            TTickIndex searchPos,
            TTickIndex limitStart,
            TTickIndex limitEnd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [retval][out] */ ChartCommentPos *nPos) const = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumADICommentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumADIComment * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumADIComment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumADIComment * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumADIComment * This,
            /* [in] */ TEnumCount n,
            /* [in] */ TTickIndex endTick,
            /* [length_is][length_is][size_is][size_is][out] */ IADIComment **iCmt,
            /* [retval][out] */ TEnumCount *nRetd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumADIComment * This,
            /* [retval][out] */ IEnumADIComment **retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IEnumADIComment * This,
            EventFindTypes findType,
            TTickIndex searchPos,
            TTickIndex limitStart,
            TTickIndex limitEnd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPosition )( 
            IEnumADIComment * This,
            /* [retval][out] */ ChartCommentPos *nPos);
        
        END_INTERFACE
    } IEnumADICommentVtbl;

    interface IEnumADIComment
    {
        CONST_VTBL struct IEnumADICommentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumADIComment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumADIComment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumADIComment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumADIComment_Next(This,n,endTick,iCmt,nRetd)	\
    ( (This)->lpVtbl -> Next(This,n,endTick,iCmt,nRetd) ) 

#define IEnumADIComment_Clone(This,retval)	\
    ( (This)->lpVtbl -> Clone(This,retval) ) 

#define IEnumADIComment_Find(This,findType,searchPos,limitStart,limitEnd)	\
    ( (This)->lpVtbl -> Find(This,findType,searchPos,limitStart,limitEnd) ) 

#define IEnumADIComment_GetPosition(This,nPos)	\
    ( (This)->lpVtbl -> GetPosition(This,nPos) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumADIComment_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_IADIComment_0000_0002 */
/* [local] */ 

 DEFINE_ENUMCOMMENTPTRTYPE2(IEnumADIComment,IADIComment) 


extern RPC_IF_HANDLE __MIDL_itf_IADIComment_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IADIComment_0000_0002_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


