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


#pragma once

#ifndef ADIIterator_H__
#define ADIIterator_H__

#include <stddef.h>  //ptrdiff_t
#include <limits>

#include "ADICOMPtr.h"
//#include "icharttypes.h"

//#include "ICalcEnum.h"

namespace ADI
{

/*
Helper class which holds onto an IEnumXXX or IEnumXXXEx style interface and 
locally buffers the data retrieved from Next() calls to make it easy to use 
the IEnumXXX interface efficiently. 
The public interface to ADI::Iterator is not STL compatible, but does wrap
up an enumerator so that it looks like a bidirectional iterator (i.e. pointer-like object). 
Typically usage:

for(;iter;++iter) 
   {
   sum += *iter;
   }
   
For sampling enumerators where the available number of samples
is not fixed, the CanAdvance() method should be called once before
entering a for(;mIter;++mIter) {...} style loop to process any new data.
This checks to see if new data is available and causes an invalid iterator
to become valid again of new samples are present.
The CanAdvance() call is not needed in the offline case, but will do no harm.
If you skip (using say, += ) this iterator back before the record start, or
beyond the current end of the record, it will become invalid (mIter==false).
When you skip or increment it forwards its position is limited to one past the
last valid sample. The first valid position is always 0. The Skip() method returns the
number of samples skipped.
It is important not to try to dereference it (*mIter) when it is invalid.
If it becomes invalid, you can make it valid again by skipping, decrementing or
incrementing it back into the valid range again, or calling CanAdvance().

The template parameter "kFillOnInit" is true by default, meaning that the buffer will be 
filled upon initialization and ready for data access.
If false, then the buffer will not be filled until an explicit call to CanAdvance() is made.

*/

const int kEnumIterDefaultBufSize = 16;

template<typename IEnum, bool kFillOnInit = true, int kBufSize = kEnumIterDefaultBufSize, template<class> class EnumIterTraits = EnumXXXTraits> class Iterator;


template<typename IEnum, bool kFillOnInit, int kBufSize, template<class> class EnumIterTraits >
class Iterator : public EnumIterTraits<IEnum>
{
public:
   typedef EnumIterTraits<IEnum> Base;
   typedef Iterator Self;
   typedef EnumIterTraits<IEnum> EnumTraits;
   typedef typename EnumIterTraits<IEnum>::XXXType T;
   typedef typename EnumIterTraits<IEnum>::PosType PosType;
   typedef typename EnumIterTraits<IEnum>::TCloneBase TCloneBase;
   

   explicit Iterator(IEnum *enumI = 0) :
      mOut(0),mStart(0),mEnd(0),mNPrevRet(0),mEndPos(0),mEnum(enumI),mHrIsFilling(S_OK),mCancelledPtr(0)
      {
      if(mEnum)
         AfterSetEnum();
      }
   explicit Iterator(AutoBool *cancelPtr) :
      mOut(0),mStart(0),mEnd(0),mNPrevRet(0),mEndPos(0),mHrIsFilling(S_OK),mCancelledPtr(cancelPtr)
      {
      if(mEnum)
         AfterSetEnum();
      }
      
      
         
   Iterator(const Iterator& other);
   
   template<typename T1>
   explicit Iterator(const ADI::impl::com_cast_t<T1> &other) throw()	:
         //Base(other),
         mOut(0),mStart(0),mEnd(0),mNPrevRet(0),mEndPos(0),
         mEnum(other), // Uses QueryInterface
         mHrIsFilling(S_OK),
         mCancelledPtr(0)
      {
      if(mEnum)
         AfterSetEnum();
      }
      
   ~Iterator()
      {
      EnumIterTraits<IEnum>::release(mStart,mEnd);
      }
   
   template<typename T1>
   Iterator& operator=(const ADI::impl::com_cast_t<T1>& other) throw()	// 0 is ok
      {   //safe in x = (COMPtrBase&)x case.
      //Base::operator =(other);
      mEnum = other;
      MYASSERT(mEnum);
      if(mEnum)
         AfterSetEnum();
      return *this;
      }
   
   void SetEnum(IEnum *enumI)
      {
      mEnum = enumI;
      if(mEnum)
         AfterSetEnum();
      }
      
   class Setter
      {
      public:
         explicit Setter(Self &parent) : mParent(parent) {}
         ~Setter()
            {
            if(mParent.mEnum)
               mParent.AfterSetEnum();
            }
         operator IEnum**() { return mParent.mEnum.Set();}
      private:
         //IEnum **mIPtr;
         Self &mParent;
      };
      
   Setter Set()
      {
      return Setter(*this);
      }
      
   typedef typename ::ADI::remove_const<IEnum>::type UnconstI;    
      
   class QuerySetter
      {
      public:
         explicit QuerySetter(Self &parent) : mParent(parent),mIUnk(0) {}
         ~QuerySetter()
            {
            if(mIUnk)
               {
               mIUnk->QueryInterface(COMType<IEnum>::uuidof(), reinterpret_cast<void**>(const_cast<UnconstI**>(mParent.mEnum.Set())));
               mIUnk->Release();
               if(mParent.mEnum)
                  mParent.AfterSetEnum();
               }
            }
         operator IUnknown**() 
            {
            return &mIUnk;
            }
         
         template<class Intf>      
         operator Intf**() 
            {
            MYASSERT(static_cast<Intf*>(mIUnk)==0); //Down cast from IUnknown to check Intf is derived from IUnknown
            return (Intf**)(&mIUnk);
            } 
      private:
         //IEnum **mIPtr;
         IUnknown *mIUnk;
         Self &mParent;
      };
      
   QuerySetter QuerySet()
      {
      return QuerySetter(*this);
      }
        
      
      
   IEnum* Get()
      {
      return mEnum.Get();
      }
      
   const IEnum* Get() const
      {
      return mEnum.Get();
      }

   void Clear()
      {
      mEnum.Clear ();
      }
      
   Self& NextMax(uint maxToGet)
      {
      if(++mOut >= mEnd)
         {
         if(mNPrevRet == kBufSize) 
            FillBufForward(maxToGet);
         else
            {//Last FillBufForward didn't fill buffer so there will be no more until loop is exited (CanAdvance() must be called prior to entering loop again).
            EnumIterTraits<IEnum>::release(mStart,mEnd);
            mEnd = mStart = mOut = mBuf;  
            mNPrevRet = 0; //Indicate not deferencable
            }
         }
      return *this;
      }      
      
   Self& operator++()
      {
      if(++mOut >= mEnd)
         FillBufForward();
      return *this;
      }
      
   Self& operator--()
      {
      if((mOut--) - mStart <= 0) // difference ensures signed pointer arithmetic
         FillBufBackward();
      return *this;
      }
   
   bool CanDeRef() const
      {
      //if(kFillOnInit)
      //   return mNPrevRet!=0;
      //return mNPrevRet!=0 || FillBufForward();
      return mNPrevRet!=0; 
      }
      
   ulong GetNReturnedByLastNext() const
      {
      return mNPrevRet;
      }      
            
   operator const void*() const throw()//safe conversion to bool
      {
      return reinterpret_cast<const void*>(CanDeRef());
      }
      
   bool HasEnum() const
      {
      return mEnum;
      }
            
//Iterator can be invalid for two reasons
//  1. Out of range
//  2. Underlying data is missing (empty block of record)
   //bool HasData() const
   //   {
   //   return mEnum;
   //   }
      
   T operator*() const
      {
      MYASSERT(CanDeRef());
      return *mOut;
      }
      
   // Smart pointer
   T* operator->() const throw()
      {
      MYASSERT(CanDeRef());
      return mOut;
      }
//Used in Online case before entering a loop running forward e.g.
//if(mIter.CanAdance())
//   {
//   for(;mIter;++mIter)
//      mSum += *mIter;
//   }
   bool CanAdvance(uint maxToGet = std::numeric_limits<uint>::max())
      {
      return mNPrevRet!=0 || FillBufForward(maxToGet);
      }

   HRESULT GetHrIsFilling() const
      { return mOut < mEnd? S_OK : mHrIsFilling;}

	HRESULT IsFilling(AutoBool *isFilling) const
	   {
	   HRESULT hr = GetHrIsFilling();
	   *isFilling = hr==S_OK;
	   return hr;
	   }     

   HRESULT SetInitialPosition(TTickIndex offset);
   HRESULT SetInitialPosition64(TTickIndex64 offset);
   
   ///// Changes the tick to pix phase, resets the position to pixel 0 and tick start, and sets the end limit to end.
   //HRESULT SetTickRange(TGenericFlags flags, double tickAtPixZero, TTickIndex start, TTickIndex end, TPixIndex *pixAtSampleZero)
   //   {
   //   EnumIterTraits<IEnum>::release(mStart,mEnd); //Just in case buffer had interface pointers in it already
   //   mOut = mStart = mEnd = 0;
   //   mNPrevRet = 0;
   //   mEndPos = 0;
   //   HRESULT hr = E_FAIL;
   //   if(mEnum)
   //      {
   //      hr = mEnum->SetTickRange(flags,tickAtPixZero, start, end, pixAtSampleZero);
   //      EnumIterTraits<IEnum>::GetPosition(mEnum.Get(), &mEndPos);
   //      }
   //   return hr;
   //   }


   PosType GetPosition() const
      {
      return mEndPos-(mEnd-mOut);
      }

   bool GetPosition(PosType *pos) const
      {
      *pos = GetPosition();
      return CanDeRef();
      }
      
   HRESULT SkipEx(PosType n,PosType *nSkipped)
      {
      *nSkipped = Skip(n);
      return n == *nSkipped?S_OK:GetHrIsFilling();
      }

   void Reset()
      {
      CAFVERIFY(mEnum->Reset()==S_OK);
      mEndPos = 0;
      if(EnumIterTraits<IEnum>::IsEnumEx())
         CAFVERIFY(mEnum->GetPosition(&mEndPos)==S_OK);
      FillBufForward();
      }

   PosType Skip(PosType n) //returns number skipped
      {
      MYASSERT(mEnum.IsValid());
      if(n >= mEnd-mOut || n < mStart-mOut) //BL 20456: Iterator::Skip(n) and ConstBiIterBase::Skip(n) broken for large n
         {
         PosType skipped = 0; //no. of valid samples skipped
         PosType nToSkip = n-(mEnd-mOut); //reduce by the number of in buffer samples skipped.
         PosType enumSkipped = 0;
         if(mEnum)
            {
            mHrIsFilling = mEnum->SkipEx(nToSkip, &enumSkipped); 
            mEndPos += enumSkipped;
            skipped = enumSkipped + (mEnd-mOut); //increase by the number of in buffer samples skipped.
#ifdef _DEBUG
            PosType enumEndPos;
            EnumIterTraits<IEnum>::GetPosition(mEnum.Get(), &enumEndPos); //IEnumXXX's are assumed to start at position 0.
            MYASSERT(enumEndPos == mEndPos); 
#endif
            }
         if(enumSkipped == nToSkip)
            {//Skip was successful
            FillBufForward(); //sets mOut
            return skipped;
            }
         
         mOut = mEnd;  //Limit position for +ve and -ve skips
         EnumIterTraits<IEnum>::release(mStart,mEnd);
         mStart = mEnd;  //For mOut<mEnd, -ve skip failed, but we don't limit position,
         mNPrevRet = 0;  // that, e.g.  for(;mIter;mIter-=2); will terminate
         return skipped;
         }
      else
         mOut += n; //Skip within buffer   
      return n;
      }
      
   bool SynchWithEnum()
      {
      if(!mEnum)
         {
         //ADIASSERT0();
         return false;
         }
      AfterSetEnum();
      return true;
      }
      
protected:
   void CopyMembers(const Iterator& other);   

//Hide this because it does NOT mean the same thing as COMPtr<>:: IsValid()!!
//   bool IsValid() const
//      {
////      CHECK((mNPrevRet!=0) == (mOut < mEnd && mOut >= mStart));
//      return mNPrevRet!=0;
//      }

   void AfterSetEnum();
   bool FillBufForward(uint maxToGet = std::numeric_limits<uint>::max());
   void FillBufBackward();
//   void* operator new(size_t size, void *ptr)
//      {return ptr;}

//not implemented for efficiency reasons.
   const Self operator++(int);
   const Self operator--(int);
//may implement
   Self& operator=(const Self& other);

   T *mOut;
   T *mStart;
   T *mEnd;
   ulong mNPrevRet;   //no. of values returned by last call of Next()
   PosType mEndPos;     //Should track the internal Enum position
   ADI::COMPtr<IEnum> mEnum;
   HRESULT mHrIsFilling;
   AutoBool *mCancelledPtr;
   T mBuf[kBufSize];  
};


template<typename IEnum, bool kFillOnInit, int kBufSize, template<class> class EnumIterTraits >
Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>::Iterator(const Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>& other) :
//   Base(other),
   mCancelledPtr(0)
{
CopyMembers(other);
}
   
template<typename IEnum, bool kFillOnInit, int kBufSize, template<class> class EnumIterTraits >
void Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>::CopyMembers(const Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>& other)   
{
if(other.mEnum.IsValid())
   {
   MYASSERT(0); //this is O.K. but potentially inefficient if happens all the time.
   other.mEnum->Clone((TCloneBase**)mEnum.Set());
   ptrdiff_t offset = mBuf-other.mBuf;
   mOut = other.mOut + offset;
   mStart = other.mStart + offset;
   mEnd = other.mEnd + offset;
   mNPrevRet = other.mNPrevRet;
   mEndPos = other.mEndPos;
   mHrIsFilling = other.mHrIsFilling;
//   memcpy(mStart,other.mStart,mNPrevRet*sizeof(T));
   EnumIterTraits<IEnum>::copy(other.mStart,other.mEnd,mStart);//srcStart,srcEnd,destStart
   }
else
   {
   mEnum.Clear();
   mOut = mEnd = mStart = 0;
   mEndPos = 0;
   mNPrevRet = 0;
   mHrIsFilling = S_OK;
   }
}

template<typename IEnum, bool kFillOnInit, int kBufSize, template<class> class EnumIterTraits >
Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>& Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>::operator=(const Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>& other)
{ //Derived classes adding data members need to provide their own operator=()
if(&other != this)
   {
   Base::operator = (other);
   this->CopyMembers(other);
   //Self::~Self();
   //new (this) Self(other);
   }
return *this;
}


template<typename IEnum, bool kFillOnInit, int kBufSize, template<class> class EnumIterTraits >
void Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>::AfterSetEnum()
{
//mEnum = enumI;
EnumIterTraits<IEnum>::release(mStart,mEnd);
mOut = mStart = mEnd = 0;
mNPrevRet = 0;
mEndPos = 0;
mHrIsFilling = S_OK;
if(mEnum.IsValid())
   {
   EnumIterTraits<IEnum>::GetPosition(mEnum.Get(), &mEndPos); //IEnumXXX's are assumed to start at position 0.

   if(kFillOnInit)
      FillBufForward();
   }
}

template<typename IEnum, bool kFillOnInit, int kBufSize, template<class> class EnumIterTraits >
HRESULT Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>::SetInitialPosition(TTickIndex offset)
{
MYASSERT(mStart == mEnd && mStart == mOut && mStart == 0);  // check buffer just initialised, contains no data - you should check kFillOnInit is false if this fires
EnumIterTraits<IEnum>::release(mStart,mEnd); //Just in case buffer had interface pointers in it already
mOut = mStart = mEnd = 0;
mNPrevRet = 0;
mEndPos = offset;
ADI::COMPtr<ICalcEnum>  calcEnumI(ADI::query_cast(mEnum.Get()));
if (calcEnumI)
   return calcEnumI->SetInitialPosition(offset);
   
if(mEnum)
   {
   EnumIterTraits<IEnum>::GetPosition(mEnum.Get(), &mEndPos);

   if (mEndPos != offset)
      {
      PosType  nSkipped(0);
      HRESULT hr = mEnum->SkipEx(offset-mEndPos,&nSkipped);
      MYASSERT(offset-mEndPos == nSkipped);
      mEndPos += nSkipped;
      return hr;
      }
   return S_OK;
   }
MYASSERT(0);
return E_FAIL;
}

template<typename IEnum, bool kFillOnInit, int kBufSize, template<class> class EnumIterTraits >
HRESULT Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>::SetInitialPosition64(TTickIndex64 offset)
   {
   MYASSERT(mStart == mEnd && mStart == mOut && mStart == 0);  // check buffer just initialised, contains no data - you should check kFillOnInit is false if this fires
   EnumIterTraits<IEnum>::release(mStart,mEnd); //Just in case buffer had interface pointers in it already
   mOut = mStart = mEnd = 0;
   mNPrevRet = 0;
   mEndPos = offset;
   ADI::COMPtr<ICalcEnum64>  calcEnumI(ADI::query_cast(mEnum.Get()));
   if (calcEnumI)
      return calcEnumI->SetInitialPosition64(offset);
      
   MYASSERT(ADI::COMPtr<ICalcEnum>(ADI::query_cast(mEnum.Get()))==0); //Mixing 64 bit CalcEnums with 32 bit CalcEnums is not supported! Write a 64 bit version of the 32 bit CalcEnum!    

   if(mEnum)
      {
      EnumIterTraits<IEnum>::GetPosition(mEnum.Get(), &mEndPos);

      if (mEndPos != offset)
         {
         PosType  nSkipped(0);
         HRESULT hr = mEnum->SkipEx(offset-mEndPos,&nSkipped);
         MYASSERT(offset-mEndPos == nSkipped);
         mEndPos += nSkipped;
         return hr;
         }
      return S_OK;
      }
   MYASSERT(0);
   return E_FAIL;
   }


template<typename IEnum, bool kFillOnInit, int kBufSize, template<class> class EnumIterTraits >
bool Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>::FillBufForward(uint maxToGet)
{
MYASSERT(mEnum.IsValid());

EnumIterTraits<IEnum>::release(mStart,mEnd);

//mHrIsFilling  = mEnum->Next(kBufSize,mBuf,&mNPrevRet);
if(maxToGet > kBufSize)
   maxToGet = kBufSize;
mNPrevRet = 0;
if(mEnum && (!mCancelledPtr || !*mCancelledPtr))
   mHrIsFilling  = Base::Next(mEnum.Get(),maxToGet,mBuf,&mNPrevRet);
mEndPos += mNPrevRet;
mEnd = mBuf+mNPrevRet;
mStart = mOut = mBuf;

//#ifdef _DEBUG
//TTickIndex enumPos;
//mEnum->GetPosition(&enumPos);
//ADIASSERT(enumPos-mNPrevRet == GetPosition());
//#endif

return (mNPrevRet != 0);
}

template<typename IEnum, bool kFillOnInit, int kBufSize, template<class> class EnumIterTraits >
void Iterator<IEnum,kFillOnInit,kBufSize,EnumIterTraits>::FillBufBackward()
{
MYASSERT(mEnum.IsValid());

EnumTraits::release(mStart,mEnd);

long nNew = 0;
if(!mCancelledPtr || !*mCancelledPtr)
   {
   PosType nSkipped;
   mEnum->SkipEx(-(int)(kBufSize+mNPrevRet),&nSkipped);
   mEndPos += nSkipped;
   nNew = -nSkipped-mNPrevRet; // no. of new samples available
   }

if(nNew > 0)
   {
   //mHrIsFilling = mEnum->Next(nNew,mBuf,&mNPrevRet);
   mHrIsFilling  = EnumTraits::Next(mEnum.Get(),nNew,mBuf,&mNPrevRet);

   mEndPos += mNPrevRet;
   mEnd = mBuf+mNPrevRet;
   mOut = mEnd-1;
   mStart = mBuf;
   }
else
   { //make iterator invalid
   mEnd = mStart;
   mNPrevRet = 0;
   }
}

//returns number skipped.
//template<typename IEnum, bool kFillOnInit, int kBufSize, template<class> class EnumIterTraits >
//typename Iterator<IEnum,kBufSize,EnumIterTraits>::PosType Iterator<IEnum,kBufSize,EnumIterTraits>::Skip(PosType n)
//{
//ADIASSERT(mEnum.IsValid());
//if((mOut += n) >= mEnd || mOut < mStart)
//   {
//   PosType nSkipped;
//   mHrIsFilling = mEnum->SkipEx(mOut-mEnd, &nSkipped);
//   mEndPos += nSkipped;
//   #ifdef _DEBUG
//   PosType enumEndPos;
//   EnumIterTraits<IEnum>::GetPosition(mEnum.Get(), &enumEndPos); //IEnumXXX's are assumed to start at position 0.
//   ADIASSERT(enumEndPos == mEndPos); 
//   #endif
//   mOut -= nSkipped;
//   PosType skipped = n-(mOut-mEnd);  //no. of valid samples skipped
//   if(mOut == mEnd)
//      {//Skip was successful
//      FillBufForward();
//      return skipped;
//      }
//   //Skip failed
//   
//   //else if(mOut > mEnd)
//   //   mOut = mEnd; //+ve skip failed - limit position to one past last valid sample
//   //else
//   //   {
//   //   ADIASSERT0(); //Maybe it would be better to limit position?
//   //   skipped = n; //-ve skip failed - don't limit position
//   //   }
//   
//   mOut = mEnd;  //Limit position for +ve and -ve skips
//   EnumIterTraits<IEnum>::release(mStart,mEnd);
//   mStart = mEnd;  //For mOut<mEnd, -ve skip failed, but we don't limit position,
//   mNPrevRet = 0;  // that, e.g.  for(;mIter;mIter-=2); will terminate
//   return skipped;
//   }
//return n;
//}

   
}//namespace

#endif