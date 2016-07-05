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

#include "ReadWriteSinewaves.h"


#include "Utility/ADIMath.h"
#include "Utility/ADIDataWriter.h"
#include "Utility/ADICBaseUnitsInfo.h"
#include "Utility/CTimeDate.h"
#include "Utility/ADIIterator.h"
#include "Utility/ADIStringPtr.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace ADIMath;
using namespace ADI;
using namespace std;




//This example illustrates efficiently adding individual samples to each channel.
//This is particularly useful for situations where the source data has the samples interleaved
//across channels , as would commonly be the case when reading samples from a text file,
//or a sound card.
HRESULT gAddCommentsToExistFile(IADIDataClass *dataClassObj, const wchar_t *fileName, bool useADIDatFormat)
   {
   
   COMPtr<IClassFactory> classFactory(ADI::query_cast(dataClassObj));
   if(!classFactory)
      return E_FAIL;
   
   COMPtr<IADIDataWriter> dataWriterI;
   HRESULT hr = classFactory->CreateInstance(0, IID_IADIDataWriter,(void**)dataWriterI.Set());
   if(FAILED(hr))
      return hr;
   
   //QueryInterface for the custom class object interface (IADIDataClass) so we can have access to 
   //IADIDataClass::GetErrorMessage() before we have an IADIData interface (which also
   //implements GetErrorMessage()).
   COMPtr<IADIDataClass> adiDataClass(ADI::query_cast(classFactory));
   MYASSERT(adiDataClass);
   
   //Opening the file for writing can fail if the file already contains data which has been written in a
   //later format than the new data will be written in. This is more likely to happen if the new data is 
   //written with the kADIWriteInADIDATFormat since this corresponds to LabChart 6.1.1 data.
   if(useADIDatFormat)
      hr = dataWriterI->CreateADIFile(fileName, ADIFileOpenFlags(kADIOpenFileForReadAndWrite | kADIWriteInADIDATFormat));
   else
      hr = dataWriterI->CreateADIFile(fileName, kADIOpenFileForReadAndWrite);
   
   if(FAILED(hr))
      {
      if(adiDataClass)
         {
         StringPtr errorMsg;
         adiDataClass->GetErrorMessage(hr,ADIReservedFlags(0),errorMsg.Set());
         wcout<<errorMsg.c_str()<<endl;
         }      
      return hr;
      }

   COMPtr<IADIDataSink> dataSink;
   hr = dataWriterI->GetADIDataSink(dataSink.Set());
   
   COMPtr<IADIData> adiData(query_cast(dataSink));
   
   int nChans = 5;
   int nRecords = 2;
   
   DataWriter dataWriter(adiData.Get());

   DataSource &dataSource = dataWriter.GetDataSource();

   //Add comment to 1st record
   ADIPosition commentPos0(0, 100);
   dataWriter.AddComment(1,L"Channel 2 comment 2",&commentPos0);

   dataWriter.CommitFile();
   
   return S_OK;
   }
