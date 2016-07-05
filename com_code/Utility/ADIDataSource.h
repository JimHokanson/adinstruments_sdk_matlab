/**
* Copyright (c) 2011-2012 ADInstruments. All rights reserved.
*
* \ADIDatFileSDK_license_start
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
*
* 2. The name of ADInstruments may not be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* 3. This is an unsupported product which you use at your own risk. For unofficial 
*    technical support, please use http://www.adinstruments.com/forum .
*
* THIS SOFTWARE IS PROVIDED BY ADINSTRUMENTS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ADINSTRUMENTS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* \ADIDatFileSDK_license_end
*/


#ifndef ADIDataSource_H__
#define ADIDataSource_H__


#include "IADIDataTypes.h"
#include "IADIDataSinkSource.h"

#include "Utility/ADIPtrVector.h"
#include "Utility/ADIRingBuffer.h"
#include "Utility/ADICBaseUnitsInfo.h"
#include "Utility/ADICUserUnitsInfo.h"

/** 
Helper classes useful for implementing the interfaces the ADIDataObject requires from data sources.
*/

namespace ADI
{

const double kTickToSampleRoundingErrorCorrection = 1e-8;


//Base class implementation of functionality common to different ChannelSource types.
class ChannelSourceBase
   {
   public:
      ChannelSourceBase(ADIDataType dataChannelType = kADIDataRecorded, ADIDataValueId dataValueType = kADIDataValue16Bit, double secsPerSample = 0);
      virtual ~ChannelSourceBase();
      
      void SetSecsPerSample(double secsPerSample) //Determines the sampling rate (1/secsPerSample) of the channel
         {
         mSecsPerSample = secsPerSample;
         }
         
      double GetSecsPerSample() const
         {
         return mSecsPerSample;
         }
         
      void SetUnits(
         const wchar_t *baseUnitsName = L"V",   //name of the unprefixed base unit, usually L"V".
         const CBaseUnitsInfo *baseInfo = 0,    //optional, may be null,specifies the scaling from ADCValues to base units (usually Volts). Null results in identity scaling.
         const CUserUnitsInfo *userInfo=0,      //optional, may be null, specifies the scaling from Volts to a unit (such as mmHg).
         const wchar_t *userUnitsName=0         //optional, may be null,name of the user unit, e.g. L"N".
         );

      //Returns a numeric constant representing the type of data to be stored in the channel      
      ADIDataValueId GetDataValueType() const
         {
         return mDataValueId;
         }
      
      //Returns a linear transformation to convert from stored data values to physical units (typically Volts)
      ADIScaling GetBaseScaling() const
         {
         ADIScaling result; //Initialised to the identity transform
         if(mBaseUnitsInfo.get())
            {
            result.mScaleSourceToOutput=mBaseUnitsInfo->mScaleToBase;
            result.mOffsetInSourceUnits=mBaseUnitsInfo->mMLVOffset;
            }
         return result;
         }
      
      //Transfers information about the the configuration of this channel through to the ADIData Object.
      HRESULT SetupChannel(int chanIndex, IADIDataSink *dataSink);

      //Creates an enumerator (IEnumShortEx or IEnumFloatEx) to supply data to the ADIData Object.
      virtual HRESULT CreateEnum(IEnumExBase **enumI) const = 0;
      
      //Returns the number of samples added to the channel source since the start of the record.
      virtual TTickIndex GetSampleCount() const = 0;
      
      //Returns true if there are no buffered samples which have not been transferred into the ADIData Object.
      virtual bool empty() const = 0;
      
   protected:
      ADIDataType mChannelType;
      ADIDataValueId mDataValueId;
      double mSecsPerSample;
      std::auto_ptr<CBaseUnitsInfo> mBaseUnitsInfo;
      std::auto_ptr<CUserUnitsInfo> mUserUnitsInfo;
      std::wstring mBaseUnitsName;
      std::wstring mUserUnitsName;
      bool mEnabled;
   };


const ulong kChannelSourceBufferCapacity = 511;

//declare a template for mapping data types to ADIDataValueId
template <typename T> struct DataTypeToId
   {
   static const ADIDataValueId GetId();
   };

//Specialise the template for the data types we care about.
template<>
struct DataTypeToId<int16> { static const ADIDataValueId GetId() {return kADIDataValue16Bit;} };

template<>
struct DataTypeToId<float> { static const ADIDataValueId GetId() {return kADIDataValueFloat;} };

template<>
struct DataTypeToId<int32> { static const ADIDataValueId GetId() {return kADIDataValue32Bit;} };

template<>
struct DataTypeToId<double> { static const ADIDataValueId GetId() {return kADIDataValueDouble;} };


//ChannelSource implementation for the case where each ChannelSource has an internal buffer of samples
//ready to be added to the ADIDataObject.
template<class IEnum>
class ChannelSourceBuffered : public ChannelSourceBase
{
typedef ChannelSourceBase Inherited;
public:
   typedef typename EnumXXXTraits<IEnum>::XXXType T; //the type output by the enumerators created from mRingBuffer
   
   ChannelSourceBuffered(ADIDataType dataChannelType = kADIDataRecorded) :
      Inherited(dataChannelType, DataTypeToId<T>::GetId()),
      mRingBuffer(kChannelSourceBufferCapacity+1)
      {
      }
     
   virtual HRESULT CreateEnum(IEnumExBase **enumI) const
      {
      mRingBuffer.CreateEnum((IEnum**)enumI);
      return S_OK;
      }

   virtual TTickIndex GetSampleCount() const
      {
      return mRingBuffer.GetInsertCount();
      }
   
   ulong GetSpace() const
      {
      return mRingBuffer.GetSpace();
      }
      
   //Adds a single data value.
   //Returns S_FALSE if not enough space to add the data value.
   HRESULT Add(T data)
      {
      return mRingBuffer.Add(data);
      }

   //Returns true if there are no buffered samples which have not been transferred into the ADIData Object.
   virtual bool empty() const
      {
      return mRingBuffer.GetMinCount()==0;
      }
protected:
   typedef RingBuffer<T, IEnum> TRingBuffer;
   TRingBuffer mRingBuffer;      
};

typedef ChannelSourceBuffered<IEnumShortEx> ChannelSourceBufferedInt16;
typedef ChannelSourceBuffered<IEnumFloatEx> ChannelSourceBufferedFloat;

//ChannelSource implementation for the case where each ChannelSource holds a reference to an external buffer 
//of the samples to be added to the ADIDataObject.
template<class IEnum>
class ChannelSourceUnbuffered : public ChannelSourceBase
{
typedef ChannelSourceBase Inherited;
public:
   typedef typename EnumXXXTraits<IEnum>::XXXType T; //the type output by the enumerators created from mRingBuffer

   ChannelSourceUnbuffered(ADIDataType dataChannelType = kADIDataRecorded) :
      Inherited(dataChannelType, DataTypeToId<T>::GetId()),
      mBufferPtr(0),
      mBufferLenSamples(0),
      mSamplesInRecord(0)
      {
      }

   void SetTickToSample(const TTickToSample &tickToSample)
      {
      mTickToSample = tickToSample;
      }

   virtual HRESULT CreateEnum(IEnumExBase **enumI) const
      {
      //if(mTheEnum)
      //   {
      //   MYASSERT(0);  //Only allow one enumerator at a time
      //   return E_FAIL;
      //   }
      //Only allow one enumerator at a time
      mTheEnum = new Enum(*this);
      mTheEnum.GetOut(enumI);
      return S_OK;
      }

   virtual TTickIndex GetSampleCount() const
      {
      return mSamplesInRecord;
      }
      
   //Returns true if there are no buffered samples which have not been transferred into the ADIData Object.
   virtual bool empty() const
      {
      if(mTheEnum)
         return mTheEnum->GetCount()==0;
      return mBufferLenSamples == 0;
      }
      

   void ReferenceBuffer(const T* buffer, TTickIndex numberOfSamplesInBuffer)
      {
      mBufferPtr = buffer;
      mBufferLenSamples = numberOfSamplesInBuffer;
      mSamplesInRecord += numberOfSamplesInBuffer;
      if(mTheEnum)
         mTheEnum->SetBuffer(mBufferPtr);
      }
   
   class Enum : public ADICOM::SimpleUnknownImp1_1<IEnum, IEnumExBase>
      {
      friend class ChannelSourceUnbuffered;
      
      int64 mPos;
      const T *mOut;
      const ChannelSourceUnbuffered &mSourceBuf;

      Enum& operator=(const Enum& other); //hide the assignment operator 

      protected:
      
         void SetBuffer(const T* buffer)
            {
            mOut = buffer;
            }

      public:

         explicit Enum(const ChannelSourceUnbuffered &sourceBuf):
            mSourceBuf(sourceBuf)
            {
            mPos = 0;
            mOut = mSourceBuf.mBufferPtr;
            }
         virtual ~Enum()
            {
            }
            
         HRESULT _IFUNC Clone(IEnum **clone)
            {//N.B. Assumes created with mNRef==1
            *clone = 0;
            MYASSERT(0);
            return E_NOTIMPL;
            }
            
      
         HRESULT _IFUNC Next(ulong nReq, T *buf, ulong *nRet)
            {
            *nRet = this->DoNext(nReq, buf);
            return S_OK; //always filling!
            }

         ulong DoNext(ulong nReq,T *buf) // Returns elements transfered count
            {
            ulong nToCopy = GetCount();
            if(nReq<nToCopy)
               nToCopy = nReq;
            memcpy(buf, mOut, nToCopy*sizeof(T));

            mOut += nToCopy;
            mPos += nToCopy;
            return nToCopy;
            }
            
         HRESULT _IFUNC SkipEx(long nToSkip, long *nSkipped)
            {
            HRESULT hr = S_OK;
            if(nToSkip >= 0)
               {
               long avail = GetCount();
               if(nToSkip > avail)
                  {
                  nToSkip = avail;
                  hr = S_FALSE;
                  }
               UnlimitedSkip(nToSkip);
               }
            else
               {//nToSkip < 0
               long avail = -(mOut-mSourceBuf.mBufferPtr); 
               if(nToSkip < avail)
                  {
                  nToSkip = avail;
                  hr = S_FALSE;
                  }
               mOut += nToSkip;
               mPos += nToSkip;
               }
            *nSkipped = nToSkip;
            return hr;
            }

         HRESULT _IFUNC GetPosition(long *nPos) const
            {
            *nPos = static_cast<long>(mPos);
            return S_OK;
            }

         HRESULT _IFUNC GetPosition(int64 *nPos) const
            {
            *nPos = mPos;
            return S_OK;
            }
            
         HRESULT _IFUNC GetTickToSample(TTickToSample *tickToSample) const
            {
            *tickToSample = mSourceBuf.mTickToSample;
            return E_NOTIMPL; //mTickToSample is not currently required by the ADIData Object
            }
            
         HRESULT _IFUNC Reset() 
            {
            MYASSERT(0); // Reset() should never be called on data source enumerators.
            return E_NOTIMPL;
            }

         HRESULT _IFUNC IsFilling(AutoBool *isFilling) const
            {
            *isFilling = true;
            MYASSERT(0); // IsFilling() should never be called on data source enumerators.
            return S_OK;
            }
            
         ulong GetCount() const 
            {
            return (mSourceBuf.mBufferPtr+mSourceBuf.mBufferLenSamples) - mOut;
            }

         void UnlimitedSkip(ulong n)
            {
            mOut += n;
            mPos += n;
            }
      };

protected:
   const T* mBufferPtr;
   TTickIndex mBufferLenSamples;
   int64 mSamplesInRecord;
   TTickToSample mTickToSample; 
   
   mutable ADI::COMPtr<Enum> mTheEnum;  //Only allow one enumerator to be created at a time.   
};

typedef ChannelSourceUnbuffered<IEnumShortEx> ChannelSourceUnbufferedInt16;
typedef ChannelSourceUnbuffered<IEnumFloatEx> ChannelSourceUnbufferedFloat;


//Helper class implementing the IADIChannelDataSource interface required by the ADIDataObject from data sources.
//This is basically just a container of ChannelSources.
class DataSource : public ADICOM::SimpleUnknownImp1<IADIChannelDataSource>  //IChartDataSource
{
public:
   typedef ADI::PtrVector<ChannelSourceBase> TChannels;


   DataSource();
   virtual ~DataSource();

   HRESULT _IFUNC GetChannelEnumShort(TGenericFlags, long chanIndex, IEnumShortEx **shortOut) const; // { ADIASSERT0(); return E_FAIL; }
   HRESULT _IFUNC GetChannelEnumFloat(TGenericFlags flags, long chanIndex, IEnumFloatEx **floatOut) const;
   HRESULT _IFUNC GetDataStreamEnum(TGenericFlags,long chanIndex,const IID &,IUnknown **) const { MYASSERT(0); return E_NOTIMPL; }
   
   TTickIndex GetTicks() const;
   
   double FindSecsPerTick() const;

   TChannels& GetChannelSources()
      {
      return mChannels;
      }
      
     
   HRESULT SetChannelSource(int chan, ChannelSourceBase *channelSource)
      {
      mChannels.SetOrAdd(chan, channelSource);
      return S_OK;
      }
      
   HRESULT SetupChannels(IADIDataSink *dataSink);      
           
protected:   
   TChannels mChannels;
};


}//namespace



#endif