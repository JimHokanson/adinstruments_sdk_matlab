/*
 *
 *      mex sdk_test.cpp ADIDatIOWin.lib
 *
 *      adinstruments.sdk.make_mex()
 */

#include "mex.h"
#include "ADIDatCAPI_mex.h"
#include <string>
#include <iostream>
#include <sstream>

ADI_FileHandle getFileHandle(const mxArray *prhs[])
{
    
    //TODO: Test code without this function, then add this and test
    
    int *input_file_handle;
    input_file_handle = (int *)mxGetData(prhs[1]);
    return ADI_FileHandle(input_file_handle[0]);
    
}

void getWCHAR(char *orig, wchar_t *new_string)
{
//http://msdn.microsoft.com/en-us/library/ms235631%28VS.80%29.aspx
    
//This is currently not used. I had problems with it. Just passing
//in a int16 array instead.
    
    size_t origsize = strlen(orig) + 1;
    const size_t newsize = 1000; //MS example uses 100, let's use 1000!
    size_t convertedChars = 0;
    wchar_t wcstring[newsize];
    mbstowcs_s(&convertedChars, wcstring, origsize, orig, _TRUNCATE);
    wcscat_s(wcstring, L" (wchar_t *)");
    new_string = wcstring;
}

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //Documentation of the calling forms is given within each if clause
    
    double function_option;   //Which function to call
    int *out_result; //Each function will return a result code as well as
    //possibly other values ...
    
    int *input_file_handle;
    int file_handle_value; //This will be needed for 
    //http://msdn.microsoft.com/en-us/library/ms235631%28VS.80%29.aspx
    
    ADIResultCode result;
    
    //http://stackoverflow.com/questions/4470553/initialization-parenthesis-vs-equals-sign
    ADI_FileHandle fileH(0); //Pointer to ADI_FileHandle__
    
    //TODO: This could change if 64 bit ...
    plhs[0]    = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
    out_result = (int *) mxGetData(plhs[0]);
    
    function_option = mxGetScalar(prhs[0]);
    
    if (function_option == 0)
    {
        //  ADI_OpenFile
        //  ===================================================
        //  [result_code,file_handle] = sdk_mex(0,file_path)
        
        wchar_t *w_file_path = (wchar_t *)mxGetData(prhs[1]);
        
        //Conversion of input string (char) to wchar_t for function call
        //char    *c_file_path = mxArrayToString(prhs[1]);
        //wchar_t *w_file_path = L"F:\\GSK\\140204 control cmg.adicht";
        
        //getWCHAR(c_file_path,w_file_path);
        
        //Why doesn't this print????
        //wprintf???
        //-----------------------------------
        //std::wostringstream wsout;
        //wsout << w_file_path << std::endl;
        //printf("path: %s",wsout.str().c_str());
        
        //http://stackoverflow.com/questions/6608942/how-can-cstring-be-passed-to-format-string-s
        //wprintf(L"Test: %s\n",w_file_path);
 
        result        = ADI_OpenFile(w_file_path, &fileH, kOpenFileForReadOnly);

        out_result[0] = result;

        int *fh_pointer;
        plhs[1]    = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
        fh_pointer = (int *) mxGetData(plhs[1]);
        if (result == 0)
            fh_pointer[0] = (int)fileH;
        else
            fh_pointer[0] = 0;
        
    }
    else if (function_option == 1)
    {
        //  ADI_GetNumberOfRecords
        //  ======================================================
        //  [result_code,n_records] = sdk_mex(1,file_handle)
        
        long nRecords = 0;
 
        //TODO: Make this a function ...
        input_file_handle = (int *)mxGetData(prhs[1]);
        fileH  = ADI_FileHandle(input_file_handle[0]);
        //-----------------------------------------
        
        
        
        result        = ADI_GetNumberOfRecords(fileH,&nRecords);
        out_result[0] = result;
        
        plhs[1]    = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
        long *p_nRecords;
        p_nRecords = (long *)mxGetData(plhs[1]);
        p_nRecords[0] = nRecords; 
        
    }
    else if (function_option == 2)
    {
        //DLLEXPORT ADIResultCode ADI_GetNumberOfChannels(ADI_FileHandle fileH, long* nChannels);
        //
        //ADI_GetNumberOfChannels
        //  ========================================================
        //  [result_code,n_channels] = sdk_mex(2,file_handle)
        
        long nChannels = 0;
        fileH          = getFileHandle(prhs);
        result         = ADI_GetNumberOfChannels(fileH,&nChannels);
        out_result[0]  = result;
        
        plhs[1]     = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
        long *p_nChannels;
        p_nChannels = (long *)mxGetData(plhs[1]);
        p_nChannels[0] = nChannels;
    }
    else if (function_option == 3)
    {
        fileH          = getFileHandle(prhs);
        //DLLEXPORT ADIResultCode ADI_GetNumTicksInRecord(ADI_FileHandle fileH, long record, long* nTicks);
    }
    else if (function_option == 4)
    {
        fileH          = getFileHandle(prhs);
        //DLLEXPORT ADIResultCode ADI_GetRecordTickPeriod(ADI_FileHandle fileH, long channel, long record, 
      //double* secsPerTick);
    }
    else if (function_option == 5)
    {
        fileH          = getFileHandle(prhs);
           //DLLEXPORT ADIResultCode ADI_GetNumSamplesInRecord(ADI_FileHandle fileH, long channel, long record, 
      //long* nSamples);
    }
    else if (function_option == 6)
    {
        fileH          = getFileHandle(prhs);
          //DLLEXPORT ADIResultCode ADI_CreateCommentsAccessor(ADI_FileHandle fileH, long record, 
      //ADI_CommentsHandle* commentsH); 
    }
    else if (function_option == 7)
    {
        fileH          = getFileHandle(prhs);
        //DLLEXPORT ADIResultCode ADI_CloseCommentsAccessor(ADI_CommentsHandle *commentsH);

    }
    else if (function_option == 8)
    {
        fileH          = getFileHandle(prhs);
      //   DLLEXPORT ADIResultCode ADI_GetCommentInfo(ADI_CommentsHandle commentsH, long *tickPos, long *channel, long *commentNum, wchar_t* text, 
      //long maxChars, long *textLen);
    }
    else if (function_option == 9)
    {
        fileH          = getFileHandle(prhs);
           // Advances the comments accessor to the next comment in the record
            // Params: ADI_CommentsHandle       - handle to a comments accessor
            // Returns kResultNoData if this accessor has reached the end of the comments in the record.
        
            //DLLEXPORT ADIResultCode ADI_NextComment(ADI_CommentsHandle commentsH);
    }
    else if (function_option == 10)
    {
        fileH          = getFileHandle(prhs);
          // Retrieves a block of sample data from the file into a buffer. Samples are in physical 
   // prefixed units.
   // Params: fileH    - ADI_FileHandle for the open file
   //         channel  - the channel containing the desired data (starting from 0)
   //         record   - the record containing the start position of the desired data 
   //                    (starting from 0)
   //         startPos - the start position as an offset from the start of the record (0)
   //         nLength  - number of elements (ticks/samples) to retrieve
   //         dataType - specifies the type of data (ticks or samples) to retrieve
   //         data     - pointer to a float array of 'nLength' in size    
   //                    e.g. float* data=(float*)malloc(sizeof(float*kDataSize)); [outparam]
   //         returned - the number of samples actually returned by the function (may be less 
   //                    than the amount requested) [outparam]
   // Return: a ADIResultCode for result of the operation
   //DLLEXPORT ADIResultCode ADI_GetSamples(ADI_FileHandle fileH, long channel, long record, long startPos, 
   //  ADICDataFlags dataType, long nLength, float* data, long* returned);
 
    }
    else if (function_option == 11)
    {
           // Retrieves the prefixed units of a channel, as a string.
   // Params: fileH     - ADI_FileHandle for the open file
   //         channel   - the unit's channel (starting from 0)
   //         record    - the unit's record (starting from 0)
   //         units     - buffer to receive null terminated text for the units name (optional, may be NULL) [outparam]
   //         maxChars  - the size of the text buffer in wchar_t s. The text will be truncated to fit in this size
   //         textLen   - receives the number of characters needed to hold the full comment text, 
   //                     even if parameter text is NULL (optional, may be NULL) [outparam]
   // Return: returns kResultBufferTooSmall if maxChars was too small to receive the full comment text.
   // Return: a ADIResultCode for result of the operation
    //    DLLEXPORT ADIResultCode ADI_GetUnitsName(ADI_FileHandle fileH, long channel, long record, wchar_t* units, 
    //  long maxChars, long *textLen);
    }
    else if (function_option == 12)
    {
         // Retrieves the name of a channel, as a string.
   // Params: fileH    - ADI_FileHandle for the open file
   //         channel  - the channel index (starting from 0)
   //         name    - null-terminated text for the name [outparam]
   //         maxChars - the size used for the buffer. Must not exceed this when copying 
   //                    text into the buffer
   //         textLen   - receives the number of characters needed to hold the full comment text, 
   //                     even if parameter text is NULL (optional, may be NULL) [outparam]
   // Return: returns kResultBufferTooSmall if maxChars was too small to receive the full title text.
   // Return: a ADIResultCode for result of the operation
   // DLLEXPORT ADIResultCode ADI_GetChannelName(ADI_FileHandle fileH, long channel, wchar_t* name, 
   //   long maxChars, long *textLen);  
    }
    else if (function_option == 13)
    {
        fileH          = getFileHandle(prhs);
        result         = ADI_CloseFile(&fileH);
        out_result[0]  = result;
    }
    
    else
    {
        out_result[0] = 3; 
    }

}