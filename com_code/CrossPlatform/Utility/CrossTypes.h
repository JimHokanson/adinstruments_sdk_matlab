/*
CrossTypes

Inspiration is CfW's ADIBaseTypes.h, QuickTimes's MacTypes.h, Borland's SysTypes.h, Boost cstdint.hpp et al.
Does not require any of the above.

Rationale for design decisions:
We want uint32, int32 etc (familiar to CfW developers)

We also have UInt32, SInt32 etc (familiar to Mac developers), but these are now deprecated. There isn't
a lot of code using the Mac types in shared code in the latest codebase, so these will go away some rainy day.

If you get a clashing type, or compile explodes in interesting ways in config.hpp:
- it may be a supported configuration, see if the logic below supports including the other file first (e.g. Carbon.h).
- it may be a new issue as environments evolve. Look for most robust way to move forward.
- Talk to JGee, who lovingly crafted this file, and is keen to make it work reasonably everywhere.

It is ok to use (say) uint8_t et al from stdint.h instead of these types. See:
http://wiki.adi.co.nz/wiki/bin/view/Main/CrossPlatformGuidelines

There are static assertions on the size of the types in the optional CrossTypes.cpp file. CrossTypes.h has been used in
some hardware projects with plain C compilers, so we do some extra work to support the widespread use of this header.
*/

// See CVS for full change history. (Simplifies source mirrors, merging, and the clincher was Boost made the same decision!)

#ifndef CROSSPLATFORM_CROSSTYPES_H
#define CROSSPLATFORM_CROSSTYPES_H

#include "CrossPlatform/config/config.hpp"

// Lint-like care, use "pragma once" after including config.hpp to get conditional
#ifdef ADI_HAS_PRAGMA_ONCE
#pragma once
#endif

// By default define the CfW flavour first and use it for the Mac flavour
#define CROSSTYPES_TYPEDEF_MAC_FROM_WIN


#if defined(ADI_TARGET_OS_WIN32)
    // KISS. These are same as in SysTypes.h and ADIBaseTypes.h.
    typedef signed char     int8;
    typedef unsigned char   uint8;
    typedef signed short    int16;
    typedef unsigned short  uint16;
    typedef signed long     int32;
    typedef unsigned long   uint32;
    // 64 bit support is more suspect, do something that might work
    #if defined(ADI_HAS_MS_INT64)
        typedef signed __int64      int64;
        typedef unsigned __int64    uint64;
    #else
        typedef signed long long    int64;
        typedef unsigned long long  uint64;
    #endif
#elif defined(ADI_TARGET_OS_MAC)
    #undef CROSSTYPES_TYPEDEF_MAC_FROM_WIN
    // See below. A couple of special cases mean starting from CfW flavours is not convenient.
#elif 1 && defined(ADI_HAS_STDINT_H)
    // Using stdint.h is appealing, but turns out to cause problems in our legacy code where we have mixed use 
    // of (especially) long and int32. Historically on both Mac and Windows the foo32 types are long, but on Linux 
    // int32_t is an int. This leads to some compile problems we first hit in LabChart Online  that we are not 
    // interested in chasing at the moment, so the ADI_HAS_STDINT_H conditional branch is disabled for now. 
    // A good time to revisit this might be when we take a serious look at 64 bit compiles.

    // rua trying this now - hoping to fix the long/int32 bugs while I'm at it
        // places we used long should often be int64
    #include <stdint.h>
    typedef int8_t    int8;
    typedef int16_t   int16;
    typedef int32_t   int32;
    typedef uint8_t   uint8;
    typedef uint16_t  uint16;
    typedef uint32_t  uint32;
    #ifndef ADI_NO_INT64_T
    typedef uint64_t  uint64;
    typedef int64_t   int64;
    #endif
#else
    // KISS. These are correct for many compilers.
    // This logic branch is used for compile of license generator on distributor web site.
    typedef signed char     int8;
    typedef unsigned char   uint8;
    typedef signed short    int16;
    typedef unsigned short  uint16;
    #if defined(ADI_TARGET_RT_64_BIT) && defined(ADI_TARGET_RT_LP64)
    typedef signed int      int32;
    typedef unsigned int    uint32;
    #else
    typedef signed long     int32;
    typedef unsigned long   uint32;
    #endif
    // 64 bit support is more suspect, do something that might work
    typedef signed long long    int64;
    typedef unsigned long long  uint64;
#endif

#ifdef CROSSTYPES_TYPEDEF_MAC_FROM_WIN
    // Mac flavour
    typedef int8	SInt8;
    typedef int16	SInt16;
    typedef int32	SInt32;
    typedef uint8	UInt8;
    typedef uint16	UInt16;
    typedef uint32	UInt32;
    #ifndef ADI_NO_INT64_T // KISS: currently assume if ADI_NO_INT64_T is set then not interested in 64.
    typedef int64	SInt64;
    typedef uint64	UInt64;
    #endif
    #undef CROSSTYPES_TYPEDEF_MAC_FROM_WIN
#endif


// KISS. These currently work as expected everywhere.
typedef float	float32;
typedef double	float64;

#if !defined(__MWERKS__)	// SfW compile uses MetroWerks, and has clashing Float32/64 from somewhere else (Movies.h?)
typedef float32	Float32;
typedef float64	Float64;
#endif


#if defined(ADI_TARGET_OS_MAC)
    // Things are complicated because we can easily get clashing definitions from commonly included headers. Look for
    // some interesting files and let them define the types the way they want. 
    // Of special note, MacTypes.h and stdint.h have same size but different types for 32 sizes.
        
    // Do the Mac flavours first
    #ifdef __MACTYPES__
        // <CarbonCore/MacTypes.h>
        // Gets pulled in by Carbon.h
        // Supplies full Mac flavours, somewhat by definition!
    #elif defined(ADI_HAS_STDINT_H)
        #include <stdint.h>
        typedef int8_t    SInt8;
        typedef int16_t   SInt16;
        typedef int32_t   SInt32;
        typedef int64_t   SInt64;
        typedef uint8_t   UInt8;
        typedef uint16_t  UInt16;
        typedef uint32_t  UInt32;
        typedef uint64_t  UInt64;
    #else
        // KISS, want to know more about other cases before deciding how to proceed.
        #error "Unexpected compile environment, extend as appropriate!"
    #endif
    
    // And now do the CfW flavours
    typedef SInt8    int8;
    typedef SInt16   int16;
    typedef SInt32   int32;
    typedef SInt64   int64;
    #ifdef _CSSMCONFIG_H_
        // <Security/cssmconfig.h>
        // Gets pulled in by Carbon.h
        // Supplies sint8, uint8, ...
        // In 10.4 and before uses MacTypes, in 10.5 and later uses stdint.h, cross fingers and go with the flow
        // even though may be getting different types for Mac/CfW flavours!!
    #else
        typedef UInt8   uint8;
        typedef UInt16  uint16;
        typedef UInt32  uint32;
        typedef UInt64  uint64;
    #endif
#endif  // ADI_TARGET_OS_MAC


#endif	// CROSSPLATFORM_CROSSTYPES_H
