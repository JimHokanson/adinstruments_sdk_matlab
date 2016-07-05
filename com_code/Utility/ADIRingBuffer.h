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


#ifndef ADIRingBuffer_H__
#define ADIRingBuffer_H__

#include "SimpleUnknownImp.h"
#include "adidat/include/IADIEnums.h"

namespace ADI
{

/*
Ring buffer (FIFO) template class for data types T which are POD data (i.e. T contains no pointers, 
no references, no virtual functions, and has no destructor).
Various methods for adding data to the buffer are supported, and clients can create multiple
independent enumerators (of type IEnumTEx) to extract data from the buffer.
Adding data and extracting data (by calling Next() on an enumerator) can be done on separate
threads without the need for mutex locks.
The buffer does not grow when it becomes full and can only be safely resized when it is not
in use, since doing so will invalidate any enumerators on the buffer.
*/ 

template <class T, class IEnum>
class RingBuffer
   {
   public:
      typedef RingBuffer Self;
      typedef int64 TInsertCountType;

      class Enum : public ADICOM::SimpleUnknownImp1_1<IEnum, IEnumExBase>
         {
         int64 mPos;
         T *mOut;
         const RingBuffer<T,IEnum> &mRingBuf;
         Enum *mNext;

         Enum& operator=(const Enum& other); //hide the assignment operator 

         protected:

            const RingBuffer<T,IEnum> &GetRingBuf() const {return mRingBuf;}

         public:

            explicit Enum(const RingBuffer<T,IEnum> &ringBuf):
               mRingBuf(ringBuf)
               {
               mPos = 0;
               mOut = mRingBuf.mStart;
               mNext = ringBuf.mOutputEnumList;
               ringBuf.mOutputEnumList = this;
               }

            Enum(const Enum& other):
               mPos(other.mPos),
               mOut(other.mOut),
               mRingBuf(other.mRingBuf)
                  {
                  mNext = mRingBuf.mOutputEnumList;
                  mRingBuf.mOutputEnumList = this;
                  }

               ~Enum()
                  {
                  Enum** ptr = &mRingBuf.mOutputEnumList;
                  while(*ptr != this)
                     ptr = &((*ptr)->mNext);

                  *ptr =(*ptr)->mNext;
                  }


               HRESULT _IFUNC Next(ulong nReq, T *buf, ulong *nRet)
                  {
                  *nRet = RingBuffer<T,IEnum>::Enum::DoNext(nReq, buf);
                  return *nRet == nReq ? S_OK : mRingBuf.mHRIsFilling;/*S_FALSE*/
                  }

               HRESULT _IFUNC Skip(ulong n)
                  {
                  HRESULT result = S_OK;
                  ulong avail = GetCount();
                  if(n > avail)
                     {
                     n = avail;
                     result = S_FALSE;
                     }
                  UnlimitedSkip(n);
                  return result;
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
                     //The maximum usable buffer size is(mRingBuf.mEnd-mRingBuf.mStart)-1 since the buffer is considered empty if the input and output pointers coincide.
                     long avail = -static_cast<long>(HasWrapped()?mRingBuf.mLenMask/*GetSpace()*/:mOut-mRingBuf.mStart); 
                     if(nToSkip < avail)
                        {
                        nToSkip = avail;
                        hr = S_FALSE;
                        }
                     mOut += nToSkip;
                     if(mOut < mRingBuf.mStart)
                        mOut +=(mRingBuf.mEnd-mRingBuf.mStart);
                     mPos += nToSkip;
                     }
                  *nSkipped = nToSkip;
                  return hr;
                  }

               HRESULT _IFUNC Reset() 
                  {
                  MYASSERT(0); // Reset() should never be called on data source enumerators.
                  return E_NOTIMPL;
                  }

               HRESULT _IFUNC Clone(IEnum **clone)
                  {//N.B. Assumes created with mNRef==1
                  *clone = new Enum(*this);
                  return S_OK;
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

               HRESULT _IFUNC IsFilling(AutoBool *isFilling) const
                  {
                  *isFilling = true;
                  MYASSERT(0); // IsFilling() should never be called on data souce enumerators.
                  return S_OK;
                  }

               HRESULT _IFUNC GetTickToSample(TTickToSample *tickToSample) const
                  {
                  *tickToSample = mRingBuf.mTickToSample;
                  return E_NOTIMPL; //mTickToSample is not currently required by the ADIData Object
                  }

               HRESULT _IFUNC SetTickToSample(TGenericFlags flags,const TTickToSample *tickToSample)
                  {
                  mRingBuf.mTickToSample = *tickToSample;
                  return S_OK;
                  }

               ulong DoNext(ulong nReq,T *buf) // Returns elements transfered count
                  {
                  ulong nTotal = GetCount();
                  if(nReq<nTotal)
                     nTotal = nReq;
                  if(mOut+nTotal > mRingBuf.mEnd)
                     {// wrapped
                     ulong nEnd = mRingBuf.mEnd-mOut;
                     memcpy(buf, mOut, nEnd*sizeof(T));
                     memcpy(buf+nEnd, mRingBuf.mStart,(nTotal-nEnd)*sizeof(T));
                     }
                  else // No wrap
                     memcpy(buf, mOut, nTotal*sizeof(T));

                  mOut += nTotal;
                  if(mOut >= mRingBuf.mEnd)
                     mOut -=(mRingBuf.mEnd-mRingBuf.mStart);
                  mPos += nTotal;
                  return nTotal;
                  }

               void UnlimitedSkip(ulong n)
                  {
                  mOut += n;
                  if(mOut >= mRingBuf.mEnd)
                     mOut = mRingBuf.mStart+((mOut-mRingBuf.mStart) & mRingBuf.mLenMask);
                  mPos += n;
                  }

               ulong CountedSkip(ulong n)
                  {
                  if(n > GetCount())
                     n = GetCount();

                  mOut += n;
                  if(mOut >= mRingBuf.mEnd)
                     mOut -=(mRingBuf.mEnd-mRingBuf.mStart);
                  mPos += n;
                  return n;
                  }

               ulong Peek(ulong nReq, T *&buf) const // Returns elements available count
                  {
                  uint available = min(nReq, GetCount());
                  buf = mOut;
                  if(mOut + available > mRingBuf.mEnd)
                     available = mRingBuf.mEnd - mOut; // wrap required, return chunk to end of buffer

                  return available;
                  }

               ulong GetCount() const //N.B. this only works if buffer length is 2^n
                  {
                  return(mRingBuf.mIn - mOut) & mRingBuf.mLenMask;
                  }
                  
               bool HaveData() const 
                  {
                  return mOut != mRingBuf.mIn;
                  }
               ulong GetSpace() const 
                  {
                  return mRingBuf.mLenMask - GetCount();
                  }
               Enum *GetNextEnum() const {return mNext;}

               bool HasWrapped() const
                  {
                  return mRingBuf.mHasWrapped;
                  }

               friend RingBuffer<T,IEnum>;
         };

      friend class Enum;

      explicit RingBuffer(ulong minLength = 128);
      
      virtual ~RingBuffer();


      void SetTickToSample(const TTickToSample &tickToSample)
         {
         mTickToSample = tickToSample;
         }


      void CreateEnum(IEnum **enumOut) const
         {
         ADI::COMPtr<IEnum> enumI(new Enum(*this));
         enumI.Transfer(enumOut);
         }


      template <class Enum> 
      HRESULT AddFromEnum(Enum *enumI) //Returns S_FALSE if the buffer was filled.
         {
         ulong nRet;
         return Self::AddFromEnum(enumI,&nRet);
         }   

      template <class Enum> 
      HRESULT AddFromEnum(Enum *enumI, ulong *nRet) //Returns S_FALSE if the buffer was filled.
         {
         ulong space = GetSpace();
         ulong space1 = min<ulong>(mEnd-mIn,space);
         enumI->Next(space1,mIn,nRet);
         mIn += *nRet;
         if(mIn >= mEnd)
            {//Wrapped
            mHasWrapped = true;
            if(space > space1)
               {
               mIn = mStart;
               ulong nRet1;
               enumI->Next(space-space1, mIn, &nRet1);
               mIn += nRet1;
               *nRet += nRet1;
               }
            }
         mInsertCount += *nRet;
         return space > *nRet ? S_OK : S_FALSE;
         }
      
      //Adds a single data value.
      //Returns S_FALSE if not enough space to add the data value.
      HRESULT Add(const T &data)
         {
         if(!GetSpace())
            return S_FALSE;
            
         *mIn++ = data;
         ++mInsertCount;

         if(mIn >= mEnd)
            {
            mHasWrapped = true;
            mIn -=(mEnd-mStart);
            }
         return S_OK;
         }

//Adds n data values, returning the number of values successfully added in nAdded
//Returns S_FALSE if not all n data values successfully added.
      HRESULT Add(ulong n, T* data, ulong *nAdded);


      ulong capacity() const 
         {
         return mLenMask;
         }
      ulong GetSpace() const;                   //Number of samples that can be added without the buffer over flowing.
      ulong GetMinCount() const;                //Number of samples buffered for the most advanced output enumerator.
      TInsertCountType GetInsertCount() const   //Total number of samples added to the ring buffer since it was last flushed.
         {
         return mInsertCount;
         }
               
      // Enumerators must not be accessed, nor Add called, during Flush() & Resize()
      void Flush();  //Reset the ringbuffer, clearing all data.
      void Resize(ulong newMinLength); // N.B. implies a Flush(), clearing out all the data

      Enum *GetEnumList() const 
         {
         return mOutputEnumList;
         }

      void SetIsFilling(bool filling)
         {
         mHRIsFilling = filling ? S_OK : S_FALSE;
         }

private:

   RingBuffer(const RingBuffer &other) // declared private to ensure compiler errors if external code tries to call it.
      {}

   ulong CalcPow2n(ulong minLength);
   void SetBufferMinSize(ulong minLength);

   T *mStart;
   T *mIn;
   T *mEnd;
   T *mBlockPos;

   ulong mLenMask;
   TInsertCountType mInsertCount;
   mutable TTickToSample mTickToSample; 

   mutable Enum *mOutputEnumList;   //Used to reference output enumerators so we can check for overflow
   HRESULT mHRIsFilling;
   bool mHasWrapped;
};

template <class T, class IEnum>
RingBuffer<T,IEnum>::RingBuffer(ulong minLength) : mStart(0)
   {
   mOutputEnumList = 0;
   mHasWrapped = false;
   mHRIsFilling = S_OK;
   SetBufferMinSize(minLength);
   }

template <class T, class IEnum>
RingBuffer<T,IEnum>::~RingBuffer()
   {
   MYASSERT(mOutputEnumList == 0);
   delete [] mStart;
   }


template <class T, class IEnum>
ulong RingBuffer<T,IEnum>::GetSpace() const
   {
   ulong minSpace = mLenMask;
   for(Enum *ptr = mOutputEnumList; ptr; ptr = ptr->mNext)
      {
      ulong space = ptr->GetSpace();
      if(space < minSpace)
         minSpace = space;
      }
   return minSpace;
   }


template <class T, class IEnum>
ulong RingBuffer<T,IEnum>::GetMinCount() const
   {
   ulong minCount = mLenMask;
   for(Enum *ptr = mOutputEnumList; ptr; ptr = ptr->mNext)
      {
      ulong count = ptr->GetCount();
      if(count < minCount)
         minCount = count;
      }
   return minCount;
   }
   
template <class T, class IEnum>
HRESULT RingBuffer<T,IEnum>::Add(ulong n, T* data, ulong *nAdded)
   {
   HRESULT hr = S_OK;
   ulong minSpace = GetSpace();
   if(n > minSpace)
      {
      n = minSpace;
      hr = S_FALSE;
      }

   if(mIn+n > mEnd)
      {// Wrapped
      ulong n1 = mEnd-mIn;
      memcpy(mIn, data, n1*sizeof(T));
      memcpy(mStart, data+n1,(n-n1)*sizeof(T));
      }
   else //no wrap
      memcpy(mIn, data, n*sizeof(T));

   mIn += n;
   mInsertCount += n;

   if(mIn >= mEnd)
      {
      mHasWrapped = true;
      mIn -=(mEnd-mStart);
      }
   *nAdded = n;
   return hr;
   }

template <class T, class IEnum>
ulong RingBuffer<T,IEnum>::CalcPow2n(ulong minLength)
   {
   ulong pow2n = 2;
   while(pow2n && pow2n < minLength)
      pow2n <<= 1;

   return pow2n;
   }


template <class T, class IEnum>
void RingBuffer<T,IEnum>::SetBufferMinSize(ulong minLength)
   {
   ulong pow2n = CalcPow2n(minLength);
   delete [] mStart;
   mIn = mStart = new T[pow2n];
   mEnd = mStart+pow2n;
   mBlockPos = mIn;
   mLenMask = pow2n-1;
   mInsertCount = 0;
   mHasWrapped = false;
   }
   

template <class T, class IEnum>
void RingBuffer<T,IEnum>::Flush()
   {
   mIn = mStart;
   mBlockPos = mIn;
   for(RingBuffer<T,IEnum>::Enum* pEnum = mOutputEnumList; pEnum; pEnum = pEnum->mNext)
      pEnum->mOut = mIn;

   mInsertCount = 0;
   mHasWrapped = false;
   }


template <class T, class IEnum>
void RingBuffer<T,IEnum>::Resize(ulong newMinLength)
   {
   MYASSERT(mOutputEnumList == 0); //Resizing invalidates all enumerators

   ulong pow2n = CalcPow2n(newMinLength);
   if(pow2n != mEnd - mStart)
      {
      delete [] mStart;
      mStart = new T[pow2n];
      mEnd = mStart+pow2n;
      mLenMask = pow2n-1;
      }

   Flush();
   }

      
}


#endif