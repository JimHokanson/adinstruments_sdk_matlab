// Deduce conditionals which have not been explicitly set

//==========
// This file contains parts of boost/config/suffix.hpp
// NB: In the copyright which follows, "this software" means just this file 
// and not the whole software of which this is but a small part.

//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.
//==========

// See CVS for full change history. (Simplifies source mirrors, merging, and the clincher was Boost made the same decision!)

//  This file is intended to be stable, and relatively unchanging.


// ADI_TARGET_OS_
// Most code will assume Mac/Win
// Some code will support Unix.
// Some code will support None. None is useful for compile targetting embedded systems which are none of the above!
#if !defined(ADI_TARGET_OS_WIN32) && !defined(ADI_TARGET_OS_MAC) && !defined(ADI_TARGET_OS_LIN) && !defined(ADI_TARGET_OS_NONE)
	#error "ADI_TARGET_OS configuration problem, too few set"
#endif
// Check that #ifdef x and #if x give same result, so explicitly compatible with Apple conventions
#if defined(ADI_TARGET_OS_WIN32) && !ADI_TARGET_OS_WIN32
	#error "ADI_TARGET_OS_WIN32 configuration problem, bad value"
#endif
#if defined(ADI_TARGET_OS_MAC) && !ADI_TARGET_OS_MAC
	#error "ADI_TARGET_OS_MAC configuration problem, bad value"
#endif
#if defined(ADI_TARGET_OS_LIN) && !ADI_TARGET_OS_LIN
	#error "ADI_TARGET_OS_LIN configuration problem, bad value"
#endif
#if defined(ADI_TARGET_OS_NONE) && !ADI_TARGET_OS_NONE
	#error "ADI_TARGET_OS_NONE configuration problem, bad value"
#endif
// Check not more than one set
#if ADI_TARGET_OS_WIN32 + ADI_TARGET_OS_MAC + ADI_TARGET_OS_LIN + ADI_TARGET_OS_NONE != 1
	#error "ADI_TARGET_OS configuration problem, too many set"
#endif

// ADI_TARGET_RT endian
// One must be set
#if !defined(ADI_TARGET_RT_LITTLE_ENDIAN) && !defined(ADI_TARGET_RT_BIG_ENDIAN)
	#error "ADI_TARGET_RT endian configuration problem, too few set"
#endif
// Check that #ifdef x and #if x give same result, so explicitly compatible with Apple conventions
#if defined(ADI_TARGET_RT_LITTLE_ENDIAN) && !ADI_TARGET_RT_LITTLE_ENDIAN
	#error "ADI_TARGET_RT_LITTLE_ENDIAN configuration problem, bad value"
#endif
#if defined(ADI_TARGET_RT_BIG_ENDIAN) && !ADI_TARGET_RT_BIG_ENDIAN
	#error "ADI_TARGET_RT_BIG_ENDIAN configuration problem, bad value"
#endif
// Check not more than one set
#if ADI_TARGET_RT_LITTLE_ENDIAN + ADI_TARGET_RT_BIG_ENDIAN != 1
	#error "ADI_TARGET_RT endian configuration problem, too many set"
#endif

// FOUR_CHAR_CODE
#if !defined(FOUR_CHAR_CODE)
	#define FOUR_CHAR_CODE(x)       (x)
#endif

// ADI_DISABLE_WIN32
#if !defined(ADI_DISABLE_WIN32) && !defined(ADI_TARGET_OS_WIN32)
	#define ADI_DISABLE_WIN32
#endif

// ADI_DISABLE_OWL
#if !defined(ADI_DISABLE_OWL) && !defined(CROSS_HAS_OWL) && defined(ADI_DISABLE_WIN32)
	#define ADI_DISABLE_OWL
#endif

// ADI_DISABLE_ATL
#if !defined(ADI_DISABLE_ATL) && !defined(CROSS_HAS_ATL) && defined(ADI_DISABLE_WIN32)
	#define ADI_DISABLE_ATL
#endif
