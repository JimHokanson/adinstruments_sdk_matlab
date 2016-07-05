//  Compiler configuration selection header file
//
// We do not support all these configurations, but list them so that this file 
// will hopefully not need to change if we choose to add support for more.


//==========
// This file is derived from boost/config/select_compiler_config.hpp
// NB: In the copyright which follows, "this software" means just this file 
// and not the whole software of which this is but a small part.

//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.
//==========

// See CVS for full change history. (Simplifies source mirrors, merging, and the clincher was Boost made the same decision!)

// locate which compiler we are using and define
// CROSS_COMPILER_CONFIG as needed: 

// NB: the include files listed here only exist for platforms we have used at ADInstruments!


#if defined __clang__
//  Clang
//  Test __clang__ before __GNUC__ as clang defines __GNUC__ too.
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/clang.hpp"

#elif defined __GNUC__
//  GNU C++
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/gcc.hpp"

#elif defined __COMO__
//  Comeau C++
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/comeau.hpp"

#elif defined __KCC
//  Kai C++
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/kai.hpp"

#elif defined __sgi
//  SGI MIPSpro C++
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/sgi_mipspro.hpp"

#elif defined __DECCXX
//  Compaq Tru64 Unix cxx
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/compaq_cxx.hpp"

#elif defined __ghs
//  Greenhills C++
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/greenhills.hpp"

#elif defined __BORLANDC__
//  Borland
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/borland.hpp"

#elif defined(__ICL) || defined(__ICC)
//  Intel
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/intel.hpp"

#elif defined  __MWERKS__
//  Metrowerks CodeWarrior
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/metrowerks.hpp"

#elif defined  __SUNPRO_CC
//  Sun Workshop Compiler C++
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/sunpro_cc.hpp"

#elif defined __HP_aCC
//  HP aCC
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/hp_acc.hpp"

#elif defined(__MRC__) || defined(__SC__)
//  MPW MrCpp or SCpp
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/mpw.hpp"

#elif defined(__IBMCPP__)
//  IBM Visual Age
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/vacpp.hpp"

#elif defined _MSC_VER
//  Microsoft Visual C++
//
//  This must remain the last #elif since some other vendors (Metrowerks, for
//  example) also #define _MSC_VER
#   define CROSS_COMPILER_CONFIG "CrossPlatform/config/compiler/visualc.hpp"

#elif defined (CROSS_ASSERT_CONFIG)
// this must come last - generate an error if we don't
// recognise the compiler:
#  error "Unknown compiler"

#endif

