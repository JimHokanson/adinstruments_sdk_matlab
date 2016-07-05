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


#ifndef ADIMath_H__
#define ADIMath_H__

#include "adidat/include/ADIBaseTypes.h"

namespace ADIMath
{

const int64 kDoubleNonFiniteBytePattern =    0x7ff0000000000000LL;

const int64 kDoubleQuietNaNBytePattern =     0x7ff8000000000000LL;
const int64 kDoubleMakeUninitialized =       0x0000700000000000LL;

const int64 kDoubleUninitializedNanBytePattern = kDoubleQuietNaNBytePattern | kDoubleMakeUninitialized;


const uint32 kFloatNonFiniteBytePattern           = 0x7f800000;
const uint32 kFloatMakeNeg                            = 0x80000000;
const uint32 kFloatPosInfinityBytePattern             = kFloatNonFiniteBytePattern;
const uint32 kFloatNegInfinityBytePattern             = kFloatNonFiniteBytePattern | kFloatMakeNeg;


const int16 k16BitDataScaleTop = 32000;
const int16 k16BitDataScaleBottom = -32000;

const int16 k16BitDataMaxLimit = 32767;
const int16 k16BitDataMinLimit = -32767;


inline void setPosInfinity(float &f)
   { reinterpret_cast<uint32&>(f) = kFloatPosInfinityBytePattern; }

inline void setNegInfinity(float &f)
   { reinterpret_cast<uint32&>(f) = kFloatNegInfinityBytePattern; }



inline bool isfinite(const double &f)
   {
   return (reinterpret_cast<const int64&>(f) & kDoubleNonFiniteBytePattern) != kDoubleNonFiniteBytePattern;
   }

inline void uninitializedNan(double *out)    //Use this Nan to indicate uninitialized data, e.g. when MinMax range for data blocks has not yet been calculated
   { 
   *reinterpret_cast<int64*>(out) = kDoubleUninitializedNanBytePattern;
   }


inline double Round(double x)
   {
   return floor(x+0.5);
   }
inline int RoundToInt(double x)
   {
   return static_cast<int> (x<0?-(0.5-x):x+0.5);
   }
inline long RoundToLong(double x)
   {
   return static_cast<long> (x<0?-(0.5-x):x+0.5);
   }

}

#endif