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


#ifndef ADIDataWriter_H__
#define ADIDataWriter_H__

#include "adidat/include/IADIDataTypes.h"
#include "adidat/include/ADIDataObject_h.h"  //IADIDataClass

#include "Utility/ADIDataSource.h"


namespace ADI
{


//Helper class that holds onto the interfaces needed to write (and read) data to (and from)
//an ADIDataObject.
class DataWriter : public COMPtr<IADIData>
{
   typedef COMPtr<IADIData> Base;
public:
   
   explicit DataWriter(IADIDataClass *dataObjectClass, const wchar_t *outputFile);
   explicit DataWriter(IADIData *adiData);

   virtual ~DataWriter();
      
   HRESULT SetChannelName(ADIChannelId chanId, const wchar_t *name);
   
   HRESULT SetChannelName(int chanIndex, const wchar_t *name)
      {
      return SetChannelName(ADIChannelId(chanIndex, kADIDataRecorded), name);
      }
      
   HRESULT SetChannelSource(int chan, ChannelSourceBase *channelSource);
   
  
/**
Creates a new record the specified time information, ready to receive new data.
Params:
   triggerTickTime           - timestamp for the trigger tick.
                               This is the 0 time tick (time origin) for the record (in the LabChart "time from
                               start of block" mode. Note that the trigger tick need not be the first tick in 
                               the record. It is possible that the trigger tick is not actually part of the 
                               recorded data where pre or post triggering has been used.
   samplingTickAtRecordStart - tick number of the first record tick counted from when the
                               hardware started sampling.
   triggerMinusStartTicks    - tick delta between samplingTickAtRecordStart and the notional
                               trigger point tick (+ve => pre-trigger, -ve => post-trigger).
*/
   HRESULT StartRecord(ADITimeDate triggerTickTime, int64 samplingTickAtRecordStart, TTickIndex triggerMinusStartTicks);
   

/** 
   Adds any data in the ChannelSources to the ADIData object. In general, for greatest efficiency, 
   this should be called many times for large records.
   Returns the number of new ticks added in this call.
*/
   TTickIndex AddNewData();
/**
   Terminates the currently recording record, and causes the ADIData object to release
   the channel data source enumerators.
*/  
   HRESULT EndRecord();
   
/** AddComment
Adds a new comment at the specified position in the existing data.
Params:        chan              - channel to add the comment to. Should be -1 for all-channel comments.
               text              - comment text
               tickPos           - specifies record and tick within record at which to position the comment. 
                                   Optional - if 0 and sampling is in progress, comment is added at the end of the sampling record.
               cafid             - optional comment type identifier. 0 for user comments.
               addedCommentOut   - optional reference to the added comment. May be 0.
*/
   HRESULT AddComment(int chan, const wchar_t *text, const ADIPosition *tickPos = 0, TCAFId typeId = 0, IADIComment **addedCommentOut = 0);
   
/** RemoveComment
Removes the comment passed in from the ADIData object.
Params:        comment           - reference to the comment to be removed
Return:   S_OK on success, E_INVALIDARG if comment is not found in the ADIData object.
*/
   HRESULT RemoveComment(IADIComment *comment);
   
   HRESULT CommitFile(TGenericFlags flags = 0);
   
   
   ADI::DataSource & GetDataSource()
      {
      return *mDataSource;
      }
       
       
   //IADIData* ADIData()
   //   {
   //   return mADIData.Get();
   //   }       
protected:
   ADI::COMPtr<IADIDataWriter> mWriter;      //Holds the ADIData object via its IADIDataWriter interface.
   //ADI::COMPtr<IADIData> mADIData;           //Holds the ADIData object via its IADIData interface.
   ADI::COMPtr<IADIDataSink> mDataSink;      //Holds the ADIData object via its IADIDataSink interface.
   ADI::COMPtr<ADI::DataSource> mDataSource; //Holds object supplying source data enumerators to the ADIData object.
   TTickIndex mTicksInRecord;   
};


}//namespace



#endif