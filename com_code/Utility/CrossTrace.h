#ifndef PORTABLE_CROSSTRACE_H
#define PORTABLE_CROSSTRACE_H

//#include "CrossPlatform/config/config.hpp"

#ifdef ADI_HAS_PRAGMA_ONCE
#pragma once
#endif

#include "Utility/CrossDebug.h"


/*
Provides cross platform trace macros.
By default these stream into cerr.
On some platforms implementation code will be needed to redirect cerr to
somewhere convenient. E.g. on Window one needs to implement a streambuf 
that outputs to OutputDebugString() inorder to see the messages in the 
VS output pane.
*/

// Rua has disabled this for now; there are lots of these in new portable ADIDatCore code.
// They aren't seen on LfW but they pollute the console in LfM!
#if ADIDEBUG
//#define ENABLE_TRACE 1 // BL39231: ADITRACE disabled
#endif

#ifdef ENABLE_TRACE
#undef ADITRACE
#define ADITRACE(msg) { std::wcerr << msg << std::endl; };
#else
#undef ADITRACE
#define ADITRACE(msg) ((void)0)
#endif // ENABLE_TRACE

//ADITRACEG is ADITRACE with grouping information (a string) that might be used (with a different implementation) to
//filter the TRACE output at run-time.
#ifdef ENABLE_TRACE
#undef ADITRACEG
#define ADITRACEG(group,msg) { std::wcerr << group << L" says: " << msg << std::endl; };
#else
#undef ADITRACEG
#define ADITRACEG(group,msg) ((void)0)
#endif // ENABLE_TRACE


//In Release builds, cerr should be re-directed to the boot log text file.
#define ADIBOOTLOG(msg) { std::wcerr << msg << std::endl; };


#endif
