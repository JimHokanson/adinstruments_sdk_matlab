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


#ifndef ADICBaseUnitsInfo_H__
#define ADICBaseUnitsInfo_H__

#include "adidat/include/IADIDataTypes.h"
#include "Utility/ADIMath.h"

namespace ADI
{

/* 
Class adding initialisation and useful methods, but no data members or virtual functions to 
the C struct it derived from. 
This class is the same size as the struct and may therefore be used in place of it.
*/
class CBaseUnitsInfo : public BaseUnitsInfo
   {
   public:
      
      //Initializes to identity scaling
      CBaseUnitsInfo()
         {
         mScaleToBase=1.0;
         mMLVOffset=0.0; // Added before ScaleToBase is applied
         ADIMath::setPosInfinity(mMaxValid);
         ADIMath::setNegInfinity(mMinValid);
         mDecPlacesBase=2;
         mPrefixBase=kNoPrefix;
         mAutoPrefixBase=kAutoFalse;
         }

      CBaseUnitsInfo(
         const ADIScaling &scaleADCToV,      //Scale factor and offset (in ADC units) to linearly transform from ADC units to Volts.
         int decPlaces = 2,                  //Default number of decimal places used to display this data in LabChart   
         float maxLimit = ADIMath::k16BitDataMaxLimit,//values >= maxLimit will display as "Out of Range" in LabChart. 
         float minLimit = ADIMath::k16BitDataMinLimit,//values <= maxLimit will display as "Out of Range" in LabChart. 
         UnitPrefix prefix = kNoPrefix,      //e.g. kMilli corresponds to 'm' in "mV" 
         bool autoPrefix = false                  //Indicates whether the prefix should be allowed to be adjusted for display purposes to keep numbers in nice ranges
         )
         {
         mScaleToBase =scaleADCToV.mScaleSourceToOutput;
         mMLVOffset   =scaleADCToV.mOffsetInSourceUnits; // Added before ScaleToBase is applied
         mMaxValid = maxLimit;
         mMinValid = minLimit;
         mDecPlacesBase=decPlaces;
         mPrefixBase=prefix;
         mAutoPrefixBase=autoPrefix;
         }


      CBaseUnitsInfo(
         double scaleToBase,
         double offsetADCUnits,
         float maxValid,//=Chart::k16BitDataMaxValid
         float minValid,//=Chart::k16BitDataMinValid
         int decPlaces = 2,
         UnitPrefix prefix = kNoPrefix,
         AutoBool autoPrefix = kAutoFalse
         )
         {
         mScaleToBase=scaleToBase;
         mMLVOffset=offsetADCUnits; // Added before ScaleToBase is applied
         mMaxValid=maxValid;
         mMinValid=minValid;
         mDecPlacesBase=decPlaces;
         mPrefixBase=prefix;
         mAutoPrefixBase=autoPrefix;
         }
         
            

   };

}//namespace

#endif