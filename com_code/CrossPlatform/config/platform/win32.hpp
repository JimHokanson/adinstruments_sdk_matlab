// For documentation see also "CrossPlatform/config/conditionals.txt"

// See CVS for full change history. (Simplifies source mirrors, merging, and the clincher was Boost made the same decision!)

#ifndef ADI_TARGET_OS_WIN32
	#define ADI_TARGET_OS_WIN32 1
#endif

// Default for Windows is little endian
#if !defined(ADI_TARGET_RT_LITTLE_ENDIAN) && !defined(ADI_TARGET_RT_BIG_ENDIAN)
	#define ADI_TARGET_RT_LITTLE_ENDIAN 1
#endif
