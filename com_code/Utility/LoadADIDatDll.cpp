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

#include "LoadADIDatDll.h"

#include <wtypes.h>  
#include <stdlib.h>


//define ADI_USELOADIDATDLL to link explicitly to the ADIDatDll. To link implicitly using the import library leave this undefined.
#ifdef ADI_USELOADIDATDLL


//First set the macro to define the function pointer
#define ADI_X_FUNC_PTR_DEFINE(funcName) T##funcName funcName;

//Define the the function pointers, e.g. TADI_OpenFile ADI_OpenFile;

ADI_X_FUNC_PTR_DEFINE(ADI_OpenFile)
ADI_X_FUNC_PTR_DEFINE(ADI_CreateFile)
ADI_X_FUNC_PTR_DEFINE(ADI_GetErrorMessage)
ADI_X_FUNC_PTR_DEFINE(ADI_TickToSamplePos)
ADI_X_FUNC_PTR_DEFINE(ADI_SamplePosToTick)
ADI_X_FUNC_PTR_DEFINE(ADI_GetNumberOfRecords)
ADI_X_FUNC_PTR_DEFINE(ADI_GetNumberOfChannels)
ADI_X_FUNC_PTR_DEFINE(ADI_GetNumTicksInRecord)
ADI_X_FUNC_PTR_DEFINE(ADI_GetRecordTickPeriod)
ADI_X_FUNC_PTR_DEFINE(ADI_GetNumSamplesInRecord)
ADI_X_FUNC_PTR_DEFINE(ADI_GetRecordSamplePeriod)
ADI_X_FUNC_PTR_DEFINE(ADI_GetRecordTime)
ADI_X_FUNC_PTR_DEFINE(ADI_CreateCommentsAccessor)
ADI_X_FUNC_PTR_DEFINE(ADI_CloseCommentsAccessor)
ADI_X_FUNC_PTR_DEFINE(ADI_GetCommentInfo)
ADI_X_FUNC_PTR_DEFINE(ADI_NextComment)
ADI_X_FUNC_PTR_DEFINE(ADI_GetSamples)
ADI_X_FUNC_PTR_DEFINE(ADI_GetUnitsName)
ADI_X_FUNC_PTR_DEFINE(ADI_GetChannelName)
ADI_X_FUNC_PTR_DEFINE(ADI_SetChannelName)
ADI_X_FUNC_PTR_DEFINE(ADI_CreateWriter)
ADI_X_FUNC_PTR_DEFINE(ADI_SetChannelInfo)
ADI_X_FUNC_PTR_DEFINE(ADI_StartRecord)
ADI_X_FUNC_PTR_DEFINE(ADI_AddChannelSamples)
ADI_X_FUNC_PTR_DEFINE(ADI_FinishRecord)
ADI_X_FUNC_PTR_DEFINE(ADI_CommitFile)
ADI_X_FUNC_PTR_DEFINE(ADI_CloseWriter)
ADI_X_FUNC_PTR_DEFINE(ADI_AddComment)
ADI_X_FUNC_PTR_DEFINE(ADI_DeleteComment)
ADI_X_FUNC_PTR_DEFINE(ADI_CloseFile)

//Now set the macro to initialise the function pointer
#undef ADI_X_FUNC_PTR_DEFINE
#define ADI_X_FUNC_PTR_DEFINE(funcName) funcName =(T##funcName##) GetProcAddress(dllInstance, #funcName);


HMODULE LoadADIDatDll()
{
HMODULE dllInstance = 0;

#if defined(_M_IX86)
const wchar_t *dllName = L"ADIDatIOWin.dll";
#else
const wchar_t *dllName = L"ADIDatIOWin64.dll";
#endif

wchar_t pathName[_MAX_PATH];
_wsearchenv_s(dllName,L"ADIDATPATH",pathName);

if(pathName[0])
   dllInstance=::LoadLibrary(pathName); //try loading from environment variable path

//Try looking in the executable directory
dllInstance=::LoadLibrary(dllName); 

//Try looking in the standard places nearby   
if(!dllInstance)
   {
   wchar_t path[4*_MAX_PATH];
   wcscpy_s(path,L"..\\bin\\");
   wcscat_s(path,dllName);
   dllInstance=::LoadLibrary(path); 
   }  
if(!dllInstance)
   {
   wchar_t path[4*_MAX_PATH];
   wcscpy_s(path,L"..\\..\\bin\\");
   wcscat_s(path,dllName);
   dllInstance=::LoadLibrary(path); 
   }  
if(!dllInstance)
   {
   wchar_t path[4*_MAX_PATH];
   wcscpy_s(path,L"..\\..\\..\\bin\\");
   wcscat_s(path,dllName);
   dllInstance=::LoadLibrary(path); 
   }  
   
if(dllInstance) 
   {
   //e.g. ADI_OpenFile = (TADI_OpenFile) GetProcAddress(dllInstance, "ADI_OpenFile");
   ADI_X_FUNC_PTR_DEFINE(ADI_OpenFile)
   ADI_X_FUNC_PTR_DEFINE(ADI_CreateFile)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetErrorMessage)
   ADI_X_FUNC_PTR_DEFINE(ADI_TickToSamplePos)
   ADI_X_FUNC_PTR_DEFINE(ADI_SamplePosToTick)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetNumberOfRecords)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetNumberOfChannels)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetNumTicksInRecord)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetRecordTickPeriod)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetNumSamplesInRecord)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetRecordSamplePeriod)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetRecordTime)
   ADI_X_FUNC_PTR_DEFINE(ADI_CreateCommentsAccessor)
   ADI_X_FUNC_PTR_DEFINE(ADI_CloseCommentsAccessor)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetCommentInfo)
   ADI_X_FUNC_PTR_DEFINE(ADI_NextComment)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetSamples)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetUnitsName)
   ADI_X_FUNC_PTR_DEFINE(ADI_GetChannelName)
   ADI_X_FUNC_PTR_DEFINE(ADI_SetChannelName)
   ADI_X_FUNC_PTR_DEFINE(ADI_CreateWriter)
   ADI_X_FUNC_PTR_DEFINE(ADI_SetChannelInfo)
   ADI_X_FUNC_PTR_DEFINE(ADI_StartRecord)
   ADI_X_FUNC_PTR_DEFINE(ADI_AddChannelSamples)
   ADI_X_FUNC_PTR_DEFINE(ADI_FinishRecord)
   ADI_X_FUNC_PTR_DEFINE(ADI_CommitFile)
   ADI_X_FUNC_PTR_DEFINE(ADI_CloseWriter)
   ADI_X_FUNC_PTR_DEFINE(ADI_AddComment)
   ADI_X_FUNC_PTR_DEFINE(ADI_DeleteComment)
   ADI_X_FUNC_PTR_DEFINE(ADI_CloseFile)
   }  

return dllInstance;
}

void UnloadADIDatDll(HMODULE dllInstance)
{
FreeLibrary(dllInstance);
}


#endif //ADI_USELOADIDATDLL