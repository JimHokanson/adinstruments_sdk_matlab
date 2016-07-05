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


#ifndef SimpleUnknownImp_H__
#define SimpleUnknownImp_H__

#include "adidat/include/ADIBaseTypes.h"

#if !defined( _OBJBASE_H_ ) && !defined(ADI_DISABLE_ATL)
#include <objbase.h>
#endif

#include "ADIIDLStuff.h"	// for COMType, a compiler independent way of associating IID's with COM Interfaces

namespace ADICOM
{


/** class for use in ctors of COM objects, before an external strong reference exists, particularly when using
aggregation, to ensure the object is not deleted by a call to Release().
*/
template<class T>
class InternalRef
   { //Hold a temporary reference without deleting obj in Release().
   public:
      InternalRef(T *obj) : mObj(obj)
         {
         mObj->IncRef();
         }

      ~InternalRef()
         {
         mObj->DecRef();
         }
   private:
      T *mObj;   

   };


/** SimpleUnknownImp, one base interface.
*/
template<class I1>
class SimpleUnknownImp1 : public I1
   {
   public:
      SimpleUnknownImp1() : mNRefs(0) 
         {
         }
      SimpleUnknownImp1(const SimpleUnknownImp1& other) : mNRefs(0) {}
      virtual ~SimpleUnknownImp1() 
         {
         }

      SimpleUnknownImp1& operator=(const SimpleUnknownImp1 &other)
         {
         return *this;
         }

      virtual ULONG _IFUNC AddRef()
         { 
         return IncRef();
         }

      virtual ULONG _IFUNC Release()
         {
         return DoRelease();
         }

      ULONG DoRelease()
         {
         ulong result = DecRef();
         MYASSERT(long(result)>=0);
         if(result == 0)
            delete this;
         return result;
         }

      virtual HRESULT _IFUNC QueryInterface(const IID& iid, void **out)
         {
         *out = 0;
         if(iid == COMType<IUnknown>::uuidof())
            *out = static_cast<IUnknown*>(this);
         else if(iid == COMType<I1>::uuidof())
            *out = static_cast<I1*>(this);
         else
            return E_NOINTERFACE;

         ((IUnknown*)*out)->AddRef();
         return S_OK;
         }

      ulong IncRef() const
         { 
         ULONG result = ::InterlockedIncrement(&mNRefs);
         return result;
         }

      ulong DecRef() const //N.B. does not delete (same as ATL's InternalRelease()).
         {
         ULONG result = ::InterlockedDecrement(&mNRefs);
         return result;      
         }
      long GetNRef() const {return mNRefs;}
   protected:
      mutable long mNRefs;
   };

template<class I1, class I2>
class SimpleUnknownImp2 : public SimpleUnknownImp1<I1>, public I2
   {
   public:
      HRESULT _IFUNC QueryInterface(const IID& iid, void **out)
         {
         *out = 0;
         if(iid == COMType<IUnknown>::uuidof())
            *out = static_cast<IUnknown*>(static_cast<I1*>(this));
         else if(iid == COMType<I1>::uuidof())
            *out = static_cast<I1*>(this);
         else if(iid == COMType<I2>::uuidof())
            *out = static_cast<I2*>(this);
         else
            return E_NOINTERFACE;
         ((IUnknown*)*out)->AddRef();
         return S_OK;
         }

      virtual ULONG _IFUNC AddRef()
         { 
         return this->IncRef();
         }

      virtual ULONG _IFUNC Release()
         {
         return this->DoRelease();
         }
   };

/*
For the case where interface I1 derives from interface QI1 and we wish to
support QueryInferface succeeding for both I1 and QI1.
*/
template<class I1, class QI1>
class SimpleUnknownImp1_1 : public SimpleUnknownImp1<I1>
   {
   public:
      HRESULT _IFUNC QueryInterface(const IID& iid, void **out)
         {
         //Interfaces here are not inherited - QI only.
         if(iid == COMType<QI1>::uuidof())
            *out = static_cast<QI1*>(this);
         else
            return SimpleUnknownImp1<I1>::QueryInterface(iid, out);
         ((IUnknown*)*out)->AddRef();
         return S_OK;
         }

      virtual ULONG _IFUNC AddRef()
         { 
         return this->IncRef();
         }

      virtual ULONG _IFUNC Release()
         {
         return this->DoRelease();
         }
   };

}//namespace

#endif