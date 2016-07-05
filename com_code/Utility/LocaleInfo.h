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


#ifndef LocaleInfo_H__
#define LocaleInfo_H__

namespace ADI
{

/*
Object holding some information about the current user's local.
*/

class LocaleInfo
   {
   private: //Enforce use as a singleton

      LocaleInfo();
      LocaleInfo(const LocaleInfo &); 
      LocaleInfo& operator=(const LocaleInfo &);
      
      static LocaleInfo sTheLocaleInfo;
       
      
      wchar_t mSepTime[8];
      wchar_t mSepDate[8];
      wchar_t mAMSym[16];
      wchar_t mPMSym[16];
      bool mIs24HourTime;

   public:
      
      static const wchar_t* GetSepTime()
         {
         return sTheLocaleInfo.mSepTime;
         }

      static const wchar_t* GetSepDate()
         {
         return sTheLocaleInfo.mSepDate;
         }

      static const wchar_t* GetAMSym()
         {
         return sTheLocaleInfo.mAMSym;
         }

      static const wchar_t* GetPMSym()
         {
         return sTheLocaleInfo.mPMSym;
         }
         
      static bool GetIs24Hour()
         {
         return sTheLocaleInfo.mIs24HourTime;
         }
      
   };


}//namespace


#endif