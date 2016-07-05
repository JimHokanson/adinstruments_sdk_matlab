// Define useful conditional macros to make it easier to write code that can be used
// in multiple ADInstruments environments. (Especially CfM and CfW.)
//
// The conditionals are inspired by:
//	ConditionalMacros.h from Apple's Universal Interfaces, which strives for portable code, especially QuickTime.
//	compiler.h from CfW, which strives for portable CfW code between compilers.
//  boost/config.hpp from boost, which strives for portable standard C++ code.
//
// The conditionals are not documented here because this file is intended to be completely stable.
// See "CrossPlatform/config/conditionals.txt"

//==========
// This file is derived from boost/config.hpp
// NB: In the copyright which follows, "this software" means just this file 
// and not the whole software of which this is but a small part.
//
//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.
//==========

// See CVS for full change history. (Simplifies source mirrors, merging, and the clincher was Boost made the same decision!)

//  CAUTION: This file is intended to be completely stable -
//           DO NOT MODIFY THIS FILE!
//


#ifndef CROSSPLATFORM_CONFIG_HPP
#define CROSSPLATFORM_CONFIG_HPP

#define CROSS_ASSERT_CONFIG // We always want to know about unexpected configurations

// Include user override file first
#ifdef CROSS_USER_CONFIG
#  include CROSS_USER_CONFIG
#endif

// if we don't have a compiler config set, try and find one:
#if !defined(CROSS_COMPILER_CONFIG) && !defined(CROSS_NO_COMPILER_CONFIG) && !defined(CROSS_NO_CONFIG)
#  include "CrossPlatform/config/select_compiler_config.hpp"
#endif
// if we have a compiler config, include it now:
#ifdef CROSS_COMPILER_CONFIG
#  include CROSS_COMPILER_CONFIG
#endif

// if we don't have a std library config set, try and find one:
#if !defined(CROSS_STDLIB_CONFIG) && !defined(CROSS_NO_STDLIB_CONFIG) && !defined(CROSS_NO_CONFIG)
#ifdef __cplusplus  // Trying support for SOME C compiles, in which case stay away from C++ stdlib!
#  include "CrossPlatform/config/select_stdlib_config.hpp"
#endif
#endif
// if we have a std library config, include it now:
#ifdef CROSS_STDLIB_CONFIG
#  include CROSS_STDLIB_CONFIG
#endif

// if we don't have a platform config set, try and find one:
#if !defined(CROSS_PLATFORM_CONFIG) && !defined(CROSS_NO_PLATFORM_CONFIG) && !defined(CROSS_NO_CONFIG)
#  include "CrossPlatform/config/select_platform_config.hpp"
#endif
// if we have a platform config, include it now:
#ifdef CROSS_PLATFORM_CONFIG
#  include CROSS_PLATFORM_CONFIG
#endif

// Tidy up
#include "CrossPlatform/config/suffix.hpp"

// This looks a bit strange down here, but there is no point having it earlier since this file determines the conditional!
#ifdef ADI_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif	// CROSSPLATFORM_CONFIG_HPP
