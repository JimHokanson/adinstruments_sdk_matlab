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

#include "ADIDataSource.h"

using namespace ADI;

ChannelSourceBase::ChannelSourceBase(ADIDataType dataChannelType, ADIDataValueId dataValueType, double secsPerSample) :
   mChannelType(dataChannelType),
   mDataValueId(dataValueType),
   mSecsPerSample(secsPerSample),
   mEnabled(true)
   {
   }
   
ChannelSourceBase::~ChannelSourceBase()
   {
   }
   
   
HRESULT ChannelSourceBase::SetupChannel(int chanIndex, IADIDataSink *dataSink)
{
return dataSink->SetupChannel(ADIChannelId(chanIndex,mChannelType),mEnabled,mSecsPerSample,mDataValueId,mBaseUnitsName.c_str(),mBaseUnitsInfo.get(),mUserUnitsInfo.get(),mUserUnitsName.c_str());
}
   

void ChannelSourceBase::SetUnits(
              const wchar_t *baseUnitsName,   //name of the unprefixed base unit, usually L"V".
              const CBaseUnitsInfo *baseInfo,     //optional, may be null,specifies the scaling from ADCValues to base units (usually Volts). Null results in identity scaling.
              const CUserUnitsInfo *userInfo,             //optional, may be null, specifies the scaling from Volts to a unit (such as mmHg).
              const wchar_t *userUnitsName         //optional, may be null,name of the user unit, e.g. L"N".
              )
{
if(baseUnitsName)
   mBaseUnitsName = baseUnitsName;
else
   mBaseUnitsName.clear();
   
if(baseInfo)
   mBaseUnitsInfo.reset(new CBaseUnitsInfo(*baseInfo));
if(userInfo)
   mUserUnitsInfo.reset(new CUserUnitsInfo(*userInfo));
if(userUnitsName)
   mUserUnitsName = userUnitsName;
else
   mUserUnitsName.clear();
}              

DataSource::DataSource()
{

}

DataSource::~DataSource()
{

}

   
HRESULT DataSource::SetupChannels(IADIDataSink *dataSink)
{
for(TChannels::size_type chan(0),endChan(mChannels.size());chan<endChan;++chan)
   {
   ChannelSourceBase* channelSource = mChannels[chan];
   if(channelSource)
      {
      channelSource->SetupChannel(chan,dataSink);
      }
   else
      {//No channel source - turn off the channel in the ADIData object
      dataSink->SetupChannel(ADIChannelId(chan,kADIDataRecorded),false,0.0,kADIDataValue16Bit,0,0,0,0,0);      
      }
   }

return S_OK;
}     
   
   
TTickIndex DataSource::GetTicks() const
{
//Find the number of samples added to the fastest channel
TTickIndex ticks = 0;
for(TChannels::size_type chan(0),endChan(mChannels.size());chan<endChan;++chan)
   {
   const ChannelSourceBase* channelSource = mChannels[chan];
   if(channelSource)
      {
      TTickIndex samples = channelSource->GetSampleCount();
      if(samples > ticks)
         ticks = samples;
      }
   }
return ticks;
}

double DataSource::FindSecsPerTick() const
{
//Return the secsPerSample from the fastest channel
double secsPerTick = std::numeric_limits<double>::max();
for(TChannels::size_type chan(0),endChan(mChannels.size());chan<endChan;++chan)
   {
   const ChannelSourceBase* channelSource = mChannels[chan];
   if(channelSource)
      {
      double secsPerSample = channelSource->GetSecsPerSample();
      if(secsPerSample < secsPerTick)
         secsPerTick = secsPerSample;
      }
   }
return secsPerTick;

}

  
HRESULT _IFUNC DataSource::GetChannelEnumShort(TGenericFlags, long chanIndex, IEnumShortEx **enumOut) const
{
*enumOut = 0;
if(TChannels::size_type(chanIndex)<mChannels.size())
   {
   const ChannelSourceBase* channelSource = mChannels[chanIndex];
   if(channelSource && channelSource->GetDataValueType()==kADIDataValue16Bit)
      {
      return channelSource->CreateEnum((IEnumExBase**)enumOut);
      }
   }
return S_FALSE;
}

HRESULT _IFUNC DataSource::GetChannelEnumFloat(TGenericFlags flags, long chanIndex, IEnumFloatEx **enumOut) const
{
*enumOut = 0;
if(TChannels::size_type(chanIndex)<mChannels.size())
   {
   const ChannelSourceBase* channelSource = mChannels[chanIndex];
   if(channelSource && channelSource->GetDataValueType()==kADIDataValueFloat)
      {
      return channelSource->CreateEnum((IEnumExBase**)enumOut);
      }
   }
return S_FALSE;
}
 