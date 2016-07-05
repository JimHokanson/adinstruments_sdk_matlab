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

#include <clocale>
#include <locale>
#include <string>
#include <vector>

#include "ADIDataWriter.h"
#include "Utility/ADIStringPtr.h"

//Convert wide wstring to narrow string
inline std::string narrow(std::wstring const& text)
   {
   std::locale const loc("");
   wchar_t const* from = text.c_str();
   std::size_t const len = text.size();
   std::vector<char> buffer(len + 1);
   std::use_facet<std::ctype<wchar_t> >(loc).narrow(from, from + len, '_', &buffer[0]);
   return std::string(&buffer[0], &buffer[len]);
   }

using namespace ADI;

DataWriter::DataWriter(IADIDataClass *dataObjectClass, const wchar_t *outputFile)
{
//Create output file
HRESULT hr = dataObjectClass->CreateNew(outputFile,0,mWriter.Set());

if(hr != S_OK)
   {
   ADI::StringPtr message;
   dataObjectClass->GetErrorMessage(hr,ADIReservedFlags(0),message.Set());
   std::string msg("Unable to open or create file: ");
   msg += narrow(message.c_str()); //Convert wide wstring to narrow string
   throw std::exception(msg.c_str());
   }

if(!mWriter)
   //throw std::exception(ADI::MessageFromHRESULT(hr,"Unable to create file : "));
   throw std::exception("Unable to create file");
   
mWriter->GetADIDataSink(mDataSink.Set());
Base::operator=(ADI::query_cast(mDataSink));

mDataSource = new DataSource();

mDataSink->PrepareForSampling(0);

}


DataWriter::DataWriter(IADIData *adiData)
{
////Create output file
//HRESULT hr = dataObjectClass->CreateNew(outputFile,0,mWriter.Set());

mWriter = ADI::query_cast(adiData);

if(!mWriter)
   //throw std::exception(ADI::MessageFromHRESULT(hr,"Unable to create file : "));
   throw std::exception("Unable to write to file");

mWriter->GetADIDataSink(mDataSink.Set());
Base::operator=(ADI::query_cast(mDataSink));

mDataSource = new DataSource();

mDataSink->PrepareForSampling(0);

}


DataWriter::~DataWriter()
{

}

HRESULT DataWriter::SetChannelSource(int chan, ChannelSourceBase *channelSource)
{
return mDataSource->SetChannelSource(chan, channelSource);
}

HRESULT DataWriter::SetChannelName(ADIChannelId chanId, const wchar_t *name)
{
return mDataSink->SetChannelName(chanId, name);
}



HRESULT DataWriter::StartRecord(ADITimeDate triggerTickTime, int64 samplingTickAtRecordStart, TTickIndex triggerMinusStartTicks)
{

mDataSource->SetupChannels(mDataSink.Get());

mTicksInRecord = 0;

//double secsPerTick = mDataSource->GetSecsPerTick();
//do we need secsPerTick in this method, or could we use the value from the sampling record in ChartMemData?
return mDataSink->OnRecordStart(ADIRecordFlags(0),mDataSource.Get(),triggerTickTime,samplingTickAtRecordStart,triggerMinusStartTicks,true);
}


TTickIndex DataWriter::AddNewData()
{
TTickIndex ticks = mDataSource->GetTicks();
TTickIndex newTicks = ticks-mTicksInRecord;
mDataSink->Update(newTicks);
mTicksInRecord = ticks;
return newTicks;
}

HRESULT DataWriter::AddComment(int chan, const wchar_t *text, const ADIPosition *tickPos, TCAFId typeId, IADIComment **addedCommentOut)
{
return mDataSink->AddComment(ADIChannelId(chan,kADIDataRecorded),text,tickPos,typeId,addedCommentOut);
}

HRESULT DataWriter::RemoveComment(IADIComment *comment)
{
return mDataSink->RemoveComment(comment);
}


HRESULT DataWriter::EndRecord()
{
return mDataSink->OnRecordEnd(0);
}

HRESULT DataWriter::CommitFile(TGenericFlags flags)
{
mDataSink->CleanUpAfterSampling(false);
return mWriter->CommitFile(flags);
}

