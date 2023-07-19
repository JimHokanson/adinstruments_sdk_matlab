//This example runs the example provided by ADInstruments
//
//
//      mex('adi_example.cpp','-v','ADIDatIOWin64.lib')

#include "mex.h"

#include "stdafx.h"

#define _USE_MATH_DEFINES  //for M_PI
#include <math.h>


#include <stdlib.h>

//#include "Utility/LoadADIDatDll.h"
#include "ADIDatCAPI_mex.h"  //Non COM DLL entry points


bool IsError(ADIResultCode code)
{
if(code != kResultSuccess)
  {
  const int kMaxErrorMsgLen = 1024;
  wchar_t errorMsg[kMaxErrorMsgLen];
  ADI_GetErrorMessage(code,errorMsg,kMaxErrorMsgLen,0);
  wprintf_s(L"\n%s\n", errorMsg);
  return true;
  }
return false;
}

   

//---------------------------------------------
//      main function  
//---------------------------------------------------------
int _tmain()
{

#ifdef ADI_USELOADIDATDLL
HMODULE dllInstance = LoadADIDatDll(); //Explicity link to the dll

if(!dllInstance)
   {
   //cout<<"Usage: TestReader <inputFileName>"<<endl;
   wprintf_s(L"Error: unable to find ADIDatIOWin.dll. Copy this dll to the same folder as the executable.");
   return 1;
   }

#endif

const long kMaxSourceBufferSize(1024);
ADI_FileHandle fileH(0);
ADIResultCode result = ADI_CreateFile(L"CSinewaves.adidat", &fileH); //Create new file
if(IsError(result))
   return 1;

//-------------------------
// Writing data into a file.  
// The procedure is to create a writer object for the file, set up the channel parameters 
// start a new record, then write the new data into the record (remembering to finalize 
// the record when done).
// The same writer may be used to write multiple records to the file.

ADI_WriterHandle writerH(0);
ADI_CreateWriter(fileH, &writerH);

int nRecords = 2;

for(int record = 0;record<nRecords;++record)
   {
   ADIDataLimits dataLimits;
   dataLimits.mMaxLimit = 12.0;
   dataLimits.mMinLimit = -12.0;
   //For this example all channels are at the same rate (the tick rate).
   double samplePeriod = 1.0/2000.0;

   const long nChans = 3;

   //Allocate buffers to hold source data
   float* dataBuffers[nChans];
   long channelLengths[nChans];
   for(int chan = 0;chan<nChans;++chan)
      {
      dataBuffers[chan] = (float*)malloc(sizeof(float) * kMaxSourceBufferSize); 
      channelLengths[chan] = 0;
      result = ADI_SetChannelInfo(writerH, chan, true/*enabled*/, samplePeriod, L"mV", &dataLimits);
      if(IsError(result))
         return 1;
      }

   long nTicksToAddToRecord = 17000;

   time_t time(1336660750+record*60); // 10 May, 2012, 14:39:10 for record 0, 14:40:10 for record 1
   double fracSecs(0.25);
   result = ADI_StartRecord(writerH, time, fracSecs, 0/*trigMinusRecStart*/); //Start a new record
   if(IsError(result))
      return 1;

   long ticksAddedToRecord = 0; 

   //Adding samples in medium sized chunks in parallel across channels results in the most efficient
   //layout of data for scrolling through large files.
   while(ticksAddedToRecord < nTicksToAddToRecord)
      {
      //Loop across channels loading (or, in this case calculating) data from the source into buffers
      for(int chan(0);chan<nChans;++chan)
         {
         const double kRadiansPerSample = 2*M_PI*samplePeriod*(chan+1); //1 Hz for channel 1, 2 Hz for channel 2 etc

         float* chanBuf = dataBuffers[chan];

         long samplesAddedToChannel = channelLengths[chan];
         long numNewSamples = nTicksToAddToRecord-samplesAddedToChannel; //ticksAddedToRecord;
         if(numNewSamples >  kMaxSourceBufferSize)
            numNewSamples = kMaxSourceBufferSize;

         int i = 0;
         long endSample = samplesAddedToChannel+numNewSamples;  //std::min(ticksAddedToRecord+chanBuf.size(),nTicksInRecord);
         for(long sample(samplesAddedToChannel);sample<endSample;++sample,++i)//buffer sample chunks
            {
            float val = sin(kRadiansPerSample*sample);
            chanBuf[i]=val;            
            }
         long newTicks = 0;
         result = ADI_AddChannelSamples(writerH, chan, chanBuf, numNewSamples, &newTicks); //Add samples to the new record
         if(IsError(result))
            return 1;

         channelLengths[chan] += numNewSamples;
         ticksAddedToRecord += newTicks;
         }
      }

   result = ADI_FinishRecord(writerH); // must close the record
   if(IsError(result))
      return 1;

   //Free buffers to hold source data
   for(int chan = 0;chan<nChans;++chan)
      free(dataBuffers[chan]);    
   }

//Add a couple of comments. 
long channel = 0;
long commentNum;
result = ADI_AddComment(fileH, channel, 0/*record*/, 512/*tickPos*/, 
               L"Comment 1", &commentNum);
if(IsError(result))
   return 1;


result = ADI_AddComment(fileH, channel, 0/*record*/, 900/*tickPos*/, 
               L"Comment 2", 0);
if(IsError(result))
   return 1;


//Delete the first comment we added above
result = ADI_DeleteComment(fileH, commentNum);
if(IsError(result))
   return 1;

result = ADI_CommitFile(writerH,0);  //Ensure all changes are written to disk
ADI_CloseWriter(&writerH);  //Release resources held by the writer
if(IsError(result))
   return 1;


result = ADI_CloseFile(&fileH);
if(IsError(result))
   return 1;


#ifdef ADI_USELOADIDATDLL
UnloadADIDatDll(dllInstance);
#endif

return 0;
}

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    _tmain();
}
   
