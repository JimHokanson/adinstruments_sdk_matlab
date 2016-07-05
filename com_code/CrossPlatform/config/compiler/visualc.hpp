// For documentation see also "CrossPlatform/config/conditionals.txt"

// See CVS for full change history. (Simplifies source mirrors, merging, and the clincher was Boost made the same decision!)

#ifndef _MSC_VER
	#error "Expecting Microsoft Visual C++ compiler"
#endif

#define ADI_MSC_VER _MSC_VER

//
// __int64 support, similar to boost/config/compiler/visualc.hpp
//
#if !defined(ADI_HAS_MS_INT64) && (_MSC_VER >= 1200) && defined(_MSC_EXTENSIONS)
	#define ADI_HAS_MS_INT64
#endif

//
// disable Win32 API's if compiler extentions are
// turned off, similar to boost/config/compiler/visualc.hpp
//
//#if !defined(ADI_DISABLE_WIN32) && !defined(_MSC_EXTENSIONS)
//	#define ADI_DISABLE_WIN32
//#endif

//
// FOUR_CHAR_CODE
//
#if defined(_M_IX86)  /* Visual Studio with Intel x86 target */
	#define FOUR_CHAR_CODE(x)           (x)
#endif

//
// ADI_HAS_PRAGMA_ONCE
//
#if _MSC_VER >= 1020
	#define ADI_HAS_PRAGMA_ONCE
#endif

//
// 64 bit
//
#ifdef _WIN64
   #define ADI_TARGET_RT_64_BIT 1
   #define ADI_TARGET_RT_LLP64
#endif
