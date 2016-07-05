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

#ifndef GlobalDefinesPortable_H_
#define GlobalDefinesPortable_H_

//#include "CrossPlatform/config/config.hpp"
#define ADI_TARGET_OS_WIN32 1
#define PUBLIC_OEM_UTIL 1        //hide e.g. boost dependencies in ADIBaseTypes.idl

#ifdef ADI_TARGET_OS_WIN32
#ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
//For VC8 we can fix deprecated warning for things like strcpy by changing to strcpy_s.
//This defines templates that determine the extra size parameter at compile time for static arrays.
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1
#endif
#endif

#ifdef ADI_TARGET_OS_WIN32
#ifndef NOMINMAX
#define NOMINMAX            //Suppress min and max defines (turns off Microsoft macro).
#define __MINMAX_DEFINED    //Suppresses OWL versions
#endif
#endif

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include <algorithm>
using std::min;
using std::max;

#ifdef ADI_TARGET_OS_WIN32
#ifndef _ATL_NO_UUIDOF
#define _ATL_NO_UUIDOF
//#error define _ATL_NO_UUIDOF on the command line
#endif
#endif


#if _MSC_VER >= 1200 || __BORLANDC__ > 0x540
   #define __TMPL_FULL_SPEC_SYNTAX 1
   #define ADI_FULL_TPL_SPEC_SYNTAX
#elif defined(__MWERKS__) || defined(__GNUC__)
   #define ADI_FULL_TPL_SPEC_SYNTAX
#else
   #define __TMPL_FULL_SPEC_SYNTAX 0
#endif  

#ifdef ADI_FULL_TPL_SPEC_SYNTAX
 template <bool> struct StaticChecker;
 template <> struct StaticChecker<true>{};
 template <int SizeIs> struct ADIShowSize;
 // Use: ADIShowSize <sizeof (type)> test;
 // to generate a compile time error showing sizeof (type) 
#endif


template <class type>
inline int CountOf (type const &x)
	{// Return number of items in C array x
	return sizeof (x) / sizeof (x [0]);
	}

// Add a declare macro to match the definiton flavour of the hybrid DEFINE_GUID macro. A small
// part of a pattern to eliminate link errors from duplicate GUID in non-Windows compiles.
// http://wiki.adi.co.nz/wiki/bin/view/Main/InitGuid
#define ADI_DECLARE_GUID(name) \
        EXTERN_C const GUID name

#endif