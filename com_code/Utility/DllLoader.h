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


#ifndef DllLoader_H_
#define DllLoader_H_

#include "Utility/ADICOMPtr.h"

#include <iostream>


class CoInit
   {
   public:
      CoInit()
         {
         //      CoInitializeEx(0,COINIT_APARTMENTTHREADED);
         CoInitialize(0);
         }
      ~CoInit()
         {CoUninitialize();}
   };


//This object will attempt to load the ChartReader dll even if it is
//not registered with COM.
//While Registration is necessary for use with Visual Basic, C++ client programs
//may not want to bother with it.
//This code should work if the ChartReader.dll is in the same directory as the
//client executable.
   
   //const TCHAR
class DllLoader
   {
   public:
      DllLoader(const wchar_t *dllName, REFCLSID rclsid);
      ~DllLoader();

      IClassFactory* GetClassObj()
         { 
         return mClassObj.Get();
         }

   private:
      HINSTANCE mHMod;
      ADI::COMPtr<IClassFactory> mClassObj;
      HRESULT mHResult;
   };

   //OLD CODE
    //DllLoader::DllLoader(const TCHAR *dllName, REFCLSID rclsid) :
   
DllLoader::DllLoader(const wchar_t *dllName, REFCLSID rclsid) :
   mHMod((HINSTANCE)HINSTANCE_ERROR),
   mHResult(E_FAIL)
      {
      using namespace std;
      wcout<<L"Loading "<<dllName<<endl;
      
      wchar_t pathName[_MAX_PATH];
      
      _wsearchenv(dllName,L"ADIDATPATH",pathName);
      
      
      // Note: _searchenv is deprecated; consider using _searchenv_s
      if(pathName[0])
         mHMod=::LoadLibrary(pathName); //try loading explicitly first
         
      //Try looking in the standard place nearby   
      if(mHMod <= (HINSTANCE)HINSTANCE_ERROR)
         {
         wstring path(L"..\\bin\\");
         path += dllName;
         mHMod=::LoadLibrary(path.c_str()); //try loading explicitly first
         }  
      if(mHMod <= (HINSTANCE)HINSTANCE_ERROR)
         {
         wstring path(L"..\\..\\bin\\");
            path += dllName;
         mHMod=::LoadLibrary(path.c_str()); //try loading explicitly first
         }  
      if (mHMod > (HINSTANCE)HINSTANCE_ERROR)
         {
         wcout<<L"LoadLibrary succeeded"<<endl;
         //   STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
         HRESULT (STDAPICALLTYPE *pfn)(REFCLSID, REFIID, LPVOID* );
         (FARPROC&)pfn=::GetProcAddress(mHMod, "DllGetClassObject");

         if (pfn)
            mHResult=(*pfn)(rclsid, IID_IClassFactory, (void**)mClassObj.Set());
         }
      else
         { //dll not found, see if it is registered
         cout<<"dll not found, trying CoGetClassObject()"<<endl;
         mHResult = ::CoGetClassObject(
            rclsid,
            CLSCTX_INPROC_SERVER,
            0,
            IID_IClassFactory,
            (void**)mClassObj.Set()
            );
         if(SUCCEEDED(mHResult))
            cout<<"CoGetClassObject() succeeded"<<endl;
         else
            cout<<"CoGetClassObject() failed with HRESULT: "<<mHResult<<endl;
         }
      }

   DllLoader::~DllLoader()
      {
      mClassObj.Clear();
      if(mHMod > (HINSTANCE)HINSTANCE_ERROR)
         ::FreeLibrary(mHMod);
      mHMod = (HINSTANCE)HINSTANCE_ERROR;
      }
      
      
      
#endif      
