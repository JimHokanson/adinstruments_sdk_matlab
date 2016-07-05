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


#include "stdafx.h"

#include "LocaleInfo.h"

#include <wtypes.h>
#include <tchar.h>

using namespace ADI;

LocaleInfo LocaleInfo::sTheLocaleInfo;


LocaleInfo::LocaleInfo()
{
const LCID kUserLocaleId = LOCALE_USER_DEFAULT;

wchar_t itimeResult[8];
wchar_t itimeMarkPosition[8];

mIs24HourTime = false;

bool success =
::GetLocaleInfo( kUserLocaleId,	LOCALE_STIME, mSepTime, sizeof(mSepTime)/sizeof(wchar_t)) &&
::GetLocaleInfo( kUserLocaleId,	LOCALE_SDATE, mSepDate, sizeof(mSepDate)/sizeof(wchar_t)) &&
//GetLocaleInfo( GetUserLocaleID(),	LOCALE_SLIST, SepList.setStr(), SepList.Size()) &&
::GetLocaleInfo( kUserLocaleId,	LOCALE_S1159, mAMSym, sizeof(mAMSym)/sizeof(wchar_t)) &&
::GetLocaleInfo( kUserLocaleId,	LOCALE_S2359, mPMSym, sizeof(mPMSym)/sizeof(wchar_t)) &&
::GetLocaleInfo( kUserLocaleId,	LOCALE_ITIME, itimeResult, sizeof(itimeResult)/sizeof(wchar_t));
//::GetLocaleInfo( kUserLocaleId,	LOCALE_ITIMEMARKPOSN, itimeMarkPosition, sizeof(itimeMarkPosition)/sizeof(wchar_t));

if(success)
   {
   mIs24HourTime = _ttoi (itimeResult) == 1;
//   mIsAMPMPrefix = _ttoi (itimeMarkPosition);
   }

}