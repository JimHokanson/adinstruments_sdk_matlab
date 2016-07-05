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

#ifndef __ADICOMPtr_h
#define __ADICOMPtr_h

#include <algorithm>  //for std::swap
//#include <boost/type_traits.hpp>

#include "Utility/myassert.h"

#ifdef ADI_TARGET_OS_MAC
#include <Winerror.h> // [sic] for S_OK
#endif

// See comments below (just before ADI::COMPtr definition).

namespace ADI
{

template<typename T>
class remove_const
{
private:

   template<class U> struct UnConst
      {
      typedef U Result;
      };   
   template<class U> struct UnConst<const U>
      {
      typedef U Result;
      };   
public:

   typedef typename UnConst<T>::Result type;
};

//using ::boost::remove_const;
using ::ADI::remove_const;

/**
 *  Reference counted owner policy for COMPtr.
 */
template<class I>
class COMRefCount
{
public:

typedef typename remove_const<I>::type UnconstI;

class QuerySetter
   {
   friend class COMRefCount;
   public:
      ~QuerySetter()
         {
         if(mIUnk)
            {
            mIUnk->QueryInterface(COMType<I>::uuidof(), reinterpret_cast<void**>(const_cast<UnconstI**>(mIPtr)));
            mIUnk->Release();
            }
         }
      operator IUnknown**() { return &mIUnk;}

      template<class Intf>      
      operator Intf**() 
         {
         MYASSERT(static_cast<Intf*>(mIUnk)==0); //Down cast from IUnknown to check Intf is derived from IUnknown
         return (Intf**)(&mIUnk);
         } 

   private:
      explicit QuerySetter(I **pi) : mIPtr(pi),mIUnk(0) {}
      I **mIPtr;
      IUnknown *mIUnk;
   };


typedef I** SetterType;
typedef QuerySetter QuerySetterType;

static I* DoBind(I *i)
   {
   return DoCopy(i);
   }
   
static SetterType DoSet(I **i)
   {
   return i;
   }
   
static QuerySetter DoQuerySet(I **i)
   {
   return QuerySetter(i);
   }

static I* DoCopy(I *i)
   {
   if(i)
      const_cast<UnconstI*>(i)->AddRef();
   return i;
   }
   
static void DoRelease(I *i)
   {
   if(i)
      const_cast<UnconstI*>(i)->Release();
   }
   
template<class Iin>   
static void DoQuery(Iin *in, I **out)
   {
   *out = 0;
   // This typedef makes it easier to get various compilers to cope with the following cast (needed tweaks for CodeWarrior and GCC)
   typedef typename remove_const<Iin>::type* tempType;
   if(in)
      const_cast<tempType>(in)->
         QueryInterface(COMType<I>::uuidof(), reinterpret_cast<void**>(const_cast<UnconstI**>(out)));
   }
};

template<class I>
class COMWeak
{
public:

typedef typename remove_const<I>::type UnconstI;


   class Setter
      {
      friend class COMWeak<I>;
      public:
         ~Setter()
            {
            if(*mIPtr)
               {
               int refs = const_cast<UnconstI*>(*mIPtr)->Release();
               MYASSERT(refs!=0); //Verify it wasn't deleted
               }
            }
         operator I**() { return mIPtr;}
      private:
         explicit Setter(I **pi) : mIPtr(pi) {}
         I **mIPtr;
      };


   class QuerySetter
      {
      friend class COMWeak;
      public:
         ~QuerySetter()
            {
            if(*mIPtr)
               {
               int refs = const_cast<UnconstI*>(*mIPtr)->Release();
               MYASSERT(refs!=0); //Verify it wasn't deleted
               const_cast<UnconstI*>(*mIPtr)->QueryInterface(COMType<I>::uuidof(), reinterpret_cast<void**>(const_cast<UnconstI**>(mIPtr)));
               if(*mIPtr)
                  {
                  int refs = const_cast<UnconstI*>(*mIPtr)->Release();
                  MYASSERT(refs!=0); //Verify it wasn't deleted
                  }
               }
            }
         operator IUnknown**() { return (IUnknown**)mIPtr;}
         
         template<class Intf>      
         operator Intf**() 
            {
            MYASSERT(static_cast<Intf*>(this->mIUnk)==0); //Down cast from IUnknown to check Intf is derived from IUnknown
            return (Intf**)(&this->mIUnk);
            } 
         
      private:
         explicit QuerySetter(I **pi) : mIPtr(pi) {}
         I **mIPtr;
      };
      
   typedef Setter SetterType;
   typedef QuerySetter QuerySetterType;


static I* DoBind(I *i)
   {
   return i;
   }
   
static SetterType DoSet(I **i)
   {
   return Setter(i);
   }
   
static QuerySetterType DoQuerySet(I **i)
   {
   return QuerySetter(i);
   }

static I* DoCopy(I *i)
   {
   return i;
   }
   
static void DoRelease(I *i)
   {
   }

template<class Iin>   
static void DoQuery(Iin *in, I **out)
   {
   *out = 0;
   // This typedef makes it easier to get various compilers to cope with the following cast (needed tweaks for CodeWarrior and GCC)
   typedef typename remove_const<Iin>::type* tempType;
   if(in)
      const_cast<tempType>(in)->
         QueryInterface(COMType<I>::uuidof(), reinterpret_cast<void**>(const_cast<UnconstI**>(out)));
   if(*out)
      const_cast<UnconstI*>(*out)->Release();
   }

};


template<class I>
class COMClone
{
public:

typedef typename remove_const<I>::type UnconstI;

class QuerySetter
   {
   friend class COMClone;
   public:
      ~QuerySetter()
         {
         if(mIUnk)
            {
            mIUnk->QueryInterface(COMType<I>::uuidof(), reinterpret_cast<void**>(const_cast<UnconstI**>(mIPtr)));
            mIUnk->Release();
            }
         }
      operator IUnknown**() { return &mIUnk;}
      
      template<class Intf>      
      operator Intf**() 
         {
         MYASSERT(static_cast<Intf*>(mIUnk)==0); //Down cast from IUnknown to check Intf is derived from IUnknown
         return (Intf**)(&mIUnk);
         }
          
   private:
      explicit QuerySetter(I **pi) : mIPtr(pi),mIUnk(0) {}
      I **mIPtr;
      IUnknown *mIUnk;
   };


typedef I** SetterType;
typedef QuerySetter QuerySetterType;

static QuerySetter DoQuerySet(I **i)
   {
   return QuerySetter(i);
   }


static I* DoBind(I *i)
   {
   if(i)
      const_cast<UnconstI*>(i)->AddRef();
   return i;
   }
   
//Derived class Set() must call Clear() before this   
static SetterType DoSet(I **i)
   {
   return i;
   }

static I* DoCopy(I *i)
   {
   if(i)
      {
      I *tmp = 0;
      const_cast<UnconstI*>(i)->Clone(&tmp);
      i = tmp;
      }
   return i;
   }
   
static void DoRelease(I *i)
   {
   if(i)
      const_cast<UnconstI*>(i)->Release();
   }
   
template<class Iin>   
static void DoQuery(Iin *in, I **out)
   {
   *out = 0;
   // This typedef makes it easier to get various compilers to cope with the following cast (needed tweaks for CodeWarrior and GCC)
   typedef typename remove_const<Iin>::type* tempType;
   if(in)
      const_cast<tempType>(in)->
         QueryInterface(COMType<I>::uuidof(), reinterpret_cast<void**>(const_cast<UnconstI**>(out)));
   }

};

//template<class I>
//I* COMClone<I>::DoCopy(I *i)
//{
//if(i)
//   {
//   //I *tmp = 0;
//   //const_cast<UnconstI*>(i)->Clone(&tmp);
//   //const_cast<UnconstI*>(i)->Release();
//   //i = tmp;
//   }
//return i;
//}



//template<class I>
//I* COMClone<I>::DoCopy(I *i)
//{
//if(i)
//   {
//   //I *tmp = 0;
//   //const_cast<UnconstI*>(i)->Clone(&tmp);
//   //const_cast<UnconstI*>(i)->Release();
//   //i = tmp;
//   }
//return i;
//}


/**
 *  The standard ref-counted COM pointer.
 */
template<typename T, template<class> class OwnerPolicy = COMRefCount> class COMPtr;


namespace impl 
	{
   template<typename Itf> class com_cast_t 
      {
      public:
         explicit com_cast_t(Itf* p) : ptr_(p) {};
         Itf* Get() const { return ptr_; }
      private:
         Itf* ptr_;
         com_cast_t& operator=(const com_cast_t&);
      };



   }

// Metrowerks does not like plain typename for OP
//template<typename Itf, typename OP> inline impl::com_cast_t<Itf> query_cast(const COMPtr<Itf,OP>& t) { return impl::com_cast_t<Itf>(t.Get()); }
template<typename Itf, template<class> class OP> inline impl::com_cast_t<Itf> query_cast(const COMPtr<Itf,OP>& t) { return impl::com_cast_t<Itf>(t.Get()); }
template<typename Itf> inline impl::com_cast_t<Itf> query_cast(Itf* t) { return impl::com_cast_t<Itf>(t); }
   

/**
 *   Implement a Smart Pointer for COM interfaces.
 *
 *
 * Usage:
 * Normal strong reference to COM object - AddRefs on copy and assignment
 *
 *  ADI::COMPtr<ISomeInterface> myPtr;
 *
 *  To construct using QueryInterface from pointer of different type:
 *
 *  ISomeOther *other;
 *  or
 *  ADI::COMPtr<ISomeOther> other;
 *  ...
 *  ADI::COMPtr<ISomeInterface> myPtr(ADI::query_cast(other)); //remember to check myPtr is valid before using it in case QI failed.
 *
 *  The ownership policy used by COMPtr defaults to COMRefCount.
 *  Other policies can be substituted for the 2nd template param to change the behavour .e.g.
 *
 *  ADI::COMPtr<T,ADI::COMWeak> myPtr;
 *
 *  gives a pointer for holding weak references to the owner COM object from within
 *  an owned COM object so as to avoid circular reference deadlocks. Calls Release()
 *  on interfaces returned as out params from, say QueryInterface() so be careful
 *  that these objects already have at least one strong reference somewhere else.
 *  
 *  ADI::COMPtr<T,ADI::COMClone> myPtr
 *  
 *  gives a pointer which calls T->Clone(T** out); when a smart pointer is copied or assigned
 *  to it, but not when it is initialised with a raw interface pointer.
 *  
 *  COMPtrs with different ownership policies can be copied and assigned to one another.
 *
 */
template<typename T, template<class> class OwnerPolicy>
class COMPtr
{
public:

   typedef OwnerPolicy<T> OP;

   typedef typename remove_const<T>::type UnconstT;
   
   COMPtr() throw()  : mInterface(0){}

   /**
    *  Not a virtual destructor, derive with extreme care!
    */
   ~COMPtr() throw()
      {
      OP::DoRelease(mInterface);
      #if __DEBUG > 0
      reinterpret_cast<intptr_t &>(mInterface) = -1;
      #endif
      }

   COMPtr(const COMPtr& other) throw():
      mInterface(OP::DoCopy(other.mInterface))
      {
      }

   explicit COMPtr(T* i) throw():
      mInterface(OP::DoBind(i))
      {
      }
   
   /**
    *  Reference (force non-cloning).
    */
   void Reference(T* t) 
      {
      COMPtr temp(t);  //OP::DoBind(i)
      swap(temp);
      }	// 0 is ok

   /**
    *  Clone (like reference, but force clone).
    */
   void Clone(T* t) // 0 is ok
      {
      if (t && t != mInterface)
         t->Clone(Set());
      }
      
//Should remove this!!!
//   explicit COMPtr (T &i) throw():
////   explicit COMPtr (const impl::no_addref_t<T> &i) throw():
//      mInterface(&i.Get())
//      {
//      }
//      

   //Up-cast ctor - upcast without QI  
   //template<typename T1>  
   //COMPtr(const COMPtr<T1> &other) throw() : 
   //   mInterface(OP::DoCopy(static_cast<T*>(other.Get()));
   //   {	
   //   }
      
   template<typename T1, template<class> class OP1>
   COMPtr(const COMPtr<T1, OP1> &other) :
      //mInterface(OP::DoCopy(static_cast<T*>(other.Get())))
      mInterface(OP::DoCopy(other.Get()))
      {	
      }

   
   /**
    *  Casting constructor.  
    *
    *  Usage:
    *  COMPtr<I2> pI2;
    *   ...
    *   COMPtr<I1> pI1(query_cast(pI2)); //Does QueryInterface.
    */
   template<typename T1>
   COMPtr(const impl::com_cast_t<T1> &other) throw()	// Uses QueryInterface
      {
      OP::DoQuery(other.Get(), &mInterface);
      }
   
   
   void swap(COMPtr &other) throw()
      {
      std::swap(mInterface,other.mInterface);
      }

   COMPtr& operator=(const COMPtr &other) throw()
      {
      COMPtr temp(other);
      swap(temp); 
      return *this;
      }
   
   //Up-cast assignment   
   //template<typename T1>
   //COMPtr& operator=(const COMPtr<T1> &other) throw()
   //   {
   //   COMPtr temp(other);
   //   swap(temp); 
   //   return *this;
   //   }
      
   template<typename T1, template<class> class OP1>
   COMPtr& operator=(const COMPtr<T1,OP1> &other) throw()
      {
      COMPtr temp(other);
      swap(temp); 
      return *this;
      }

   COMPtr& operator=(T *t) throw()  //Same interface type - no need for QI
      {
      COMPtr temp(t);
      swap(temp); 
      return *this;
      }

  
   /**
    *  QueryInterface assignment.
    *  Usage:
    *   pI1 = query_cast(pI2);
    */
   template<typename T1>
   COMPtr& operator=(const impl::com_cast_t<T1>& other) throw()	// 0 is ok
      {   //safe in x = (COMPtrBase&)x case.
      COMPtr temp(other);
      swap(temp);
      return *this;
      }
   
   
   void Clear() throw()
      {
      OP::DoRelease(mInterface);
      mInterface=0;
      }

   bool IsValid() const throw()
      {
      MYASSERT((reinterpret_cast<const intptr_t &>(mInterface) != -1)); //Make sure it hasn't been destroyed
      return mInterface!=0;
      }
   
   operator const void*() const throw()//safe conversion to bool
      {
      MYASSERT((reinterpret_cast<const intptr_t &>(mInterface) != -1)); //Make sure it hasn't been destroyed
      return mInterface;
      }
   
	void Bind(T* i) throw()
	   {
	   COMPtr temp(i);
	   swap(temp);
	   }
	
   
   /**
    *  Smart pointer
    */
   T* operator->() const throw()
      {
      // Make sure interface has been assigned and hasn't been destroyed
      MYASSERT ((mInterface != 0) && (reinterpret_cast<intptr_t>(mInterface) != -1));
      return mInterface;
      }
   T& operator*() const throw()
      {
      // Make sure interface has been assigned and hasn't been destroyed
      MYASSERT ((mInterface != 0) && (reinterpret_cast<intptr_t>(mInterface) != -1));
      return *mInterface;
      }

   // Explicit (conservative) versions of operators
   typename OP::SetterType Set() throw()					// aka operator & (), "GetMessage (&a)" becomes "GetMessage (a.Set ())"
      {
      Clear(); 
      return OP::DoSet(&mInterface);
      }
   typename OP::QuerySetterType QuerySet() throw()	 // aka operator & (), "GetMessage (&a)" becomes "GetMessage (a.QuerySet ())" for IUnknown out parameters
      {
      Clear(); 
      return OP::DoQuerySet(&mInterface);
      }
   T* Get() const throw()			// aka operator T* (), "UseMessage (a)" becomes "UseMessage (a.Get ())"
      {
      MYASSERT((reinterpret_cast<const intptr_t  &>(mInterface) != -1)); //Make sure it hasn't been destroyed
      return mInterface;
      }
   T** GetSet() throw()				// aka operator & (), "UpdateMessage (&a)" becomes "UpdateMessage (a.GetSet ())"
      {
      return &mInterface;
      }

   template<typename T1>
   void GetOut(T1** out) const throw()
      {//Even a WeakCOMPtr needs an AddRef() here
      if(mInterface != 0)
         {
         MYASSERT((reinterpret_cast<const intptr_t &>(mInterface) != -1)); //Make sure it hasn't been destroyed      
         const_cast<UnconstT*>(mInterface)->AddRef();
         }
      *out = static_cast<T1*>(mInterface);
      }
      
   //More efficient than GetOut() if the COMPtr is not needed afterwards.
   template<typename T1>
   void Transfer(T1** out) throw()
      {
      *out = static_cast<T1*>(mInterface);
      mInterface = 0;
      }
      

   void GetInOut(T** inOut) const throw()
      {//Even a WeakCOMPtr needs a Release() here
      if(*inOut != 0)
         const_cast<UnconstT*>(*inOut)->Release();
      GetOut(inOut);
      }
         
   // Have assign too, like STL
   HRESULT Assign (const COMPtr& other) throw() 
      {
      Bind(other.Get()); 
      return S_OK;
      }
   HRESULT Assign (T* t) throw() 
      {
      Bind(t); 
      return S_OK;
      }
      
   // Causes conflict with HRESULT Assign (T* t) when T is IUnknown.     
   //HRESULT Assign (IUnknown *i) throw()	// Uses QueryInterface
   //   {
   //   operator=(i); 
   //   return mInterface ? S_OK : S_FALSE;
   //   }
   template<typename T1, template<class> class OP1>
   HRESULT Assign (const COMPtr<T1,OP1> &other) throw() 	// Uses QueryInterface
      {
      operator=(other); 
      return mInterface ? S_OK : S_FALSE;
      }

   unsigned long GetRefCount() const
      {
      if(!mInterface)
         return 0;
      const_cast<UnconstT*>(mInterface)->AddRef();
      return const_cast<UnconstT*>(mInterface)->Release();
      }

   static const IID& uuidof()
      {
      return COMType<T>::uuidof();
      }
      
protected:
   T *mInterface;   ///<  C-style pointer to the COM Interface of the object.
};



}//namespace

#endif
