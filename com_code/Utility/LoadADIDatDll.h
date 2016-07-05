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

#ifndef ADIDatCAPILoadLib_H__
#define ADIDatCAPILoadLib_H__

//define ADI_USELOADIDATDLL to link explicitly to the ADIDatDll. 
//Leave this undefined to link implicitly using the import library (adidat/lib/ADIDatIOWin.lib).
#define ADI_USELOADIDATDLL 1

#include "adidat/include/ADIDatCAPI.h"

#include <wtypes.h>  


#ifdef ADI_USELOADIDATDLL

HMODULE LoadADIDatDll(void);

void UnloadADIDatDll(HMODULE dllInstance);

//Declare pointers to functions for the functions exported from the dll. 
//These are initialised by LoadADIDatDll() if the dll is successfully loaded.

typedef ADIResultCode (*TADI_OpenFile)(const wchar_t* path, ADI_FileHandle* fileH, ADIFileOpenMode mode);
extern TADI_OpenFile ADI_OpenFile;

typedef ADIResultCode (*TADI_CreateFile)(const wchar_t* path, ADI_FileHandle* fileH);
extern TADI_CreateFile ADI_CreateFile;

typedef const wchar_t* (*TADI_GetErrorMessage)(ADIResultCode code, wchar_t* messageOut, 
   long maxChars, long *textLen);
extern TADI_GetErrorMessage ADI_GetErrorMessage;

typedef ADIResultCode (*TADI_TickToSamplePos)(ADI_FileHandle fileH, long channel, long record, 
                                            long tickInRecord, double* samplePosInRecord);
extern TADI_TickToSamplePos ADI_TickToSamplePos;                                            

typedef ADIResultCode (*TADI_SamplePosToTick)(ADI_FileHandle fileH, long channel, long record, 
                                            double samplePosInRecord, double* tickInRecord);
extern TADI_SamplePosToTick ADI_SamplePosToTick;
                                            
typedef ADIResultCode (*TADI_GetNumberOfRecords)(ADI_FileHandle fileH, long* nRecords);
extern TADI_GetNumberOfRecords ADI_GetNumberOfRecords;

typedef ADIResultCode (*TADI_GetNumberOfChannels)(ADI_FileHandle fileH, long* nChannels);
extern TADI_GetNumberOfChannels ADI_GetNumberOfChannels;

typedef ADIResultCode (*TADI_GetNumTicksInRecord)(ADI_FileHandle fileH, long record, long* nTicks);
extern TADI_GetNumTicksInRecord ADI_GetNumTicksInRecord;

typedef ADIResultCode (*TADI_GetRecordTickPeriod)(ADI_FileHandle fileH, long channel, long record, 
                                                double* secsPerTick);
extern TADI_GetRecordTickPeriod ADI_GetRecordTickPeriod;                                                

typedef ADIResultCode (*TADI_GetNumSamplesInRecord)(ADI_FileHandle fileH, long channel, long record, 
                                                  long* nSamples);
extern TADI_GetNumSamplesInRecord ADI_GetNumSamplesInRecord;
                                                  
typedef ADIResultCode (*TADI_GetRecordSamplePeriod)(ADI_FileHandle fileH, long channel, long record, 
                                                  double* secsPerSample);
extern TADI_GetRecordSamplePeriod ADI_GetRecordSamplePeriod;                                                  

typedef ADIResultCode (*TADI_GetRecordTime)(ADI_FileHandle fileH, long record, time_t *triggerTime, 
                                          double *fracSecs, long *triggerMinusStartTicks);
extern TADI_GetRecordTime ADI_GetRecordTime;
                                          
typedef ADIResultCode (*TADI_CreateCommentsAccessor)(ADI_FileHandle fileH, long record, 
                                                   ADI_CommentsHandle* commentsH);
extern TADI_CreateCommentsAccessor ADI_CreateCommentsAccessor;                                                   

typedef ADIResultCode (*TADI_CloseCommentsAccessor)(ADI_CommentsHandle *commentsH);
extern TADI_CloseCommentsAccessor ADI_CloseCommentsAccessor;

typedef ADIResultCode (*TADI_GetCommentInfo)(ADI_CommentsHandle commentsH, long *tickPos, long *channel, long *commentNum, wchar_t* text, 
                                           long maxChars, long *textLen);
extern TADI_GetCommentInfo ADI_GetCommentInfo;
                                           
typedef ADIResultCode (*TADI_NextComment)(ADI_CommentsHandle commentsH);
extern TADI_NextComment ADI_NextComment;

typedef ADIResultCode (*TADI_GetSamples)(ADI_FileHandle fileH, long channel, long record, long startPos, 
                                       ADICDataFlags dataType, long nLength, float* data, long* returned);
extern TADI_GetSamples ADI_GetSamples;                                       

typedef ADIResultCode (*TADI_GetUnitsName)(ADI_FileHandle fileH, long channel, long record, wchar_t* units, 
                                         long maxChars, long *textLen);
extern TADI_GetUnitsName ADI_GetUnitsName;
                                         
typedef ADIResultCode (*TADI_GetChannelName)(ADI_FileHandle fileH, long channel, wchar_t* name, 
                                           long maxChars, long *textLen);
extern TADI_GetChannelName ADI_GetChannelName;                                           

typedef ADIResultCode (*TADI_SetChannelName)(ADI_FileHandle fileH, long channel, const wchar_t* name);
extern TADI_SetChannelName ADI_SetChannelName;

typedef ADIResultCode (*TADI_CreateWriter)(ADI_FileHandle fileH, ADI_WriterHandle* writerH);
extern TADI_CreateWriter ADI_CreateWriter;

typedef ADIResultCode (*TADI_SetChannelInfo)(ADI_WriterHandle writerH, long channel, int enabled, 
                                           double secondsPerSample, const wchar_t* units, const ADIDataLimits *limits);
extern TADI_SetChannelInfo ADI_SetChannelInfo;                                           

typedef ADIResultCode (*TADI_StartRecord)(ADI_WriterHandle writerH, time_t triggerTime, 
                                        double fracSecs, long triggerMinusStartTicks);
extern TADI_StartRecord ADI_StartRecord;
                                        
typedef ADIResultCode (*TADI_AddChannelSamples)(ADI_WriterHandle writerH, long channel, 
                                              float* data, long nSamples, long *newTicksAdded);
extern TADI_AddChannelSamples ADI_AddChannelSamples;                                              

typedef ADIResultCode (*TADI_FinishRecord)(ADI_WriterHandle writerH);
extern TADI_FinishRecord ADI_FinishRecord;

typedef ADIResultCode (*TADI_CommitFile)(ADI_WriterHandle writerH, long flags);
extern TADI_CommitFile ADI_CommitFile;

typedef ADIResultCode (*TADI_CloseWriter)(ADI_WriterHandle *writerH);
extern TADI_CloseWriter ADI_CloseWriter;

typedef ADIResultCode (*TADI_AddComment)(ADI_FileHandle fileH, long channel, long record, long tickPos, 
                                       const wchar_t* text, long* commentNum);
extern TADI_AddComment ADI_AddComment;                                       

typedef ADIResultCode (*TADI_DeleteComment)(ADI_FileHandle fileH, long commentNum);
extern TADI_DeleteComment ADI_DeleteComment;

typedef ADIResultCode (*TADI_CloseFile)(ADI_FileHandle* fileH);
extern TADI_CloseFile ADI_CloseFile;

#endif //ADI_USELOADIDATDLL

#endif