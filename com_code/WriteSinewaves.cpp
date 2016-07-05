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

#define _USE_MATH_DEFINES
#include <math.h>

#include "WriteSinewaves.h"


#include "Utility/ADIMath.h"
#include "Utility/ADIDataWriter.h"
#include "Utility/ADICBaseUnitsInfo.h"
#include "Utility/CTimeDate.h"
#include "Utility/ADIIterator.h"

#include <sstream>
#include <vector>

using namespace ADIMath;
using namespace ADI;
using namespace std;


//This example illustrates efficiently adding individual samples to each channel.
//This is particularly useful for situations where the source data has the samples interleaved
//across channels , as would commonly be the case when reading samples from a text file,
//or a sound card.
void gWriteSinewavesFromInterleavedChannelData(IADIDataClass *dataClassObj, const wchar_t *fileName)
{
int nChans = 5;
int nRecords = 2;

DataWriter dataWriter(dataClassObj, fileName);

DataSource &dataSource = dataWriter.GetDataSource();

for(int chan(0);chan<nChans;++chan)
   {
   wstringstream nameStr;
   nameStr<<L"Sine "<<chan+1;
   dataWriter.SetChannelName(chan, nameStr.str().c_str());
   }

//For this example all channels are at the same rate (the tick rate).
double secsPerSample = 0.0025; //2.5 ms => 400Hz

for(int record(0);record<nRecords;++record)
   {
   TTickIndex nTicksInRecord = 24000;
   
   //This example demonstrates the simple case where all channels are at the same (tick) rate.
   //Setup the channels for this record
   for(int chan(0);chan<nChans;++chan)
      {      
      if(chan < 2)
         {//For this example, the first two channels are 16 bit data
         auto_ptr<ChannelSourceBufferedInt16> sourceChan(new ChannelSourceBufferedInt16());
         sourceChan->SetSecsPerSample(secsPerSample);
         
         //For this example choose a 5V bipolar range symmetrical about 0V
         const double kVoltsRangeMax = 5;
         const double kVoltsRangeMin = -5;
         double voltsPerADCUnit = (kVoltsRangeMax-kVoltsRangeMin)/double(k16BitDataScaleTop-k16BitDataScaleBottom);
         double offsetInADCUnits = (kVoltsRangeMax+kVoltsRangeMin)/voltsPerADCUnit; 
         CBaseUnitsInfo baseInfo(ADIScaling(voltsPerADCUnit, offsetInADCUnits));
         
         sourceChan->SetUnits(L"V", &baseInfo);
         
         dataSource.SetChannelSource(chan, sourceChan.release());
         }
      else if(chan == 2 && record == 1)
         {//channel 3 is empty in the 2nd record
         dataWriter.SetChannelSource(chan, 0);
         }
      else
         {//Remaining channels contain 32bit floats in Volts.
         auto_ptr<ChannelSourceBufferedFloat> sourceChan(new ChannelSourceBufferedFloat());
         sourceChan->SetSecsPerSample(secsPerSample);
         bool setLimits = chan == 3;   //for this example we arbitrarily set limits to +/- 2 V for channel 4
         if(setLimits)
            {
            CBaseUnitsInfo baseInfo; //Initializes to identity transform
            baseInfo.mMaxValid = 2.0;
            baseInfo.mMinValid = -2.0;
            sourceChan->SetUnits(L"V", &baseInfo);         //default identity scaling is adequate
            }
         else
            sourceChan->SetUnits(L"V");         //default identity scaling is adequate

         dataWriter.SetChannelSource(chan, sourceChan.release());
         }
      }

   //For pre-recorded data where the time of the trigger (or time of first sample if no pre or post trigger samples) is known.
   // N.B. month (m) is [1,12], day (d) is [1,31]
   //CTimeDate(uint month, uint d, uint y, uint h, uint min, ADITimeType s);
   //CTimeDate(uint month, uint d, uint y, uint h, uint min, ADITimeType s, ADITimeType UTMinusLocalSecs);
   //CTimeDate triggerTime(5,18,2012,14,30,59.25); //Hard code 14:30:59.25 18 May 2012 as an example
   
   //Alternative for data which is about to be recorded now.
   CTimeDate triggerTime;
   triggerTime.SetCurrentLocalTimeDateAndBias(); //Get time now. Appropriate when sampling new data, although the time measurement should correspond to the time the trigger sample was acquired.
   
   //HRESULT StartRecord(ADITimeDate triggerTickTime, int64 samplingTickAtRecordStart, TTickIndex triggerMinusStartTicks);
   int64 samplingTickAtRecordStart = 0; //ticks since device started sampling. Only important in the case where channels sample at different rates.
   TTickIndex triggerMinusStartTicks = 0; //no pre or post trigger delay
   dataWriter.StartRecord(triggerTime, 0, 0);   //Start the recording process   
   TTickIndex ticksAddedToRecord = 0; 
   
   DataSource::TChannels &channelSources = dataSource.GetChannelSources();
     
   while(ticksAddedToRecord < nTicksInRecord) //loop over chunks of max size kChannelSourceBufferCapacity
      {
      //Now fill the ChannelSources with data.
      //Adding samples in medium sized chunks in parallel across channels results in the most efficient
      //layout of data for scrolling through large files when they are opened in LabChart.
      TTickIndex endSample = std::min<ulong>(ticksAddedToRecord+kChannelSourceBufferCapacity,nTicksInRecord);
      for(TTickIndex sample(ticksAddedToRecord);sample<endSample;++sample)//buffer a chunk of samples
         {
         //buffer chunks of data across channels
         for(int chan(0);chan<nChans;++chan)
            {
            ChannelSourceBase *sourceChannel = channelSources[chan];
            if(!sourceChannel)
               continue; //no data in this channel for this record (channel not enabled in dataWriter.SetupChannel() call above).
            
            const double kRadiansPerSample = 2*M_PI*secsPerSample*(chan+1); //1 Hz for channel 1, 2 Hz for channel 2 etc
      
            //Here we demonstrate two cases: 
            //   1)channels containing int16 (short) data samples which require a units scaling to represent physical values.
            //   2)channels containing float data samples which generally don't require scaling.
            
            //In many real world cases, all the channels would have the same data type, so the following if statement
            //could be removed.
            if(sourceChannel->GetDataValueType()==kADIDataValueFloat)
               {
               ChannelSourceBufferedFloat& channelBuf = static_cast<ChannelSourceBufferedFloat&>(*sourceChannel);
               channelBuf.Add(static_cast<float>(sin(kRadiansPerSample*sample)));
               }
            else if(sourceChannel->GetDataValueType()==kADIDataValue16Bit)
               {
               ChannelSourceBufferedInt16& channelBuf = static_cast<ChannelSourceBufferedInt16&>(*sourceChannel);
               ADIScaling scaleADCValuesToVolts = sourceChannel->GetBaseScaling();
               //The following 2 lines form a somewhat contrived example for generating 16 bit ADC values
               //from floating point data because in practice, one would generally already have 16 bit data
               //available!
               double val = sin(kRadiansPerSample*sample);
               int16 adcValue = RoundToInt(scaleADCValuesToVolts.InverseScale(val));
               
               channelBuf.Add(adcValue);            
               }
            }
         }
      //Add the samples buffered in the ChannelSources to the ADIData object.
      //This cause the ADIData object to begin writing data to the file on disk, on a separate thread.
      ticksAddedToRecord += dataWriter.AddNewData();
      
      //demonstrate adding comments at the last tick in the record 
      dataWriter.AddComment(0,L"End of chunk");
      }
   //Finish off the record.
   dataWriter.EndRecord();
   }
   
//demonstrate adding an all-channel comment at a specific position 
ADIPosition commentPos(nRecords-1, 22000);
dataWriter.AddComment(-1,L"All-channel comment",&commentPos);

//Add a comment to channel 2
commentPos.mRecordOffset = 17000;
dataWriter.AddComment(1,L"Channel 2 comment",&commentPos);

//Add another comment to channel 2
commentPos.mRecordOffset = 15000;
dataWriter.AddComment(1,L"Channel 2 comment 2",&commentPos);

//delete the 2nd last comment in channel 1
//First search backwards for comments in the last record, starting from the end of the record
Iterator<IEnumADIComment> commentIterRev; //Create helper to manager the comment enumerator
commentIterRev.SetEndLimit(0); //Allow the enumerator to search back to the start of the record.
dataWriter->CreateEnumCommentReverse(kSearchSpecificChannelOnly, 0/*channel*/, ADIPosition(nRecords-1,kRecordEndOffset), 0/*left limit*/, 0/*comment type*/, commentIterRev.Set());
++commentIterRev; //skip the last comment.This enumerator goes from right to left, so incrementing it causes it to move to the previous comment!
if(commentIterRev)
   dataWriter.RemoveComment(*commentIterRev); //delete the 2nd last comment

   
dataWriter.CommitFile();
}

const int kOptimalSampleChunkSize = 16000;

//This example illustrates efficiently adding buffers of samples to each channel.
void gWriteSinewavesFromChannelData(IADIDataClass *dataClassObj, const wchar_t *fileName)
{
int nChans = 5;
int nRecords = 2;

DataWriter dataWriter(dataClassObj, fileName);

DataSource &dataSource = dataWriter.GetDataSource();

for(int chan(0);chan<nChans;++chan)
   {
   wstringstream nameStr;
   nameStr<<L"Sine "<<chan+1;
   dataWriter.SetChannelName(chan, nameStr.str().c_str());
   }

//For this example all channels are at the same rate (the tick rate).
double secsPerSample = 0.0025; //2.5 ms => 400Hz
   
//This example illustrates efficiently adding data from pre-existing buffers of non-interleaved samples to each channel.
for(int record(0);record<nRecords;++record)
   {
   //This example demonstrates the simple case where all channels are at the same (tick) rate.
   TTickIndex nTicksInRecord = 24100;
   
   typedef std::vector<float> TChannelBufFloat;
   typedef std::vector<TChannelBufFloat> TDataBuffersFloat;
   typedef std::vector<int16> TChannelBufInt16;
   typedef std::vector<TChannelBufInt16> TDataBuffersInt16;

//In this example we have a mix of float and int16 channels   
   TDataBuffersFloat dataBuffersFloat(nChans);
   TDataBuffersInt16 dataBuffersInt16(nChans);
   
   const long kMaxSourceBufferSize = 0.5*kOptimalSampleChunkSize; //We choose an arbitrary max buffer size for demonstration purposes
   
   //Setup channels
   for(int chan(0);chan<nChans;++chan)
      {
      if(chan < 2)
         {//For this example, the first two channels are 16 bit data
         auto_ptr<ChannelSourceUnbufferedInt16> sourceChan(new ChannelSourceUnbufferedInt16());
         sourceChan->SetSecsPerSample(secsPerSample);

         //For this example choose a 5V bipolar range symmetrical about 0V
         const double kVoltsRangeMax = 5;
         const double kVoltsRangeMin = -5;
         double voltsPerADCUnit = (kVoltsRangeMax-kVoltsRangeMin)/double(k16BitDataScaleTop-k16BitDataScaleBottom);
         double offsetInADCUnits = (kVoltsRangeMax+kVoltsRangeMin)/voltsPerADCUnit; 
         CBaseUnitsInfo baseInfo(ADIScaling(voltsPerADCUnit, offsetInADCUnits));

         sourceChan->SetUnits(L"V", &baseInfo);

         dataSource.SetChannelSource(chan, sourceChan.release());
         }
      else if(chan == 2 && record == 1)
         {//channel 3 is empty in the 2nd record
         dataWriter.SetChannelSource(chan, 0);
         }
      else
         {//Remaining channels contain 32bit floats in Volts.
         auto_ptr<ChannelSourceUnbufferedFloat> sourceChan(new ChannelSourceUnbufferedFloat());
         sourceChan->SetSecsPerSample(secsPerSample);
         sourceChan->SetUnits(L"V");         //default identity scaling is adequate

         dataWriter.SetChannelSource(chan, sourceChan.release());
         }
      }

   //For pre-recorded data where the time of the trigger (or time of first sample if no pre or post trigger samples) is known.
   // N.B. month (m) is [1,12], day (d) is [1,31]
   //CTimeDate(uint month, uint d, uint y, uint h, uint min, ADITimeType s);
   //CTimeDate(uint month, uint d, uint y, uint h, uint min, ADITimeType s, ADITimeType UTMinusLocalSecs);
   CTimeDate triggerTime(5,18,2012,14,30,59.25); //Hard code 14:30:59.25 18 May 2012 as an example

   //Alternative for data which is about to be recorded now.
   //CTimeDate triggerTime;
   //triggerTime.SetCurrentLocalTimeDateAndBias(); //Get time now. Appropriate when sampling new data, although the time measurement should correspond to the time the trigger sample was acquired.

   //HRESULT StartRecord(ADITimeDate triggerTickTime, int64 samplingTickAtRecordStart, TTickIndex triggerMinusStartTicks);
   int64 samplingTickAtRecordStart = 0; //ticks since device started sampling. Only important in the case where channels sample at different rates.
   TTickIndex triggerMinusStartTicks = 0; //no pre or post trigger delay
   dataWriter.StartRecord(triggerTime, 0, 0);   //Start the recording process   
   TTickIndex ticksAddedToRecord = 0; 

   DataSource::TChannels &channelSources = dataSource.GetChannelSources();
         
   //Adding samples in medium sized chunks in parallel across channels results in the most efficient
   //layout of data for scrolling through large files.
   while(ticksAddedToRecord < nTicksInRecord)
      {
      //Loop across channels loading (or, in this case calculating) data from the source into buffers
      for(int chan(0);chan<nChans;++chan)
         {
         ChannelSourceBase *sourceChannel = channelSources[chan];
         if(!sourceChannel)
            continue; //no data in this channel for this record (channel not enabled in dataWriter.SetupChannel() call above).

         const double kRadiansPerSample = 2*M_PI*secsPerSample*(chan+1); //1 Hz for channel 1, 2 Hz for channel 2 etc
                  
         //Here we demonstrate two cases: 
         //   1)channels containing int16 (short) data samples which require a units scaling to represent physical values.
         //   2)channels containing float data samples which generally don't require scaling.
         if(sourceChannel->GetDataValueType()==kADIDataValueFloat)
            {
            TChannelBufFloat& chanBuf = dataBuffersFloat[chan];
            
            TTickIndex numNewSamples = std::min(kMaxSourceBufferSize,nTicksInRecord-ticksAddedToRecord);
            chanBuf.resize(numNewSamples);
            
            int i = 0;
            TTickIndex endSample = ticksAddedToRecord+numNewSamples;  //std::min(ticksAddedToRecord+chanBuf.size(),nTicksInRecord);
            for(TTickIndex sample(ticksAddedToRecord);sample<endSample;++sample,++i)//buffer sample chunks
               {
               float val = sin(kRadiansPerSample*sample);
               chanBuf[i]=val;            
               }
            }
         else if(sourceChannel->GetDataValueType()==kADIDataValue16Bit)
            {
            ADIScaling scaleADCValuesToVolts = sourceChannel->GetBaseScaling();
            
            TChannelBufInt16& chanBuf = dataBuffersInt16[chan];

            TTickIndex numNewSamples = std::min(kMaxSourceBufferSize,nTicksInRecord-ticksAddedToRecord);
            chanBuf.resize(numNewSamples);

            int i = 0;
            TTickIndex endSample = ticksAddedToRecord+numNewSamples;  //std::min(ticksAddedToRecord+chanBuf.size(),nTicksInRecord);
            for(TTickIndex sample(ticksAddedToRecord);sample<endSample;++sample,++i)//buffer sample chunks
               {
               //The following 2 lines form a somewhat contrived example for generating 16 bit ADC values
               //from floating point data because in practice, one would generally already have 16 bit data
               //available!
               double val = sin(kRadiansPerSample*sample);
               int16 adcValue = RoundToInt(scaleADCValuesToVolts.InverseScale(val));
               chanBuf[i]=adcValue;            
               }
            }
         }            

      //Loop across channels setting the channel sources to reference buffers containing data.
      //This code could in this case be moved into the for loop across channels above, but is kept separate here
      //to illustrate the case where the buffered data pre-exists in arrays in memory.
      for(int chan(0);chan<nChans;++chan)
         {
         ChannelSourceBase *sourceChannel = channelSources[chan];
         if(!sourceChannel)
            continue; //no data in this channel for this record (channel not enabled in dataWriter.SetupChannel() call above).

         //Here we demonstrate two cases: 
         //   1)channels containing int16 (short) data samples which require a units scaling to represent physical values.
         //   2)channels containing float data samples which generally don't require scaling.
         if(sourceChannel->GetDataValueType()==kADIDataValueFloat)
            {
            ChannelSourceUnbufferedFloat& channelSource = static_cast<ChannelSourceUnbufferedFloat&>(*sourceChannel);

            //N.B. dataBuffersFloat must not be modified between this ReferenceBuffer() call and the dataWriter.AddNewData(); call below!
            //channelEnum.ReferenceBuffer(&(dataBuffersFloat[chan][dataBufferOffset[chan]]),dataBufferRemaining[chan]);
            channelSource.ReferenceBuffer(&(dataBuffersFloat[chan][0]),dataBuffersFloat[chan].size());
            }
         if(sourceChannel->GetDataValueType()==kADIDataValue16Bit)
            {
            ChannelSourceUnbufferedInt16& channelSource = static_cast<ChannelSourceUnbufferedInt16&>(*sourceChannel);

            //N.B. dataBuffersInt16 must not be modified between this ReferenceBuffer() call and the dataWriter.AddNewData(); call below!
            //channelEnum.ReferenceBuffer(&(dataBuffersInt16[chan][dataBufferOffset[chan]]),dataBufferRemaining[chan]);
            channelSource.ReferenceBuffer(&(dataBuffersInt16[chan][0]),dataBuffersInt16[chan].size());
            }
         }      
      
      //Add samples from the referenced buffers 
      TTickIndex ticksAdded = dataWriter.AddNewData();
      //dataBufferOffset += ticksAdded;
      ticksAddedToRecord += ticksAdded;
      }  
      
   //Finish off the record.
   dataWriter.EndRecord();
   }
dataWriter.CommitFile();
}