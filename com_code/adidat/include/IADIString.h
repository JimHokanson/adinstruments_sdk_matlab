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


#ifndef IADIString_H__
#define IADIString_H__

#include "iautoadistring.h"

extern const GUID IID_IADIString;

/* Non-Automation compatible interface implemented by ADI::StringRep.
*/
COMINTERFACE IADIString : public IAutoADIString
   {
   public:
      static const IID& uuidof() {return IID_IADIString;}

      virtual HRESULT _IFUNC SetVariant(VARIANT *v) const=0; //copies the string into a BSTR set on the variant v.
      virtual uint32 _IFUNC Length() const =0;       //Does NOT include terminating NULL
      virtual void _IFUNC Delete() =0;		//This should never be called except by the String handle code.

      virtual const char* _IFUNC StrRefA() const=0; //N.B. Caller must NOT free this C string - was CStrRef()
      virtual const wchar_t* _IFUNC StrRefW() const=0;  //N.B. Caller must NOT free this BSTR - was BStrRef()
   };


#endif