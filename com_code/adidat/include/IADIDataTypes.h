

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


#ifndef __IADIDataTypes_midl_h__
#define __IADIDataTypes_midl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Utility/ADIIDLStuff.h"

/* Forward Declarations */ 

/* header files for imported files */
#include "oaidl.h"
#include "ADIBaseTypes.h"
#include "iautoadistring.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_IADIDataTypes_0000_0000 */
/* [local] */ 

typedef int32 TChanIndex;

typedef int32 TRecordIndex;

typedef int32 TCommentNum;

typedef /* [public] */ 
enum ADIReservedFlags
    {	kADIReservedNil	= 0
    } 	ADIReservedFlags;

typedef /* [public] */ 
enum TTickIndexConsts
    {	kRecordEndOffset	= 0x7fffffff
    } 	TTickIndexConsts;

typedef /* [public] */ 
enum TRecordIndexConsts
    {	kEndRecordIndex	= 0x7fffffff,
	kInvalidRecord	= 0x7fffffff,
	kPrototypeRecord	= 0x7ffffffe
    } 	TRecordIndexConsts;

typedef 
enum ADIDataFlags
    {	kADIDataScaleNone	= 0,
	kADIDataScaleADCUnits	= kADIDataScaleNone,
	kADIDataScaleToUnits	= 0x1000,
	kADIDataScaleToPrefixedUnits	= 0x2000,
	kADIDataScalingForceBaseOnly	= 0x4000,
	kADIDataScaleNoOffset	= 0x8000,
	kADIDataEnumLinear	= 0x100,
	kADIDataAtTickRate	= 0x80000000
    } 	ADIDataFlags;

typedef 
enum ADIDataType
    {	kADIDataRaw	= 1,
	kADIDataRecorded	= kADIDataRaw,
	kADIDataCalc	= 2,
	kADIDataDigital	= 3,
	kADIDataVirtual	= 4,
	kADIDataCalcElseRaw	= 0x40000000,
	kADIDataVRecorded	= 0x20000000,
	kADIDataTypesMask	= 0xff,
	kADIDataDefault	= ( kADIDataCalcElseRaw | kADIDataAtTickRate ) 
    } 	ADIDataType;

typedef 
enum ADIEnumDataType
    {	kADIEnumDataTypeNone	= 0,
	kADIEnumDataTypeFloatEx	= 0x80000000,
	kADIEnumDataTypeEventEx	= 0x40000000,
	kADIEnumDataTypeEventObjectEx	= 0x20000000,
	kADIEnumDataTypeDoubleEx	= 0x10000000,
	kADIEnumDataTypeVectorDoubleEx	= 0x8000000,
	kADIEnumDataTypeComplexEx	= 0x4000000,
	kADIEnumDataTypeVectorComplexEx	= 0x2000000,
	kADIEnumDataTypeVectorFloatEx	= 0x1000000,
	kADIEnumDataTypeVectorMask	= ( ( kADIEnumDataTypeVectorFloatEx | kADIEnumDataTypeVectorDoubleEx )  | kADIEnumDataTypeVectorComplexEx ) ,
	kADIEnumDataTypeShortEx	= 0x800000
    } 	ADIEnumDataType;

typedef 
enum ADIDataValueId
    {	kADIDataValue12Bit	= 0x80020000,
	kADIDataValue16Bit	= ( kADIDataValue12Bit + 1 ) ,
	kADIDataValue32Bit	= ( kADIDataValue16Bit + 1 ) ,
	kADIDataValueFloat	= ( kADIDataValue32Bit + 1 ) ,
	kADIDataValueDouble	= ( kADIDataValueFloat + 1 ) 
    } 	ADIDataValueId;


enum ADIDataConsts
    {	kADIInvalidChannel	= 0x80000000
    } ;
#ifndef __cplusplus
typedef struct ADIChannelId
    {
    TChanIndex mChan;
    ADIDataType mDataType;
    } 	ADIChannelId;

#else
 }//extern C 
 extern "C" {
struct ADIChannelId
{
TChanIndex mChan;
ADIDataType mDataType;
explicit ADIChannelId(TChanIndex chan = kADIInvalidChannel, ADIDataType dataType = kADIDataDefault) :
 mChan(chan), mDataType(dataType) {}
 bool operator==(const ADIChannelId &other) const {return mChan==other.mChan && mDataType==other.mDataType;}
 bool operator!=(const ADIChannelId &other) const {return !operator==(other);}
 bool operator <(const ADIChannelId& other) const {return mChan < other.mChan || (mChan == other.mChan && mDataType < other.mDataType);}
 static bool IsRaw(ADIDataType dataType)       {return (dataType & kADIDataTypesMask) == kADIDataRaw;}
 static bool IsVirtual(ADIDataType dataType)   {return (dataType & kADIDataTypesMask) == kADIDataVirtual;}
 static bool IsCalculated(ADIDataType dataType){return (dataType & kADIDataTypesMask)==kADIDataCalc || ((dataType & kADIDataTypesMask)==kADIDataVirtual && !(dataType & kADIDataVRecorded)) ;}
 static void SetRaw(ADIDataType &dataType)              {dataType = ADIDataType((dataType & ~(kADIDataTypesMask | kADIDataCalcElseRaw)) | kADIDataRaw);}
 static void SetVirtual(ADIDataType &dataType)          {dataType = ADIDataType((dataType & ~(kADIDataTypesMask | kADIDataCalcElseRaw)) | kADIDataVirtual);}
 static void SetNonVirtualCalc(ADIDataType &dataType)   {dataType = ADIDataType((dataType & ~(kADIDataTypesMask | kADIDataCalcElseRaw)) | kADIDataCalc);}
 static void SetVirtualRecorded(ADIDataType &dataType)  {dataType = ADIDataType((dataType & ~(kADIDataTypesMask | kADIDataCalcElseRaw)) | kADIDataVirtual | kADIDataVRecorded);}
 void SetRaw()              {SetRaw(mDataType);}
 void SetVirtual()          {SetVirtual(mDataType);}
 void SetNonVirtualCalc()   {SetNonVirtualCalc(mDataType);}
 void SetVirtualRecorded()  {SetVirtualRecorded(mDataType);}
 bool IsInvalid() const {return mChan == kADIInvalidChannel;}
 bool IsRaw() const {return IsRaw(mDataType);}
 bool IsVirtual() const {return IsVirtual(mDataType);}
 bool IsCalculated() const {return IsCalculated(mDataType);}
 bool IsCalcOrRaw() const {return (mDataType & kADIDataCalcElseRaw) || (mDataType & kADIDataTypesMask)==kADIDataCalc || (mDataType & kADIDataTypesMask)==kADIDataRaw;}
 bool IsSameChannel(const ADIChannelId &other) const {
     return mChan==other.mChan && (mDataType & kADIDataTypesMask)==(other.mDataType & kADIDataTypesMask);
     }
std::wostream & Write(std::wostream &s) const {s << mChan; s << L'\t'; s << static_cast<long>(mDataType); return s;}
std::wistream & Read(std::wistream &s) {long type(0); s >> mChan; s >> type; mDataType = static_cast<ADIDataType>(type); return s;}
};
#endif
#ifndef __cplusplus
typedef /* [public] */ struct ADIPosition
    {
    TTickIndex mRecordOffset;
    TRecordIndex mRecordIndex;
    } 	ADIPosition;

#else
typedef struct ADIPosition
{
ADIPosition() : mRecordOffset(kRecordEndOffset), mRecordIndex(kInvalidRecord) {}
ADIPosition(TRecordIndex rec,TTickIndex offset) : mRecordOffset(offset), mRecordIndex(rec) {}
TTickIndex mRecordOffset;
TRecordIndex mRecordIndex;
void SetInValid() { mRecordIndex = kInvalidRecord;}
bool IsValid() const { return mRecordIndex != kInvalidRecord;}
bool operator == (const ADIPosition& other) const {return (mRecordIndex == other.mRecordIndex) && (mRecordOffset == other.mRecordOffset);}
bool operator != (const ADIPosition& other) const {return (mRecordIndex != other.mRecordIndex) || (mRecordOffset != other.mRecordOffset);}
bool operator < (const ADIPosition& other) const {return (mRecordIndex < other.mRecordIndex) || ((mRecordIndex == other.mRecordIndex) && (mRecordOffset < other.mRecordOffset));}
bool operator > (const ADIPosition& other) const {return (mRecordIndex > other.mRecordIndex) || ((mRecordIndex == other.mRecordIndex) && (mRecordOffset > other.mRecordOffset));}
bool operator <= (const ADIPosition& other) const {return (mRecordIndex < other.mRecordIndex) || ((mRecordIndex == other.mRecordIndex) && (mRecordOffset <= other.mRecordOffset));}
bool operator >= (const ADIPosition& other) const {return (mRecordIndex > other.mRecordIndex) || ((mRecordIndex == other.mRecordIndex) && (mRecordOffset >= other.mRecordOffset));}
} ADIPosition;
#endif
#ifndef __cplusplus
typedef struct ADIScaling
    {
    double mScaleSourceToOutput;
    double mOffsetInSourceUnits;
    } 	ADIScaling;

#else
typedef struct ADIScaling
{
explicit ADIScaling(double scaleToOutput = 1.0, double offsetSourceUnits = 0.0) : mScaleSourceToOutput(scaleToOutput), mOffsetInSourceUnits(offsetSourceUnits) {}
double mScaleSourceToOutput;
double mOffsetInSourceUnits;
bool operator == (const ADIScaling& other) const {return (mScaleSourceToOutput == other.mScaleSourceToOutput) && (mOffsetInSourceUnits == other.mOffsetInSourceUnits);}
bool operator != (const ADIScaling& other) const {return ! operator == (other);}
double Scale(double val){return (mOffsetInSourceUnits + val) * mScaleSourceToOutput;}
double InverseScale(double val){return val/mScaleSourceToOutput - mOffsetInSourceUnits;}
} ADIScaling;
#endif
typedef 
enum UnitPrefix
    {	kUndefinedPrefix	= 0,
	kNoPrefix	= ( kUndefinedPrefix + 1 ) ,
	kAtto	= ( kNoPrefix + 1 ) ,
	kFemto	= ( kAtto + 1 ) ,
	kPico	= ( kFemto + 1 ) ,
	kNano	= ( kPico + 1 ) ,
	kMicro	= ( kNano + 1 ) ,
	kMilli	= ( kMicro + 1 ) ,
	kUnity	= ( kMilli + 1 ) ,
	kKilo	= ( kUnity + 1 ) ,
	kMega	= ( kKilo + 1 ) ,
	kGiga	= ( kMega + 1 ) ,
	kTera	= ( kGiga + 1 ) ,
	kP	= ( kTera + 1 ) ,
	kE	= ( kP + 1 ) ,
	kNumUnitPrefixes	= ( kE + 1 ) 
    } 	UnitPrefix;

#pragma pack(push,1)
typedef struct BaseUnitsInfo
    {
    double mScaleToBase;
    double mMLVOffset;
    float mMaxValid;
    float mMinValid;
    int32 mDecPlacesBase;
    UnitPrefix mPrefixBase;
    AutoBool mAutoPrefixBase;
    } 	BaseUnitsInfo;

#pragma pack(pop)
#pragma pack(push,1)
typedef struct UserUnitsInfo
    {
    double mScaleVToUnits;
    double mUnitOffset;
    int32 mDecPlaces;
    UnitPrefix mPrefix;
    AutoBool mAutoPrefix;
    AutoBool mOn;
    } 	UserUnitsInfo;

#pragma pack(pop)
typedef struct UnitPrefixInfo
    {
    uint32 mFlags;
    UnitPrefix mPrefix;
    } 	UnitPrefixInfo;

typedef 
enum TimeDisplayMode
    {	kTModeDocCurrent	= 0,
	kTModeTimeFromStartOfFile	= ( kTModeDocCurrent + 1 ) ,
	kTModeTimeFromStartOfRecord	= ( kTModeTimeFromStartOfFile + 1 ) ,
	kTModeTimeOfDay	= ( kTModeTimeFromStartOfRecord + 1 ) ,
	kTModeMask	= 0xff,
	kTModeAlwaysSecs	= 0x80000000,
	kTModeUT	= 0x40000000,
	kTModeAlwaysMilliSecs	= 0x20000000,
	kTModeUnitsNotTime	= 0x10000000
    } 	TimeDisplayMode;

typedef double ADITimeType;

typedef struct ADITimeDate
    {
    ADITimeType mSeconds;
    ADITimeType mBiasSecs;
    } 	ADITimeDate;

#ifndef __cplusplus
typedef struct RecordTimeInfo
    {
    double mSecPerTick;
    ADITimeDate mRecordTriggerTime;
    ADITimeDate mFileStartTime;
    TTickIndex mTrigTickMinusRecStartTick;
    } 	RecordTimeInfo;

#else
struct RecordTimeInfo
   {
   double mSecPerTick;
   ADITimeDate mRecordTriggerTime;
   ADITimeDate mFileStartTime;
   TTickIndex mTrigTickMinusRecStartTick;
   ADITimeType TickToSecInRec(TTickIndex tickInRec) const
      {
      return (tickInRec-mTrigTickMinusRecStartTick) * mSecPerTick;
      }
   ADITimeDate RecStartTime () const
      {
      ADITimeDate startTime(mRecordTriggerTime);
      startTime.mSeconds -= mTrigTickMinusRecStartTick * mSecPerTick;
      return startTime;
      }
   ADITimeDate RecTickTime(TTickIndex tickInRec) const
      {
      ADITimeDate startTime(mRecordTriggerTime);
      startTime.mSeconds += (tickInRec-mTrigTickMinusRecStartTick) * mSecPerTick;
      return startTime;
      }
   };
#endif
typedef struct ChannelYDataRange
    {
    double m_top;
    double m_bottom;
    } 	ChannelYDataRange;

 } //extern "C" 
inline bool operator == (const ChannelYDataRange& lhs, const ChannelYDataRange& rhs) {return lhs.m_top == rhs.m_top && lhs.m_bottom == rhs.m_bottom;}
inline bool operator != (const ChannelYDataRange& lhs, const ChannelYDataRange& rhs) {return !(lhs==rhs);}
extern "C"{
typedef /* [public] */ 
enum EventFindTypes
    {	kEFTFindForwards	= 0,
	kEFTFindBackwards	= ( kEFTFindForwards + 1 ) 
    } 	EventFindTypes;



extern RPC_IF_HANDLE __MIDL_itf_IADIDataTypes_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IADIDataTypes_0000_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


