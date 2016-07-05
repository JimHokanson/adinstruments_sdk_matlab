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

#include "CTimeDate.h"


using namespace ADIMath;
using namespace std;

namespace ADI
{


const uint CTimeDate::DaysInMonth[12] =
   { 31,28,31,30,31,30,31,31,30,31,30,31 };



CTimeDate::TimeDateConsts CTimeDate::Consts;

CTimeDate::TimeDateConsts::TimeDateConsts()
   {
#ifdef ADI_TARGET_OS_WIN32
   SYSTEMTIME sT01Jan1970 = {1970,1,0,1,0,0,0,0};
   ::SystemTimeToFileTime(&sT01Jan1970, (FILETIME*)&FT01Jan1970);

   SYSTEMTIME sT30Dec1899 = {1899,12,0,30,0,0,0,0};
   ::SystemTimeToFileTime(&sT30Dec1899, (FILETIME*)&FT30Dec1899);

   Secs1899To1970 = (FT01Jan1970.QuadPart - FT30Dec1899.QuadPart) / 10.0e6;

#else
   // KISS. If turns out not to match above, can just hard-code!
   Secs1899To1970 = (JulianDay(1,1,1970) - JulianDay(12,30,1899)) * kSecsPerDay;
#endif // ADI_TARGET_OS_WIN32

#if _DEBUG
   double checkSecs1899To1970 = (JulianDay(1,1,1970) - JulianDay(12,30,1899)) * kSecsPerDay;
   MYASSERT(checkSecs1899To1970 == Secs1899To1970);
#endif

   JulDay01Jan1970 = JulianDay(1,1,1970);
   JulDay30Dec1899 = JulianDay(12,30,1899);
   Secs1904To1970 = (JulDay01Jan1970 - JulianDay(1,1,1904)) * kSecsPerDay;
   }



CTimeDate::CTimeDate (ADITimeType seconds, ADITimeType bias)
   {
   mSeconds    = seconds;
   mBiasSecs   = bias;
   MYASSERT(HasBias());
   }

CTimeDate::CTimeDate (ADITimeType seconds)
   {
   mSeconds    = seconds;
   SetUninitializedBias();
   MYASSERT(!HasBias());
   }


CTimeDate::CTimeDate (unsigned int h, unsigned int m, ADITimeType s)
   {
   mSeconds    = s + (m * kSecsPerMin) + (h * kSecsPerHour);
   SetUninitializedBias();
   MYASSERT(!HasBias());
   }
   
   
CTimeDate::CTimeDate(uint month, uint d, uint y, uint h, uint min, ADITimeType s)
   {
   SetMDY(month,d,y);
   mSeconds += s + (min * kSecsPerMin) + (h * kSecsPerHour);
   SetUninitializedBias();
   MYASSERT(!HasBias());
   }
   
CTimeDate::CTimeDate(uint month, uint d, uint y, uint h, uint min, ADITimeType s, ADITimeType UTMinusLocalSecs)
   {
   SetMDY(month,d,y);
   mSeconds += s + (min * kSecsPerMin) + (h * kSecsPerHour);
   mBiasSecs = UTMinusLocalSecs;
   MYASSERT(HasBias());
   }
   
   
void CTimeDate::SetCurrentLocalTimeDateAndBias()
   {
   CTimeDate utc;
   long prevBiasMinutes = std::numeric_limits<long>::max();
   long biasMinutes;
   //We loop in case we hit the time when the bias is changing due to e.g. a daylight savings change over.
   //We need up to 4 separate measurements of the bias before we can be sure the result has not been affected
   //by a daylight-saving transition!
   int tries = 0;
   for(;tries<4;++tries) 
      {
      SetCurrentLocalTimeDateWithoutBias();
      utc.SetCurrentUTCSystemTimeDateAndBias();
      biasMinutes = Round((utc.AsSeconds() - AsSeconds())/kSecsPerMin); //UTC-LocalTime (round to nearest minute).
      if(prevBiasMinutes == biasMinutes)
         break;
      MYASSERT(tries<3); //should have had break by the 4th time 
      prevBiasMinutes = biasMinutes; 
      }

   mBiasSecs = biasMinutes*kSecsPerMin;
   }
   
void CTimeDate::SetCurrentLocalTimeDateWithoutBias() // doesn't set bias. Returns the system HP timer value at the time of the API call.
   {
   SYSTEMTIME  nowLocal;
   ::GetLocalTime (&nowLocal);
   Set(nowLocal);
   }

void CTimeDate::SetCurrentUTCSystemTimeDateAndBias()
   {
   SYSTEMTIME nowSystem;
   ::GetSystemTime (&nowSystem);
   Set(nowSystem);
   mBiasSecs = 0; // System time is UTC, so set bias to 0.
   }
      
void CTimeDate::Set(const SYSTEMTIME &sysTime)
   {
   SetMDY(sysTime.wMonth, sysTime.wDay, sysTime.wYear);
   mSeconds += (sysTime.wHour*kSecsPerHour + sysTime.wMinute*kSecsPerMin + sysTime.wSecond)+sysTime.wMilliseconds/1000.0;
   }
   
void CTimeDate::AsSystemTime(SYSTEMTIME *st, double *fractionalSecs, bool ut, int secsDecPlacesForRounding)
   {
   double secs = AsSeconds(ut);

//sCalcRoundedSecsMod60 modifies the secs parameter, pre-emptively rounding it up.
   double secsMod60 = sCalcRoundedSecsMod60(&secs,secsDecPlacesForRounding);  

   ulong julianDay = ulong(secs/kSecsPerDay) + Consts.JulDay30Dec1899;
   uint month, day, year;
   JulianDayToGregorianDate(julianDay,month,day,year);
   if(st)
      {
      st->wHour = sGetHour(secs);;
      st->wMinute = sGetMin(secs);
      st->wSecond = secsMod60;
      st->wMonth = month;
      st->wDay = day;
      st->wYear = year;
      }
   if(fractionalSecs)
      {
      double intPart;
      *fractionalSecs = modf(secsMod60,&intPart);
      }
   }      
   

void CTimeDate::GetHMS(int *h,int *m,double *s, bool ut, int secsDecPlacesForRounding) const
   {
   double secs = AsSeconds(ut);
   sGetHMS(secs,h,m,s,secsDecPlacesForRounding);
   }

void CTimeDate::sGetMDYHMS(double secs, uint *month, uint *D, uint *Y, int *h,int *m,double *s, int secsDecPlacesForRounding)
   {
   MYASSERT(secs >= 0); //If dealing with -ve time intervals, the caller should pass a +ve secs and apply a -ve sign afterwards.

   *s = sCalcRoundedSecsMod60(&secs,secsDecPlacesForRounding);  
   *m = sGetMin(secs);
   *h = sGetHour(secs);

   ulong j = (secs)/kSecsPerDay+Consts.JulDay01Jan1970;
   JulianDayToGregorianDate(j,*month,*D,*Y);
   }
   
void CTimeDate::sGetHMS(double secs, int *h,int *m,double *s, int secsDecPlacesForRounding)
   {
   MYASSERT(secs >= 0); //If dealing with -ve time intervals, the caller should pass a +ve secs and apply a -ve sign afterwards.

   *s = sCalcRoundedSecsMod60(&secs,secsDecPlacesForRounding);  
   *m = sGetMin(secs);
   *h = sGetHour(secs);
   }
   
   
//If a round occurs, this adjusts secs upwards
double CTimeDate::sCalcRoundedSecsMod60(double *secs, int secsDecPlacesForRounding /*double roundingDelta, double *roundedMinusActualTime*/)
   {
   MYASSERT(*secs >= 0); //If dealing with -ve time intervals, the caller should pass a +ve secs and apply a -ve sign afterwards.
   double roundingDelta = GetSecsRoundingDelta(secsDecPlacesForRounding);

   //Make preemptively round seconds, not just minutes, in case the resulting seconds will be 
   //split into integer and fractional parts e.g. SYSTEMTIME along with fractional seconds.
   double secsMod60 = fmod(*secs, kSecsPerMin);
   double intPart;
   double fracSecs = modf(secsMod60,&intPart);
   if(fracSecs + roundingDelta >= 1.0)
      {
      *secs += 0.75; //force secs, minutes and hours to round up as needed
      secsMod60 = floor(secsMod60+0.75);
      if(secsMod60 >= 60)
         secsMod60 = 0;
      }
   return secsMod60;
   }

ADITimeType CTimeDate::sGetSec(ADITimeType secs)
   {
   return fmod(secs, kSecsPerMin);
   }
int CTimeDate::sGetMin(ADITimeType secs)
   {
   return fmod( secs / kSecsPerMin , kMinPerHour );
   }
int CTimeDate::sGetHour(ADITimeType secs)
   {
   return fmod( secs / kSecsPerHour , kHoursPerDay );
   }
   

void CTimeDate::GetMDY( uint &m, uint &D, uint &y , bool ut, int decPlacesForSecs) const
   {
   MYASSERT(!ut || HasBias());
   double preemptiveRound = GetSecsRoundingDelta(decPlacesForSecs);
   ulong j = (AsSeconds(ut)+preemptiveRound)/kSecsPerDay+Consts.JulDay01Jan1970;
   JulianDayToGregorianDate(j,m,D,y);
   }

void CTimeDate::SetMDY(uint m, uint d, uint y) //e.g. SetMDY(1,1,2001) for 1st Jan 2001
   {
   mSeconds = (JulianDay(m,d,y) - Consts.JulDay01Jan1970) * kSecsPerDay;
   }
   
ADITimeType CTimeDate::operator-(const CTimeDate& t) const 
   {
   MYASSERT(!t.HasBias() || (t.mBiasSecs == mBiasSecs)); // since we're not incorporating the bias
   if(HasBias() && t.HasBias())
      return AsUTSeconds()-t.AsUTSeconds();
   //Assume we really want the difference of local times
   MYASSERT(!HasBias() && !t.HasBias()); //if this fires we could be subtracting local times from different timezones and ignoring the timezone difference.   
   return mSeconds - t.mSeconds;
   }


void CTimeDate::StreamTime(std::wostream &stream, int dec_places, bool ut, TimeMode mode) const
   {
   CTimeDate myTime(*this); 

   //We don't want e.g. 23:44:-12.43
   bool negativeTime = mSeconds < 0;
   if(negativeTime)
      {
      MYASSERT(!ut);
      myTime.mSeconds = -myTime.mSeconds;
      } 

   int hour;
   int min;
   double secs;

   myTime.GetHMS (&hour,&min,&secs,ut,dec_places);

   bool pm = hour >= 12;
   bool is12;

   if (mode == kCurrentLocale)
      is12 = ! LocaleInfo::GetIs24Hour();
   else
      is12 = (k12Hour == mode);

   if (is12)
      {
      if (pm)
         {
         if (hour > 12)
            hour -= 12;
         }
      else
         {
         if (hour == 0)
            hour = 12;
         }
      }

   if(negativeTime)
      stream << L'-';

   // Generate hours
   stream << hour << LocaleInfo::GetSepTime();
   stream.fill(L'0');

   // Generate minutes
   stream.width (2);
   stream << min << LocaleInfo::GetSepTime();

   // Generate seconds
   TCHAR secs_txt [32];
   int fieldWidth = 2; // Minimum of 2 digits

   if (dec_places > 0)
      // plus decimal point and decimal digits
      fieldWidth += 1 + dec_places;

#ifdef ADI_TARGET_OS_WIN32
   _stprintf_s (secs_txt, _T("%0*.*lf"), fieldWidth, dec_places, secs);
#else
   swprintf (secs_txt, CountOf(secs_txt), _T("%0*.*lf"), fieldWidth, dec_places, secs);
#endif
   stream << secs_txt;

   if (is12)
      {// Append pm/am
      stream << _T(" ");
      stream << (pm ? LocaleInfo::GetPMSym() : LocaleInfo::GetAMSym());
      }

   stream << ends; 
   }
   
void CTimeDate::StreamDate(std::wostream &stream, bool ut, bool longDate, int secsDecPlacesForRounding) const
   {
   uint m,d,y;
   GetMDY(m,d,y,ut,secsDecPlacesForRounding);
   if(y<=1970)
      {
      MYASSERT(0);
      return;
      }

   SYSTEMTIME sysTime;
   sysTime.wYear=y;
   sysTime.wMonth=m;
   sysTime.wDay=d;
   sysTime.wDayOfWeek=0;

   const int kBufSize = 256;
   wchar_t buf[kBufSize];

   bool ok = ::GetDateFormat(
      LOCALE_USER_DEFAULT,	// locale for which date is to be formatted
      longDate ? DATE_LONGDATE : DATE_SHORTDATE,	// flags specifying function options
      &sysTime,	// date to be formatted
      0,	// date format string
      buf,	// buffer for storing formatted string
      kBufSize 	// size of buffer
      );
   MYASSERT(ok);
   stream << buf;
   }      

//
// Convert a Julian day number to its corresponding Gregorian calendar
// date.  Algorithm 199 from Communications of the ACM, Volume 6, No. 8,
// (Aug. 1963), p. 444.  Gregorian calendar started on Sep. 14, 1752.
// This function not valid before that.
// N.B. month (m) is [1,12]
void CTimeDate::JulianDayToGregorianDate(ulong julDay, uint &m, uint &D, uint &y )
   {
   ulong d;
   ulong j = julDay - 1721119L;
   y = (((j<<2) - 1) / 146097L);
   j = (j<<2) - 1 - 146097L*y;
   d = (j>>2);
   j = ((d<<2) + 3) / 1461;
   d = (d<<2) + 3 - 1461*j;
   d = (d + 4)>>2;
   m = (5*d - 3)/153;
   d = 5*d - 3 - 153*m;
   D = ((d + 5)/5);
   y = (100*y + j);

   if( m < 10 )
      m += 3;
   else
      {
      m -= 9;
      y++;
      }
   }


// Convert Gregorian calendar date to the corresponding Julian day
// number j.  Algorithm 199 from Communications of the ACM, Volume 6, No.
// 8, (Aug. 1963), p. 444.  Gregorian calendar started on Sep. 14, 1752.
// This function not valid before that.
// Returns 0 if the date is invalid.
// m == 1 => January
ulong CTimeDate::JulianDay( uint m, uint d, uint y )
   {
   unsigned long c, ya;
   if( y <= 99 )
      return 0;
   if( !DayWithinMonth(m, d, y) )
      return 0;

   if( m > 2 )
      m -= 3;
   else
      {
      m += 9;
      y--;
      }

   c = y / 100;
   ya = y - 100*c;
   return ((146097L*c)>>2) + ((1461*ya)>>2) + (153*m + 2)/5 + d + 1721119L;
   }

//
// Is a day (1-31) within a given month?
//
int CTimeDate::DayWithinMonth( uint month, uint day, uint year )
   {
   if( day <= 0 || !AssertIndexOfMonth(month) )
      return 0;
   unsigned d = DaysInMonth[month-1];
   if( IsLeapYear(year) && month == 2 )
      d++;
   return day <= d;
   }

//
// Algorithm from K & R, "The C Programming Language", 1st ed.
//
bool CTimeDate::IsLeapYear(uint year )
   {
   return ((year & 3) == 0 && year % 100 != 0) || year % 400 == 0;
   }

}