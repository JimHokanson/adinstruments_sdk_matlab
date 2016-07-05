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


#ifndef CTimeDate_H__
#define CTimeDate_H__

#include "GlobalDefinesPortable.h"

#ifdef ADI_TARGET_OS_WIN32
#include <tchar.h>
#endif

#include "adidat/include/IADIDataTypes.h"

#include "ADIMath.h"

#include "LocaleInfo.h"


namespace ADI
{

//The primary use of TimeDate is for dates related to recording biological sciences data.
//By design the time and date are stored as local time, to avoid errors if the timezone incorrectly set.
//The ADITimeDate::mBias correction allows UTC to be calculated if desired.
//The local time is stored in ADITimeDate::mSeconds as seconds since midnight (00:00:00), January 1, 1970.
//The correction to add to mSeconds to get UTC is stored in mBias, in seconds. 


const int kDefaultSecsRoundingDecimalPlaces = 6;

//Extra decimal place for rates which are not exact powers of ten
const double kLogDecPlacesFromPeriodRoundUp = 0.99; //BL 24746: Time being round to 4 dp for 4 kHz files

class CTimeDate : public ADITimeDate
{

   class TimeDateConsts
      {
      public:
         TimeDateConsts();
   #ifndef ADI_TARGET_OS_MAC
         LARGE_INTEGER FT01Jan1970;
         LARGE_INTEGER FT30Dec1899;
   #endif
         double Secs1899To1970;
         ulong Secs1904To1970; // Difference between Mac DateTime and ADITimeDate starting date
         ulong JulDay01Jan1970;
         ulong JulDay30Dec1899;
      };

   static TimeDateConsts Consts;

public:

   // for readability
   enum { kSecsPerMin = 60, kMinPerHour = 60, kHoursPerDay = 24, kSecsPerHour = 60*60, kSecsPerDay = 60*60*24 };

   // NOTE: These only set the bias when explicitly given it! 
   // In general the bias remains unset (NaN), and can be set with SetBiasToLocal().
   CTimeDate(unsigned int h, unsigned int m, ADITimeType s);
   CTimeDate()
      {
      mSeconds = 0;
      SetUninitializedBias();
      }
      
   CTimeDate(const ADITimeDate &other) : 
      ADITimeDate(other)
      {
      }
      
   // N.B. month (m) is [1,12], day (d) is [1,31]
   CTimeDate(uint month, uint d, uint y, uint h, uint min, ADITimeType s);
   CTimeDate(uint month, uint d, uint y, uint h, uint min, ADITimeType s, ADITimeType UTMinusLocalSecs);
   explicit CTimeDate(ADITimeType localSecs, ADITimeType utMinusLocalSecs);
   explicit CTimeDate(ADITimeType seconds);
   
   //Set to the current local time from the system
   void SetCurrentLocalTimeDateAndBias();
   
   //Set to the current UTC time from the system
   //UTC has a bias of 0.
   void SetCurrentUTCSystemTimeDateAndBias();


   void GetHMS(int *h,int *m,double *s, bool ut, int secsDecPlacesForRounding = ADI::kDefaultSecsRoundingDecimalPlaces) const;


   // N.B. month (m) is [1,12], day (d) is [1,31]
   void GetMDY( uint &m, uint &D, uint &y , bool ut ,int secsDecPlacesForRounding = ADI::kDefaultSecsRoundingDecimalPlaces) const;

   //N.B. following helper function does not set UT bias.
   void SetMDY(uint m, uint d, uint y); //e.g. SetMDY(1,1,2001) for 1st Jan 2001
   
   void SetUninitializedBias()
      {
      ADIMath::uninitializedNan(&mBiasSecs);
      MYASSERT(!HasBias());
      }

   
   bool HasBias() const
      {
      return ADIMath::isfinite(mBiasSecs);
      }
      
   ADITimeType AsSeconds() const 
      {
      return mSeconds;
      }

   ADITimeType AsUTSeconds() const 
      {
      MYASSERT(HasBias());
      return HasBias()?mSeconds+mBiasSecs:mSeconds; //Ignore bias if uninitialised for backwards compatibility, ignore bias if it is uninitialised.
      }

   ADITimeType AsSeconds(bool ut) const
      {
      return (ut ? AsUTSeconds() : AsSeconds());
      }

   ADITimeType AsDaySeconds(bool ut) const
      {
      return fmod(AsSeconds(ut),kSecsPerDay);
      }
      
   void AsSystemTime(SYSTEMTIME *st, double *fractionalSecs, bool ut, int secsDecPlacesForRounding = ADI::kDefaultSecsRoundingDecimalPlaces);
      
      
   CTimeDate& operator =  (ADITimeType seconds) {mSeconds = seconds; return *this;}
   CTimeDate& operator += (ADITimeType seconds) {mSeconds += seconds; return *this;}
   CTimeDate& operator -= (ADITimeType seconds) {mSeconds -= seconds; return *this;}
      
   ADITimeType  operator -	(const CTimeDate& t) const;
   
   enum TimeMode
      {
      k12Hour = 0x0001,
      k24Hour = 0x0002,
      kCurrentLocale = 0x0008
      };


   void StreamTime(std::wostream &stream, int dec_places = 2, bool ut = false, TimeMode mode = kCurrentLocale) const;
   void StreamDate(std::wostream &stream, bool ut = false, bool longDate = false,int secsDecPlacesForRounding = ADI::kDefaultSecsRoundingDecimalPlaces) const;  //This always uses the user locale, and can generate long dates.

   static void sGetHMS(double secs, int *h,int *m,double *s, int secsDecPlacesForRounding);
   static void sGetMDYHMS(double secs, uint *month, uint *D, uint *Y, int *h,int *m,double *s, int secsDecPlacesForRounding);

   //If a round occurs, this adjusts secs upwards by an adequate amount to ensure minutes etc subsequently
   //calculated from secs will be rounded up. 
   //One should NOT use the fractional part of this adjusted secs value.
   static double sCalcRoundedSecsMod60(double *secs, int secsDecPlacesForRounding);

   static ADITimeType sGetSec(ADITimeType secs);
   static int sGetMin(ADITimeType secs);
   static int sGetHour(ADITimeType secs);

   // N.B. month (m) is [1,12], day (d) is [1,31]
   static ulong JulianDay( uint m, uint d, uint y );
   static int DayWithinMonth( uint month, uint day, uint year );
   static bool IsLeapYear(uint year );
   static void JulianDayToGregorianDate(ulong julDay, uint &m, uint &D, uint &y );
   static const uint DaysInMonth[12];

   static int RoundingDecPlacesFromSecPerTick(double secPerTick)
      {
      if(secPerTick > 0)
         {
         double logSecPerTick = -log10(secPerTick);
         if(logSecPerTick < 0)
            logSecPerTick = 0;
         return static_cast<int>(ceil(logSecPerTick+ADI::kLogDecPlacesFromPeriodRoundUp)); //Always return at least 1 decimal place
         }
      return ADI::kDefaultSecsRoundingDecimalPlaces;
      }


   static double GetSecsRoundingDelta(int decPlaces)
      {//we use a value slightly >0.5 to ensure we preemptively round when floating point errors might cause the double to string conversion not to round.
      if(decPlaces < 0)
         return 0.0;
      return 0.51*std::pow(10.0,-decPlaces); //preemptively round the time so that streaming to text won't round up just the seconds (to 60).
      }
      
   protected:
      void Set(const SYSTEMTIME &sysTime); //does not set mBias!
   
      void SetCurrentLocalTimeDateWithoutBias(); // doesn't set bias. Returns the system HP timer value at the time of the API call.

   
      // Index usually refers to things starting at 0 (i.e. 0<=m<=11), but for JulianDay(), months are 1 based.
      static int AssertIndexOfMonth( uint m )
         { return m>=1 && m<=12; }
   
};


}//namespace


#endif