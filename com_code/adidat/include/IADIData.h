

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

#ifndef __IADIData_midl_h__
#define __IADIData_midl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Utility/ADIIDLStuff.h"

/* Forward Declarations */ 

#ifndef __IADIData_FWD_DEFINED__
#define __IADIData_FWD_DEFINED__
typedef COMINTERFACE IADIData IADIData;
#endif 	/* __IADIData_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "IADIDataTypes.h"
#include "IADIEnums.h"
#include "IADIComment.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IADIData_INTERFACE_DEFINED__
#define __IADIData_INTERFACE_DEFINED__

/* interface IADIData */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IADIData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4A0A2EDF-C81C-411e-ABB7-2CC0457DFB16")
    IADIData : public IUnknown
    {
    static const IID& uuidof() {return IID_IADIData;} //Inserted by ADIIDL post-processor

    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumberOfRecords( 
            /* [in] */ ADIDataType dataType,
            /* [retval][out] */ TRecordIndex *nrecs) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumberOfChannels( 
            /* [in] */ ADIDataType dataType,
            /* [retval][out] */ TChanIndex *chan) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetChannelName( 
            /* [in] */ ADIChannelId channel,
            /* [retval][out] */ IAutoADIString **chanName) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRecordLength( 
            /* [in] */ ADIReservedFlags flags,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ TTickIndex *ticks) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RecordHasData( 
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ AutoBool *hasData) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumSamplesInRecord( 
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ TTickIndex *numSamples) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSecsPerSample( 
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ double *secs) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTickToSample( 
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ TTickToSample *tickToSample) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRecordTimeInfo( 
            /* [in] */ ADIReservedFlags flags,
            /* [in] */ TRecordIndex rec,
            /* [in] */ uint32 sizeOfTimeInfo,
            /* [retval][out] */ RecordTimeInfo *timeInfo) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ADIPositionToTime( 
            /* [in] */ ADIReservedFlags flags,
            /* [in] */ TimeDisplayMode timeMode,
            /* [in] */ ADIPosition tick,
            /* [retval][out] */ ADITimeDate *time) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDataFormatId( 
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ TCAFId *formatId) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetUnitsName( 
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ IAutoADIString **name) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetADCToUnitsScaling( 
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ ADIScaling *out) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetUnitsInfo( 
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [out] */ BaseUnitsInfo *baseInfo,
            /* [out] */ IAutoADIString **baseName,
            /* [out] */ UserUnitsInfo *userInfo,
            /* [retval][out] */ IAutoADIString **userName) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindYDataRange( 
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ ADIPosition startTP,
            /* [in] */ ADIPosition endTP,
            /* [in] */ ADIReservedFlags flags,
            /* [retval][out] */ ChannelYDataRange *range) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateEnumComment( 
            /* [in] */ EnumCommentFlags flags,
            /* [in] */ TChanIndex channel,
            /* [in] */ ADIPosition start,
            /* [in] */ TTickIndex stop,
            /* [in] */ TCAFId cafId,
            /* [out] */ IEnumADIComment **__MIDL__IADIData0000) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateEnumCommentFromPos( 
            /* [in] */ EnumCommentFlags flags,
            /* [in] */ TChanIndex channel,
            /* [in] */ TRecordIndex rec,
            /* [in] */ ChartCommentPos start,
            /* [in] */ TTickIndex stop,
            /* [in] */ TCAFId cafId,
            /* [out] */ IEnumADIComment **__MIDL__IADIData0001) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateEnumCommentReverse( 
            /* [in] */ EnumCommentFlags flags,
            /* [in] */ TChanIndex channel,
            /* [in] */ ADIPosition start,
            /* [in] */ TTickIndex stop,
            /* [in] */ TCAFId cafId,
            /* [out] */ IEnumADIComment **__MIDL__IADIData0002) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRightMostCommentInRange( 
            /* [in] */ EnumCommentFlags searchFlags,
            /* [in] */ ADIPosition leftPos,
            /* [in] */ ADIPosition rightPos,
            /* [in] */ TChanIndex chan,
            /* [out] */ IADIComment **icmt) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEnumFloat( 
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ ADIPosition start,
            /* [in] */ TTickIndex endOffset,
            /* [in] */ const ADIScaling *scaling,
            /* [retval][out] */ IEnumFloatEx **enumI) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEnumX( 
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIEnumDataType enumTypeId,
            /* [in] */ ADIChannelId channel,
            /* [in] */ ADIPosition start,
            /* [in] */ TTickIndex endOffset,
            /* [in] */ const ADIScaling *scaling,
            /* [retval][out] */ IUnknown **enumI) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetValDouble( 
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ ADIPosition position,
            /* [in] */ const ADIScaling *scaling,
            /* [retval][out] */ double *val) const = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetErrorMessage( 
            /* [in] */ HRESULT errorCode,
            /* [in] */ ADIReservedFlags reserved,
            /* [retval][out] */ IAutoADIString **msg) const = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADIDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IADIData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IADIData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IADIData * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumberOfRecords )( 
            IADIData * This,
            /* [in] */ ADIDataType dataType,
            /* [retval][out] */ TRecordIndex *nrecs);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumberOfChannels )( 
            IADIData * This,
            /* [in] */ ADIDataType dataType,
            /* [retval][out] */ TChanIndex *chan);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetChannelName )( 
            IADIData * This,
            /* [in] */ ADIChannelId channel,
            /* [retval][out] */ IAutoADIString **chanName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRecordLength )( 
            IADIData * This,
            /* [in] */ ADIReservedFlags flags,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ TTickIndex *ticks);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RecordHasData )( 
            IADIData * This,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ AutoBool *hasData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumSamplesInRecord )( 
            IADIData * This,
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ TTickIndex *numSamples);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSecsPerSample )( 
            IADIData * This,
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ double *secs);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTickToSample )( 
            IADIData * This,
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ TTickToSample *tickToSample);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRecordTimeInfo )( 
            IADIData * This,
            /* [in] */ ADIReservedFlags flags,
            /* [in] */ TRecordIndex rec,
            /* [in] */ uint32 sizeOfTimeInfo,
            /* [retval][out] */ RecordTimeInfo *timeInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ADIPositionToTime )( 
            IADIData * This,
            /* [in] */ ADIReservedFlags flags,
            /* [in] */ TimeDisplayMode timeMode,
            /* [in] */ ADIPosition tick,
            /* [retval][out] */ ADITimeDate *time);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDataFormatId )( 
            IADIData * This,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ TCAFId *formatId);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetUnitsName )( 
            IADIData * This,
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ IAutoADIString **name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetADCToUnitsScaling )( 
            IADIData * This,
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [retval][out] */ ADIScaling *out);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetUnitsInfo )( 
            IADIData * This,
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ TRecordIndex rec,
            /* [out] */ BaseUnitsInfo *baseInfo,
            /* [out] */ IAutoADIString **baseName,
            /* [out] */ UserUnitsInfo *userInfo,
            /* [retval][out] */ IAutoADIString **userName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindYDataRange )( 
            IADIData * This,
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ ADIPosition startTP,
            /* [in] */ ADIPosition endTP,
            /* [in] */ ADIReservedFlags flags,
            /* [retval][out] */ ChannelYDataRange *range);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateEnumComment )( 
            IADIData * This,
            /* [in] */ EnumCommentFlags flags,
            /* [in] */ TChanIndex channel,
            /* [in] */ ADIPosition start,
            /* [in] */ TTickIndex stop,
            /* [in] */ TCAFId cafId,
            /* [out] */ IEnumADIComment **__MIDL__IADIData0000);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateEnumCommentFromPos )( 
            IADIData * This,
            /* [in] */ EnumCommentFlags flags,
            /* [in] */ TChanIndex channel,
            /* [in] */ TRecordIndex rec,
            /* [in] */ ChartCommentPos start,
            /* [in] */ TTickIndex stop,
            /* [in] */ TCAFId cafId,
            /* [out] */ IEnumADIComment **__MIDL__IADIData0001);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateEnumCommentReverse )( 
            IADIData * This,
            /* [in] */ EnumCommentFlags flags,
            /* [in] */ TChanIndex channel,
            /* [in] */ ADIPosition start,
            /* [in] */ TTickIndex stop,
            /* [in] */ TCAFId cafId,
            /* [out] */ IEnumADIComment **__MIDL__IADIData0002);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRightMostCommentInRange )( 
            IADIData * This,
            /* [in] */ EnumCommentFlags searchFlags,
            /* [in] */ ADIPosition leftPos,
            /* [in] */ ADIPosition rightPos,
            /* [in] */ TChanIndex chan,
            /* [out] */ IADIComment **icmt);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEnumFloat )( 
            IADIData * This,
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ ADIPosition start,
            /* [in] */ TTickIndex endOffset,
            /* [in] */ const ADIScaling *scaling,
            /* [retval][out] */ IEnumFloatEx **enumI);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEnumX )( 
            IADIData * This,
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIEnumDataType enumTypeId,
            /* [in] */ ADIChannelId channel,
            /* [in] */ ADIPosition start,
            /* [in] */ TTickIndex endOffset,
            /* [in] */ const ADIScaling *scaling,
            /* [retval][out] */ IUnknown **enumI);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetValDouble )( 
            IADIData * This,
            /* [in] */ ADIDataFlags dataFlags,
            /* [in] */ ADIChannelId channel,
            /* [in] */ ADIPosition position,
            /* [in] */ const ADIScaling *scaling,
            /* [retval][out] */ double *val);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetErrorMessage )( 
            IADIData * This,
            /* [in] */ HRESULT errorCode,
            /* [in] */ ADIReservedFlags reserved,
            /* [retval][out] */ IAutoADIString **msg);
        
        END_INTERFACE
    } IADIDataVtbl;

    interface IADIData
    {
        CONST_VTBL struct IADIDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADIData_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IADIData_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IADIData_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IADIData_GetNumberOfRecords(This,dataType,nrecs)	\
    ( (This)->lpVtbl -> GetNumberOfRecords(This,dataType,nrecs) ) 

#define IADIData_GetNumberOfChannels(This,dataType,chan)	\
    ( (This)->lpVtbl -> GetNumberOfChannels(This,dataType,chan) ) 

#define IADIData_GetChannelName(This,channel,chanName)	\
    ( (This)->lpVtbl -> GetChannelName(This,channel,chanName) ) 

#define IADIData_GetRecordLength(This,flags,rec,ticks)	\
    ( (This)->lpVtbl -> GetRecordLength(This,flags,rec,ticks) ) 

#define IADIData_RecordHasData(This,channel,rec,hasData)	\
    ( (This)->lpVtbl -> RecordHasData(This,channel,rec,hasData) ) 

#define IADIData_GetNumSamplesInRecord(This,dataFlags,channel,rec,numSamples)	\
    ( (This)->lpVtbl -> GetNumSamplesInRecord(This,dataFlags,channel,rec,numSamples) ) 

#define IADIData_GetSecsPerSample(This,dataFlags,channel,rec,secs)	\
    ( (This)->lpVtbl -> GetSecsPerSample(This,dataFlags,channel,rec,secs) ) 

#define IADIData_GetTickToSample(This,dataFlags,channel,rec,tickToSample)	\
    ( (This)->lpVtbl -> GetTickToSample(This,dataFlags,channel,rec,tickToSample) ) 

#define IADIData_GetRecordTimeInfo(This,flags,rec,sizeOfTimeInfo,timeInfo)	\
    ( (This)->lpVtbl -> GetRecordTimeInfo(This,flags,rec,sizeOfTimeInfo,timeInfo) ) 

#define IADIData_ADIPositionToTime(This,flags,timeMode,tick,time)	\
    ( (This)->lpVtbl -> ADIPositionToTime(This,flags,timeMode,tick,time) ) 

#define IADIData_GetDataFormatId(This,channel,rec,formatId)	\
    ( (This)->lpVtbl -> GetDataFormatId(This,channel,rec,formatId) ) 

#define IADIData_GetUnitsName(This,dataFlags,channel,rec,name)	\
    ( (This)->lpVtbl -> GetUnitsName(This,dataFlags,channel,rec,name) ) 

#define IADIData_GetADCToUnitsScaling(This,dataFlags,channel,rec,out)	\
    ( (This)->lpVtbl -> GetADCToUnitsScaling(This,dataFlags,channel,rec,out) ) 

#define IADIData_GetUnitsInfo(This,dataFlags,channel,rec,baseInfo,baseName,userInfo,userName)	\
    ( (This)->lpVtbl -> GetUnitsInfo(This,dataFlags,channel,rec,baseInfo,baseName,userInfo,userName) ) 

#define IADIData_FindYDataRange(This,dataFlags,channel,startTP,endTP,flags,range)	\
    ( (This)->lpVtbl -> FindYDataRange(This,dataFlags,channel,startTP,endTP,flags,range) ) 

#define IADIData_CreateEnumComment(This,flags,channel,start,stop,cafId,__MIDL__IADIData0000)	\
    ( (This)->lpVtbl -> CreateEnumComment(This,flags,channel,start,stop,cafId,__MIDL__IADIData0000) ) 

#define IADIData_CreateEnumCommentFromPos(This,flags,channel,rec,start,stop,cafId,__MIDL__IADIData0001)	\
    ( (This)->lpVtbl -> CreateEnumCommentFromPos(This,flags,channel,rec,start,stop,cafId,__MIDL__IADIData0001) ) 

#define IADIData_CreateEnumCommentReverse(This,flags,channel,start,stop,cafId,__MIDL__IADIData0002)	\
    ( (This)->lpVtbl -> CreateEnumCommentReverse(This,flags,channel,start,stop,cafId,__MIDL__IADIData0002) ) 

#define IADIData_GetRightMostCommentInRange(This,searchFlags,leftPos,rightPos,chan,icmt)	\
    ( (This)->lpVtbl -> GetRightMostCommentInRange(This,searchFlags,leftPos,rightPos,chan,icmt) ) 

#define IADIData_GetEnumFloat(This,dataFlags,channel,start,endOffset,scaling,enumI)	\
    ( (This)->lpVtbl -> GetEnumFloat(This,dataFlags,channel,start,endOffset,scaling,enumI) ) 

#define IADIData_GetEnumX(This,dataFlags,enumTypeId,channel,start,endOffset,scaling,enumI)	\
    ( (This)->lpVtbl -> GetEnumX(This,dataFlags,enumTypeId,channel,start,endOffset,scaling,enumI) ) 

#define IADIData_GetValDouble(This,dataFlags,channel,position,scaling,val)	\
    ( (This)->lpVtbl -> GetValDouble(This,dataFlags,channel,position,scaling,val) ) 

#define IADIData_GetErrorMessage(This,errorCode,reserved,msg)	\
    ( (This)->lpVtbl -> GetErrorMessage(This,errorCode,reserved,msg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IADIData_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


