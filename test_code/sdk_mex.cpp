/*
 *
 *      mex sdk_mex.cpp ADIDatIOWin.lib
 *
 *      mex -v sdk_mex.cpp ADIDatIOWin64.lib
 *
 *
 *      TEST CALLING FORM:
 *      -------------------
 *      sdk_mex(0,[int16(file_path) 0]);
 *
 *
 *      adi.sdk.makeMex()
 *
 *      http://www.mathworks.com/help/matlab/matlab_external/passing-arguments-to-shared-library-functions.html
 *
 */

#define MAX_STRING_LENGTH 500 //I decided to avoid trying to deal with any
//sort of dynamic allocation. Since strings aren't that long, I'm fine
//hardcoding this value for now, assuming that this value is plenty large


#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <float.h>
#include "mex.h"
#include "ADIDatCAPI_mex.h"
#include <ctime>


//=========================================================================
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    
		//Call form 
		ADI_FileHandle fileH(0);

        wchar_t *w_file_path = (wchar_t *)mxGetData(prhs[1]);

        ADIResultCode result;
        
        result = ADI_OpenFile(w_file_path, &fileH, kOpenFileForReadOnly);
            
        mexPrintf("Result: %d\n",result);
        
        const int kBuffSize = 1024;
        long channel = 4;
		long record  = 3;
		long samplePos = 0;
		long retrieved = 0;
        
        float* dataBuffer = (float*)malloc(sizeof(float) * kBuffSize);
        
        ADI_GetSamples(fileH, channel, record, samplePos, kADICDataAtSampleRate, kBuffSize, dataBuffer, &retrieved);
                
        mexPrintf("Retrieved: %d\n",retrieved);
        
        free(dataBuffer);
		
		ADI_CloseFile(&fileH);

}