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



/*
Essential goals from http://wiki.adi.co.nz/wiki/bin/view/Main/CrossPlatformGuidelines
   diagostics for strong and weak runtime assertion failures
   ability to turn weak diagnostics on and off

***************************

ADIDEBUG controls whether any code is generated for assertion checks, and is either undefined or 1.


ADIASSERT is a strong assert, and should not fire in normal use of the program. (Also ADIASSERTX.)
   An important runtime issue has occurred. 
   So important that is is worth risking killing the program to notify the programmer.

e.g. ADIASSERT(prefsStorage != 0);


ADICHECK is a weak assert which is off by default. (Also ADICHECKX.)
   You can control at launch time and at runtime whether to have these on or off, although the method will be platform specific.

e.g. ADICHECK(name.length() < 32);


Mac personal setting for ADICHECK:
   defaults write "com.adinstruments.LabChart Reader" ADICHECK_STARTING_LEVEL 1


The intention is that this file will do something appropriate for the platform, but that clients can change
behaviour across a whole project by doing something reasonable. 
1) This is a minimal set of macros after much discussion to try and address noisy asserts, and especially to start with we want to keep it minimal.
   (i.e. We are not trying to support every possibly useful macro, like CAFCHECK0, PRECONDITION, VERIFY etc etc.)
2) support for client override customization is being added as needed, as not clear what will suit clients best.

***************************

Reference files:

C++: 
    <cassert>
	<assert.h>
CfW:
	<checks.h>
	"PCDevelop/Main/Utility/diagnostics.h" [legacy]
CfM:
	<CarbonCore/Debugging.h>
	<AssertMacros.h>
	"MacDevelop/Common/LibraryCommon/MacDiagnostics.h" [legacy]
    
Boost:
   "boost/assert.hpp"
   "boost/static_assert.hpp"

What's the best way to write a multi-statement macro?
   http://c-faq.com/cpp/multistmt.html

Future considerations:
   a standard way to handle personal and/or area checks
   make more of the extra features common, some individual platforms have support for runtime quiet all, quiet specific assert, show all asserts only once et al
   trace
   able to switch out assert handler at runtime rather than using macros (e.g. might work well for unit tests)
      
*/

#ifndef PURE_UTILITY_CROSSDEBUG_H
#define PURE_UTILITY_CROSSDEBUG_H

//#include "CrossPlatform/config/config.hpp"

#ifdef ADI_HAS_PRAGMA_ONCE
#pragma once
#endif


#ifdef ADI_TARGET_OS_MAC
#include <CoreServices/CoreServices.h>
#endif
#ifdef ADI_TARGET_OS_WIN32
#include <tchar.h>
#endif

// _DEBUG from MSC
#if defined(ADI_TARGET_OS_WIN32) && defined(_DEBUG) && !defined(ADIDEBUG)
#define ADIDEBUG 1
#endif


//--------------------------------------------------------------------
// Sanity check ADIDEBUG. 
// Check is either undefined or defined as 1, so clients can use either of "#ifdef ADIDEBUG" or plain "#if ADIDEBUG". 
// (If you have it defined but without a value, you get a strange compiler message about nothing after the "!".)
#if defined(ADIDEBUG) && !ADIDEBUG
	#error "ADIDEBUG configuration problem, should be either undefined or 1"
#endif
// Sanity check against other conditionals, currently a hard error but we may need to make this a soft warning.
// NDEBUG from traditional C assert usage
#if defined(ADIDEBUG) && defined(NDEBUG)
   #error "Suspect ADIDEBUG configuration, both ADIDEBUG and NDEBUG are defined"
#endif
// __DEBUG from mumble mumble
#if defined(ADI_TARGET_OS_WIN32) && defined(__DEBUG) && (__DEBUG > 0) && !defined(ADIDEBUG)
   #error "Suspect ADIDEBUG configuration, __DEBUG > 0 but ADIDEBUG is not defined"
#endif

    
//--------------------------------------------------------------------
// ADIASSERT_LOOK_BUT_DO_NOT_TOUCH, intended for internal use
// Suppress unused variable warnings without evaluating the expression.
// This is surprsingly hard to do at all, but helps that we are only trying to
// supports expressions that evaluate to something which makes sense in a condition.
// This will be somewhat compiler specific since the details of what triggers warnings are compiler specific.
#define ADIASSERT_LOOK_BUT_DO_NOT_TOUCH(expr) ((void)(1 ? false : (expr) && false))


//--------------------------------------------------------------------
// ADIASSERT_BREAK, intended for internal use
// Drop into debugger. This only gets called if the assertion handler returns false, so the platform specific
// assertion handler can filter the assertions, and especially may check for presence of debugger before attempting to break.
#if ADIDEBUG
   #ifdef ADI_TARGET_OS_MAC
      #define ADIASSERT_BREAK kill(getpid(), SIGINT)
   #endif
#endif


//--------------------------------------------------------------------
// External routine declarations.

// Simple support for allowing runtime control over ADICHECKS, hopefully useable cross-platform
#if defined(ADIDEBUG)
extern int GetWeakAssertLevel();
extern void SetWeakAssertLevel(int level);
#endif

#ifdef ADI_TARGET_OS_MAC
extern bool MacADIAssertHandler(char const * expr, char const * file, long line);

// Extra routine to control whether attempts to display dialog when assert fires. On by default. This is useful
// for suppressing dialogs when the Cocoa runtime is not available, especially during global static construction and destruction.
extern void MacDiagosticsDisplayDialog(int display);
#endif

#ifdef ADI_TARGET_OS_WIN32
// At the moment these are unchanged from diagnostics.h both to ease transition and simplify implementing all of the 
// "other" macros that we are not moving to CrossDebug, PRECONDITION et al. 
enum
   {
   kDiagLevelOfADIAssert = 0,
   kDiagLevelOfADICheck,
   };
bool CafBreakMessage(const _TCHAR *type, const _TCHAR *msg, const _TCHAR *file, int line );
void CafBreakSuppressable(int &suppress, int level, const _TCHAR *type, const _TCHAR *msg, const _TCHAR *file, int line );
#endif


//--------------------------------------------------------------------
// ADIASSERT
#ifdef ADIASSERT
   // Looks like client supplied their own one!
#else
   #define ADIASSERT(expr) ADIASSERTX(expr, #expr)

   #if !defined(ADIDEBUG)
      // expr is not evaluated in release version, but we try and avoid unused variable warnings
      #define ADIASSERTX(expr, message) ADIASSERT_LOOK_BUT_DO_NOT_TOUCH(expr)
   #elif ADI_TARGET_OS_MAC
      #define ADIASSERTX(expr, message) do\
         {\
         if (!(expr) && !MacADIAssertHandler(message, __FILE__, __LINE__))\
            ADIASSERT_BREAK;\
         } while(0)
   #elif ADI_TARGET_OS_WIN32
      // Same style as used in legacy diagnostics.h, no attempt to share implementation with Mac yet
      #define ADIASSERTX(p,s) do\
         {\
         if (!(p))\
            {\
            static int suppress=0;\
            CafBreakSuppressable(suppress, kDiagLevelOfADIAssert, _T("ADIASSERT"), _T(s), _T(__FILE__), __LINE__);\
            }\
         } while(0)
   #else
      // If no custom behaviour from client or platform, fallback to plain assert
      // Untried as yet!
      #include "assert.h"
      #define ADIASSERTX(expr, message) assert(expr)
   #endif
#endif


//--------------------------------------------------------------------
// ADICHECK

// Set up ADICHECK.
// We always evaluate the
#ifdef ADICHECK
   // Looks like client supplied their own one!
#else
   #define ADICHECK(expr) ADICHECKX(expr, #expr)

   #if !defined(ADIDEBUG)
      // expr is not evaluated in release version, but we try and avoid unused variable warnings
      #define ADICHECKX(expr, message) ADIASSERT_LOOK_BUT_DO_NOT_TOUCH(expr)
   #elif ADI_TARGET_OS_MAC
      #define ADICHECKX(expr, message) do\
         {\
         if (!(expr) && (GetWeakAssertLevel() > 0) && !MacADIAssertHandler(message, __FILE__, __LINE__))\
            ADIASSERT_BREAK;\
         } while(0)
   #elif ADI_TARGET_OS_WIN32
      // Same style as used in legacy diagnostics.h, no attempt to share implementation with Mac yet
      // Untried as yet!
      #define ADICHECKX(p,s) do\
         {\
         if (!(p))\
            {\
            static int suppress=0;\
            CafBreakSuppressable(suppress, kDiagLevelOfADICheck, _T("ADICHECK"), _T(s), _T(__FILE__), __LINE__);\
            }\
         } while(0)
   #else
      // If no custom behaviour from client or platform, fallback to plain assert
      // Untried as yet!
      #define ADICHECKX(expr, message) do\
         {\
         if (!(expr) && (GetWeakAssertLevel() > 0))\
            assert(0);\
         } while(0)
   #endif
#endif


#endif	// PURE_UTILITY_CROSSDEBUG_H

