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


// ADIDatWriteTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Utility/DllLoader.h"

#include <iostream>

#include "adidat/include/ADIDataObject_h.h"  //IADIDataClass
#include "adidat/include/IADIData.h"

#include "ReadWriteSinewaves.h"

#include "WriteSinewaves.h"
//#include "WriteMultirateSinewaves.h"

using namespace ADI;
using namespace std;


HRESULT gAddCommentsToExistFile(IADIDataClass *dataClassObj, const wchar_t *fileName, bool useADIDatFormat);

#include "mex.h"

 
/*

Utility an Interface libs need to be compiled - I used visual studio
Move these libs and the ADIDatIOWin64.lib into the build folder

In DllLoader - changed references const TCHAR to const wchar_t


cd C:\Users\Jim\Documents\ADInstruments\SimpleDataFileSDKCOM\examples\ADIDatReadWrite

 
mex COMPFLAGS="$COMPFLAGS /MD" ...
 -IC:/Users/Jim/Documents/ADInstruments/SimpleDataFileSDKCOM ...
 -IC:/Users/Jim/Documents/ADInstruments/SimpleDataFileSDKCOM/CrossPlatform ...
 -IC:/Users/Jim/Documents/ADInstruments/SimpleDataFileSDKCOM/adidat/include ...
 ...
 -lUtility.lib ...
 -lInterfaceLib.lib ...
 -lADIDatIOWin64.lib ...
 -DUNICODE ...
 ADIDatReadWrite.cpp C:/Users/Jim/Documents/ADInstruments/SimpleDataFileSDKCOM/Utility/LoadADIDatDll.cpp InitGuids.cpp AddCommentsToExistingFile.cpp  -v
ADIDatReadWrite

 * stdafx.cpp

ReadWriteSinewaves.cpp C:/Users/Jim/Documents/ADInstruments/SimpleDataFileSDKCOM/Utility/LoadADIDatDll.cpp InitGuids.cpp stdafx.cpp  -v
 ReadWriteSinewaves
 
 
 */


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray*prhs[])
{
// // // //     _tmain();
// // // // }
// // // // 
// // // // 
// // // // 
// // // // 
// // // // 
// // // // int _tmain() //int argc, _TCHAR* argv[]{
   try
      {
      CoInit coInit; //Initialize COM

      DllLoader loader(L"ADIDatIOWin64.dll", CLSID_ADIDataObject);  //Load ADIDatIOWin.dll. Destructor unloads.

      //Get the Class Object so we can create ADIData objects
      COMPtr<IADIDataClass> dataObjectClass(ADI::query_cast(loader.GetClassObj()));  //does QueryInterface for IChartReaderClass

      if(!dataObjectClass)
         {
         cout<<"Failed to load ADIDatIOWin.dll. Check that it is in the directory specified by the ADIDATPATH environment variable, or the same directory as the executable or registered using regsvr32."<<endl;
         return;
         }

//       //Demonstrate creating a new file and adding some data to it.
//       const wchar_t *dataFileSinewaves = L"..\\..\\DataFiles\\Sinewaves.adicht";
// 
//       //First create a new file with some data in it
//       gWriteSinewavesFromChannelData(dataObjectClass.Get(), dataFileSinewaves);
// 
//       //Append some data to the file
//       gReadWriteSinewaves(dataObjectClass.Get(), dataFileSinewaves);
// 
//       //Append more data to the already appended file
//       gReadWriteSinewaves(dataObjectClass.Get(), dataFileSinewaves);
      
      
      
      
      
      //Now demonstrate adding data to a LabChart settings file with a e.g. a setting to enable a channel calculation
      
      //First copy the settings file to make an empty .adicht data file.
      //bool bFailIfFileExists = false; //This is dangerous, but convenient so this demonstration can be run multiple times.
      //const wchar_t *dataFile = L"..\\..\\DataFiles\\ChannelCalcWithData.adicht";
      //bool ok = CopyFile(L"..\\..\\DataFiles\\ChannelCalc.adiset",dataFile,bFailIfFileExists);
      //if(!ok)
      //   {
      //   wcout << L"CopyFile() failed" <<endl;
      //   return 1;
      //   }
      ////Now append data into the file.
      //bool writeDataInADIDatFormat = false;
      //gReadWriteSinewaves(dataObjectClass.Get(), dataFile,writeDataInADIDatFormat); //Add some data
      //
      //gReadWriteSinewaves(dataObjectClass.Get(),dataFile,writeDataInADIDatFormat);  //Add some more data.


	        //First copy the data file first, for so we don't lose data on unexpected failures
      bool bFailIfFileExists = false; //This is dangerous, but convenient so this demonstration can be run multiple times.
      
      const wchar_t *dataFile = L"C:\\Users\\Jim\\Desktop\\temp_edited\\test.adicht";
      //const wchar_t *dataFile = L"..\\..\\DataFiles\\LC81FileWithComments.adicht";
      //bool ok = CopyFile(L"..\\..\\DataFiles\\LC81File.adicht",dataFile,bFailIfFileExists);
      //Now append data into the file.
      bool writeDataInADIDatFormat = false;
      //gReadWriteSinewaves(dataObjectClass.Get(), dataFile,writeDataInADIDatFormat); //Add some data
	  gAddCommentsToExistFile(dataObjectClass.Get(), dataFile,writeDataInADIDatFormat);


      }
   catch(std::exception &x)
      {
      cout<<"Unhandled Exception: "<<x.what()<<endl;
      return;
      }

   return;
   }

