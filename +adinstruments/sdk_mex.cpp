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

//TODO: It would be nice to template these ...
void setLongOutput(mxArray *plhs[],int index, long value)
{
    
    //Sets a single scalar value at the output location specified
    //  
    //  Inputs:
    //  ------------------------------------
    //  plhs  : The output data
    //  index : which index to set the data for (0 based)
    //  value : The value to assign to that particular output
    //
    //  Example: (In Matlab)
    // [a,b] = testFunction()
    // 
    //  Let's say we are trying to set b to 5
    //
    //  setLongOutput(plhs,1,5)
    
    //NOTE: We've hardcoded the output to be a scalar
    plhs[index] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
    long *p_value;
    p_value    = (long *)mxGetData(plhs[1]);
    p_value[0] = value;   
}

int getLongInput(const mxArray *prhs[], int index)
{
    //TODO: Finish documentation
    //
    //  
    //  getLongInput(prhs,2)
    //
    //  Assumes scalar value 
    
    int *p_value;
    p_value = (int *)mxGetData(prhs[index]);
    
    //Return only first value (assume only 1 value)
    return p_value[0]; 
}
//===================================================================

ADI_FileHandle getFileHandle(const mxArray *prhs[])
{
    
    //TODO: I can replace this now with a call to getLongInput ...
    int *input_file_handle;
    input_file_handle = (int *)mxGetData(prhs[1]);
    return ADI_FileHandle(input_file_handle[0]);
}

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //Documentation of the calling forms is given within each if clause
    
    ADI_FileHandle fileH(0);
    
    //TODO: This could change if 64 bit ...
    //-----------------------------------------------
    ADIResultCode result;
    int *out_result; //Each function will return a result code as well as
    //possibly other values ..
    plhs[0]    = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
    out_result = (int *) mxGetData(plhs[0]);
    
    
    //Which function to call
    double function_option = mxGetScalar(prhs[0]);   
    
    // 2 ADI_GetNumberOfChannels
    // 3 # of ticks in record
    // 4 tick period
    // 5 samples in record
    // 6 get comments accessor
    // 7 close comments accessor
    // 8 get cmment info
    // 9 next comment
    // 10 ADI_GetSamples
    // 11 ADI_GetUnitsName
    // 12 ADI_GetChannelName
    // 13 ADI_CloseFile
    
    
    if (function_option == 0)
    {
        //  ADI_OpenFile
        //  ===================================================
        //  [result_code,file_handle] = sdk_mex(0,file_path)
        
        wchar_t *w_file_path = (wchar_t *)mxGetData(prhs[1]);
         
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
        fileH         = getFileHandle(prhs);
        
        //ADIResultCode ADI_GetNumberOfRecords(ADI_FileHandle fileH, long* nRecords);
        result        = ADI_GetNumberOfRecords(fileH,&nRecords);
        out_result[0] = result;
        setLongOutput(plhs,1,nRecords);
        
    }
    else if (function_option == 2)
    {
        //  ADI_GetNumberOfChannels
        //  ========================================================
        //  [result_code,n_channels] = sdk_mex(2,file_handle)
        
        long nChannels = 0;
        fileH          = getFileHandle(prhs);
        
        //ADIResultCode ADI_GetNumberOfChannels(ADI_FileHandle fileH, long* nChannels);
        result         = ADI_GetNumberOfChannels(fileH,&nChannels);
        out_result[0]  = result;
        setLongOutput(plhs,1,nChannels);
    }
    else if (function_option == 3)
    {
        //  ADI_GetNumTicksInRecord
        //  ======================================================
        //  [result,n_ticks] = sdk_mex(3,file_handle,record_idx_0b)
        
        fileH          = getFileHandle(prhs);
        
        //0 or 1 based ...
        long record = getLongInput(prhs,2);
        long nTicks = 0;
        
        //ADIResultCode ADI_GetNumTicksInRecord(ADI_FileHandle fileH, long record, long* nTicks);
        result         = ADI_GetNumTicksInRecord(fileH,record,&nTicks);
        out_result[0]  = result;
        setLongOutput(plhs,1,nTicks);   
    }
    else if (function_option == 4)
    {
        fileH          = getFileHandle(prhs);
        //ADIResultCode ADI_GetRecordTickPeriod(ADI_FileHandle fileH, long channel, long record, double* secsPerTick);
        
        
    }
    else if (function_option == 5)
    {
        fileH          = getFileHandle(prhs);
        //ADIResultCode ADI_GetNumSamplesInRecord(ADI_FileHandle fileH, long channel, long record, long* nSamples);
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