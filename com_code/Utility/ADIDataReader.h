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

#ifndef ADIDataReader_H__
#define ADIDataReader_H__

#include "adidat/include/IADIDataTypes.h"
#include "adidat/include/IADIData.h"
#include "Utility/ADIIterator.h"
#include "Utility/ADICOMPtr.h"
#include "Utility/ADIStringPtr.h"

#include <string>

namespace ADI
{

class DataReader : public COMPtr<IADIData>
{
typedef COMPtr<IADIData> Base;
public:
   //Open the .ADIDat or .ADICHT file specified by path
   explicit DataReader(const wchar_t *path);
   
   //Reference an existing ADIData object
   explicit DataReader(IADIData *data) :
      Base(data)
      {
      }
   virtual ~DataReader()
      {
      }
   
   int NumberOfRecords() const
      {
      if(mInterface)
         {
         TRecordIndex nRecs;
         mInterface->GetNumberOfRecords(kADIDataDefault,&nRecs);
         return nRecs;         
         }
      return 0;
      }
      
   int NumberOfChannels() const
      {
      if(mInterface)
         {
         TChanIndex nChans;
         mInterface->GetNumberOfChannels(kADIDataDefault,&nChans);
         return nChans;         
         }
      return 0;
      }
      
   std::wstring UnitsName(long chanIndex, long record, ADIDataFlags dataFlags = kADIDataScaleToPrefixedUnits) const
      {
      if(mInterface)
         {
         StringPtr unitName;
         mInterface->GetUnitsName(dataFlags,ADIChannelId(chanIndex),record,unitName.Set());
         return std::wstring(unitName.c_str());
         }
      return std::wstring();
      }
      
};

class FloatIter : public Iterator<IEnumFloatEx>
{
typedef Iterator<IEnumFloatEx> Base;
public:
   FloatIter()
      {
      }
   FloatIter(IADIData *data, int channel, ADIPosition start, TTickIndex end=kRecordEndOffset, ADIDataFlags dataFlags = kADIDataScaleToPrefixedUnits)
      {
      data->GetEnumFloat(dataFlags,ADIChannelId(channel),start,end,0,Base::Set());
      }
   FloatIter(const COMPtr<IADIData> &data, int channel, ADIPosition start, TTickIndex end=kRecordEndOffset, ADIDataFlags dataFlags = kADIDataScaleToPrefixedUnits)
      {
      data->GetEnumFloat(dataFlags,ADIChannelId(channel),start,end,0,Base::Set());
      }
};

}

#endif