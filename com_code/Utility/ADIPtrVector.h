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


#ifndef ADIPtrVector_H__
#define ADIPtrVector_H__


#define ADIASSERT MYASSERT

#include <limits>

namespace ADI
{

/**
*   vector of pointers to objects owned by this container. 
*   The vector may contain null pointers.
*   This container, differs from boost::ptr_vector in that it returns pointers rather than
*   references to items.
*   Ownership is optional. If the container is not set to be an owner, it will not delete items
*   when it is destroyed.
*/
template <class T>  
class PtrVector 
   {
   typedef PtrVector Self;
   public:
   
      //STL style
      typedef unsigned int size_type;
      typedef T* value_type;
      typedef T** iterator;
      typedef const T** const_iterator;
      
      enum
         {
         kNotFoundIndex = UINT_MAX,
         kMinCapacity = 8,
         //kNotFoundIndex = std::numeric_limits<size_type>::max()
         };
         

      explicit PtrVector(	
         size_type size=0,    //Initial size, (no. of pointers initialised to 0)
         bool owner=true      //deletes pointers in destructor if true
         ) :
         A(0),
         mCapacity(std::max<size_type>(size, kMinCapacity)),
         mSize(0), //mSize is set to size in Init(size);
         mOwner(owner)
         {
         A = new T*[mCapacity];
         Init(size);
         }


      /**
      If you copy or assign PtrVectors, you need to provide a function like:
      inline animal* new_clone( const animal& a )
      {
      return a.Clone();
      }
      for the object (base) type the PtrVector owns.
      */
      PtrVector(const PtrVector &other)
         : 
         A(new T*[other.mSize]),
         mCapacity(other.mSize),
         mSize(0), //mSize is incremented below as each clone is created
         mOwner(true)//we are cloning the items, so we need to own the copies
         {
         const_iterator start(other.begin()), finish(other.end());
         ADIASSERT(start <= finish);
         size_type newSize = finish-start;
         T const **end=const_cast<T const **>(this->A+newSize);
         T const **ptr;
         T const **otherptr = start;
         for(ptr=const_cast<T const **>(this->A); ptr<end ; ++otherptr,++mSize)
            *ptr++ = (*otherptr ? new_clone(**otherptr) : *otherptr); //compatible with e.g. boost::ptr_vector     
         }

      PtrVector(const_iterator start, const_iterator finish)
         : 
         A(new T*[finish-start]),
         mCapacity(finish-start),
         mSize(0),
         mOwner(true)
         {
         ADIASSERT(start <= finish);
         size_type newSize = finish-start;
         T const **end=const_cast<T const **>(this->A+newSize);
         T const **ptr;
         T const **otherptr = start;
         for(ptr=const_cast<T const **>(this->A); ptr<end ; ++otherptr,++mSize)
            *ptr++ = (*otherptr ? new_clone(**otherptr) : *otherptr); //compatible with e.g. boost::ptr_vector     
         }                                                              //If you get a "'new_clone' not found" compiler error, you need to implement this function for T.


      void operator=(const PtrVector &other)
         {
         Self copy(other);
         swap(copy);
         }

      void assign(const_iterator start, const_iterator finish)
         {
         Self copy(start,finish);
         swap(copy);
         }      

      ~PtrVector()
         {
         clear();
         }


      //T*& operator[] was dangerous because it allowed assignment of the point without deleting the old item
      //T*& operator[](size_type i) {PRECONDITION(i<mSize); return (T*&)A[i];}
      //const T*& operator[](size_type i) const
      //	{PRECONDITION(i<mSize); return (const T*&)A[i];}
      T*& operator[](size_type i) 
         {
         ADIASSERT(i<mSize); return (T*&)A[i];
         }
      const T* operator[](size_type i) const
         {
         ADIASSERT(i<mSize); return (const T*)A[i];
         }



      //STL style

      iterator begin () {return (iterator) A;}
      iterator end () {return (iterator) (A + size ());}
      const_iterator begin () const {return (const_iterator) A;}
      const_iterator end () const {return (const_iterator) (A + size ());}
      
      size_type size() const
         {
         return mSize;
         }
         
      bool empty() const
         {
         return mSize == 0;
         }         

      T*& front() { return (T*&)*A;}
      const T*& front() const { return (T*&)*A;}
      T*& back() { return (T*&)*(A+mSize-1);}
      const T*& back() const 
         { 
         return (const T*&)*(A+mSize-1);
         }

      void push_back(T* pT)
         {
         if(mSize>=mCapacity)
            Grow();
         A[mSize++] = pT;
         }
         
      template <typename PT>      
      void push_back(PT &pT)//e.g. std::auto_ptr<T>
         {
         if(mSize>=mCapacity)
            Grow();
         A[mSize++] = static_cast<T*>(pT.release());
         }

      iterator insert(iterator pos, T* t)
         {
         int index = pos-begin(); 
         Insert(index,t);
         return iterator(A+index);
         }

      //What should this one do? Copy the items or assume nothing else owns them?
      //iterator insert(iterator before, iterator first, iterator last)
      //   {
      //   ADIASSERT(this->begin() <= before && before < this->end());
      //   if(first >= last)
      //      return;
      //   size_type newItems = last-first;
      //   //Alloc the memory we need
      //   reserve(size()+newItems);
      //   //Insert space for the new items
      //   ::memmove(before+newItems,before,newItems*sizeof(void*));         
      //   //Copy the new items from the other container
      //   ::memmove(before,first,newItems*sizeof(void*));         
      //   }

      void erase(iterator where,bool deleteIfOwner = true)
         {
         erase(where,where+1,deleteIfOwner); 
         }

      void erase(iterator start,iterator end,bool deleteIfOwner = true)
         {
         Detach(start-A,end-A,deleteIfOwner); //delete if owner
         }

      //Transfer items from another PtrVector without cloning the items. C.f. boost::ptr_vector.   
      void transfer(iterator before, iterator first, iterator last, PtrVector &from)
         {
         ADIASSERT(&from != this); //Need to check this case!
         ADIASSERT(this->begin() <= before && before <= this->end());
         ADIASSERT(from.begin() <= first && first <= from.end());
         ADIASSERT(from.begin() <= last && last <= from.end());
         if(first >= last)
            return;
         size_type iBefore = before-this->begin();
         size_type newItems = last-first;
         //Alloc the memory we need
         reserve(size()+newItems);
         //Insert space for the new items
         ::memmove(this->begin()+iBefore+newItems,this->begin()+iBefore,(size()-iBefore)*sizeof(void*));         
         //Copy the new items from the other container
         ::memmove(this->begin()+iBefore,first,newItems*sizeof(void*));         
         //Release the transferred items from the other container without deleting them
         from.Detach(first-from.begin(),last-from.begin(),false);
         this->mSize += newItems;
         } 
         
      void swap(Self &other) throw()
         {
         std::swap(mCapacity,other.mCapacity);
         std::swap(A,other.A);

         std::swap(mSize,other.mSize);
         //std::swap(Delta_,other.Delta_);
         std::swap(mOwner,other.mOwner);
         }		

      void resize(size_type newSize) 
         {
         if(newSize==mSize)
            return;
         if(newSize>mSize)
            Init(newSize);
         else
            {  //decrease Count
            if(newSize < mCapacity/4 && mCapacity/2 >= kDeltaConst)
               {//reallocate
               T** newA = new T*[mCapacity/2];
               memcpy(newA,A,newSize*sizeof(void*));
               DoFlush(newSize);
               delete[] A;
               A = newA;
               mSize = newSize;
               mCapacity /= 2;
               }
            else
               DoFlush(newSize);
            }
         }
         
      void reserve(size_type cap)
         {
         if(mCapacity < cap)
            Reserve(cap);
         }
         
      void clear()
         {
         DeleteRange(0,mSize); 
         mSize = 0;
         }         


      void Add(const PtrVector& other)
         {
         if(mSize + other.mSize > mCapacity)
            Reserve(mSize + other.mSize);
         memcpy(A+mSize,other.A,other.mSize*sizeof(void*));
         mSize+=other.mSize;
         }

      void SetOrAdd(size_type pos, T* pT)
         {
         if(pos >= mSize)
            {
            if(pos >= mCapacity)
               Reserve(max<size_type>((mCapacity * 3 + 1)/2, pos));
            Init(pos+1);
            }
         T*& p = A[pos];
         if(mOwner && p)
            DoDelete(p);
         p = pT;
         }


      void SetItem(size_type pos, T* pT)
         {
         ADIASSERT(pos<mSize);
         T*& p = A[pos];
         if(Owner && p)
            DoDelete(p);
         p = pT;
         }

      //Relinquish ownership      
      T* ReleaseItem(size_type pos)
         {
         ADIASSERT(pos<mSize);
         T* p = A[pos];
         A[pos] = 0;
         return p;
         }

      size_type Find (const T *entry) const // Returns kNotFoundIndex if not found.
         {
         void *end = A+mSize;
         for (void **scan = A; scan < end; scan++)
            {
            if (*scan == entry)
               return scan - A;
            }
         return kNotFoundIndex;
         }


      void Erase(size_type where, bool deleteIfOwner = true)
         {
         Detach(where,where+1,deleteIfOwner);
         }

      void Erase(size_type start,size_type end,bool deleteIfOwner = true)
         {
         Detach(start,end,deleteIfOwner);
         }   

      bool DetachItem (T *entry)
         {
         size_type pos(Find(entry));
         if (pos == kNotFoundIndex)
            return false;
         Detach(pos, pos + 1, Owner);
         return true;
         }


      bool Detach(size_type start, size_type end, bool doDelete=true)
         {
         ADIASSERT(start <= end);
         if(end > mSize)  
            end = mSize;
         if(start>=end)
            return false;           // in the counted portion

         if(mOwner && doDelete)
            DeleteRange(start, end);

         mSize -= end-start;
         if(mSize>start) //We can use memmove because we just have array of pointers
            memmove(A+start,A+end,(mSize-start)*sizeof(void*));
         return true;
         }


      bool Insert(size_type pos, T *pT)
         {
         if(pos>mSize) //This type of array is not designed to be sparse
            {
            ADIASSERT(0);
            return false;
            }

         if(mSize>=mCapacity)
            Grow();
         memmove(A+pos+1,A+pos,(mSize-pos)*sizeof(void*));
         A[pos]=pT;
         mSize++;
         return true;
         }

      //Transfers ownership from other to this if transfer==true
      bool Insert(size_type pos, PtrVector& other, size_type start, size_type end, bool transfer=true)
         {
         //return CArrayVoidP::Insert(pos, other, start, end, transfer);
         if(pos>mSize || start>=end) //This type of array is not designed to be sparse
            return false;

         ADIASSERT(other.mSize>=end && &other != this);

         size_type newSize=mSize+end-start;
         if(newSize>Size_)
            {
            ADIASSERT(Delta_!=0);
            Reserve(max(newSize, Size_+Delta_));
            }
         memmove(A+pos+end-start,A+pos,(mSize-pos)*sizeof(void*));
         memcpy(A+pos,other.A+start,(end-start)*sizeof(void*));
         mSize=newSize;
         if(transfer && mOwner)
            memset(other.A+start,0,(end-start)*sizeof(void*)); //set the source container items transferred to null.
         return true;
         }

      void DeleteRange(size_type start, size_type end);  //deletes range starting from A[end-1].Sets range to 0. Does NOT affect Count.

   protected:
      enum {kDeltaConst = 8}; 
      
      
      void Init(size_type size)
         {
         if(size<=mSize)
            return;
         if(size>mCapacity)
            Reserve(max<size_type>((mCapacity * 3 + 1)/2, size));
         if(size>mSize)
            {
            memset(A+mSize,0,(size-mSize)*sizeof(void*));
            mSize = size;
            }
         }

      
      T** CloneData(size_type sz)
         {
         ADIASSERT(sz>=mCapacity); 
         T** newA = new T*[sz];
         memcpy(newA,A,std::min(mSize,sz)*sizeof(T*));
         return newA;
         }
  
      void Reserve(size_type newSize) 
         {
         T** na=CloneData(newSize);
         std::swap(na,A);
         delete[] na;
         mCapacity = newSize;
         }

      void Grow()	
         {
         Reserve(max<size_type>((mCapacity * 3 + 1)/2, kDeltaConst));
         }
         
      void DoFlush(size_type nToLeave)
         { 
         DeleteRange(nToLeave, mSize); 
         mSize = nToLeave;
         }

      T **A;
      size_type mCapacity;
      size_type mSize;
      bool mOwner;  //true if the vector should delete the items it contains.

      static void DoDelete(T* p);  //work around to prevent inlines causing warnings related to forward declarations for T.
   };

template <class T>
void PtrVector<T>::DoDelete(T* p)
   { delete p;}

//Can't put this in CArrayVoidP because of delete.
template <class T>
void PtrVector<T>::DeleteRange(size_type start, size_type end)  //deletes A[end-1] first
   {
   ADIASSERT(start<=end);
   if(mOwner)
      {
      if(end>=mSize)
         end = mSize;
      T** ptr = ((T**)A)+end;
      T** stop = ((T**)A)+start;
      while(ptr>stop)
         {
         delete *(--ptr);
         *ptr = 0;
         }
      }
   }



}




#endif