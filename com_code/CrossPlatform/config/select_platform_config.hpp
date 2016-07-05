//  Platform configuration selection header file
//
// We do not support all these configurations, but list them so that this file 
// will hopefully not need to change if we choose to add support for more.

//==========
// This file is derived from boost/config/select_platform_config.hpp
// NB: In the copyright which follows, "this software" means just this file 
// and not the whole software of which this is but a small part.

//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.
//==========

// See CVS for full change history. (Simplifies source mirrors, merging, and the clincher was Boost made the same decision!)

// locate which platform we are on and define CROSS_PLATFORM_CONFIG as needed.
// Note that we define the headers to include using "header_name" not
// <header_name> in order to prevent macro expansion within the header
// name (for example "linux" is a macro on linux systems).

// NB: the include files listed here only exist for platforms we have used at ADInstruments!

#if defined(linux) || defined(__linux) || defined(__linux__)
// linux:
#  define CROSS_PLATFORM_CONFIG "CrossPlatform/config/platform/linux.hpp"

#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
// BSD:
#  define CROSS_PLATFORM_CONFIG "CrossPlatform/config/platform/bsd.hpp"

#elif defined(sun) || defined(__sun)
// solaris:
#  define CROSS_PLATFORM_CONFIG "CrossPlatform/config/platform/solaris.hpp"

#elif defined(__sgi)
// SGI Irix:
#  define CROSS_PLATFORM_CONFIG "CrossPlatform/config/platform/irix.hpp"

#elif defined(__hpux)
// hp unix:
#  define CROSS_PLATFORM_CONFIG "CrossPlatform/config/platform/hpux.hpp"

#elif defined(__CYGWIN__)
// cygwin is not win32:
#  define CROSS_PLATFORM_CONFIG "CrossPlatform/config/platform/cygwin.hpp"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
// win32:
#  define CROSS_PLATFORM_CONFIG "CrossPlatform/config/platform/win32.hpp"

#elif defined(__BEOS__)
// BeOS
#  define CROSS_PLATFORM_CONFIG "CrossPlatform/config/platform/beos.hpp"

#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
// MacOS
#  define CROSS_PLATFORM_CONFIG "CrossPlatform/config/platform/macos.hpp"

#elif defined(__IBMCPP__)
// IBM
#  define CROSS_PLATFORM_CONFIG "CrossPlatform/config/platform/aix.hpp"

#elif defined(__amigaos__)
// AmigaOS
#  define CROSS_PLATFORM_CONFIG "CrossPlatform/config/platform/amigaos.hpp"

#else

#  if defined(unix) \
      || defined(__unix) \
      || defined(_XOPEN_SOURCE) \
      || defined(_POSIX_SOURCE)

   // generic unix platform:

#  ifndef CROSS_HAS_UNISTD_H
#     define CROSS_HAS_UNISTD_H
#  endif

#  include "CrossPlatform/config/posix_features.hpp"

#  endif

#  if defined (CROSS_ASSERT_CONFIG)
      // this must come last - generate an error if we don't
      // recognise the platform:
#     error "Unknown platform"
#  endif

#endif


