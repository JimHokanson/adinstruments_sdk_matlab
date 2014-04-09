/*
 *
 *      mex sdk_test.cpp ADIDatIOWin.lib
 *
 *      adinstruments.sdk.make_mex()
 */

#define MAX_STRING_LENGTH 500

#include "mex.h"
#include "ADIDatCAPI_mex.h"
#include <string>
#include <iostream>
#include <sstream>

void setDoubleOutput(mxArray *plhs[],int index, double value)
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
    plhs[index] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
    double *p_value;
    p_value    = (double *)mxGetData(plhs[1]);
    p_value[0] = value;
}

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
    p_value    = (long *)mxGetData(plhs[index]);
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

// void setHandle(mxArray *plhs[],int index, long value)
// {
//
//             int *fh_pointer;
//         plhs[1]    = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
//         fh_pointer = (int *) mxGetData(plhs[1]);
//         if (result == 0)
//             fh_pointer[0] = (int)fileH;
//         else
//             fh_pointer[0] = 0;
//
//
// }

ADI_FileHandle getFileHandle(const mxArray *prhs[])
{
    
    //TODO: I can replace this now with a call to getLongInput ...
    int *input_file_handle;
    input_file_handle = (int *)mxGetData(prhs[1]);
    return ADI_FileHandle(input_file_handle[0]);
}

ADI_CommentsHandle getCommentsHandle(const mxArray *prhs[])
{
    
    //TODO: I can replace this now with a call to getLongInput ...
    int *input_file_handle;
    input_file_handle = (int *)mxGetData(prhs[1]);
    return ADI_CommentsHandle(input_file_handle[0]);
}

wchar_t *getStringOutputPointer(mxArray *plhs[],int index)
{
    plhs[index] = mxCreateNumericMatrix(1,MAX_STRING_LENGTH,mxINT16_CLASS,mxREAL);
    return (wchar_t *)mxGetData(plhs[index]);
}


//=========================================================================
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //Documentation of the calling forms is given within each if clause
    
    ADI_FileHandle fileH(0);
    
    ADI_FileHandle fileH2(0);
    
    int fileH3;
    
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
        //  ADI_OpenFile   <>   openFile
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
        //  ADI_GetNumberOfRecords   <>   getNumberOfRecords
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
        //  ADI_GetNumberOfChannels   <>   getNumberOfChannels
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
        //  ADI_GetNumTicksInRecord   <>   getNTicksInRecord
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
        //  ADI_GetRecordTickPeriod  <>  getTickPeriod
        //  =========================================================
        //  [result,s_per_tick] = sdk_mex(4,file_handle,record_idx_0b,channel_idx_0b)
        
        fileH          = getFileHandle(prhs);
        
        long record  = getLongInput(prhs,2);
        long channel = getLongInput(prhs,3);
        double secsPerTick = 0;
        
        //ADIResultCode ADI_GetRecordTickPeriod(ADI_FileHandle fileH, long channel, long record, double* secsPerTick);
        out_result[0] = ADI_GetRecordTickPeriod(fileH,channel,record,&secsPerTick);
        setDoubleOutput(plhs,1,secsPerTick);
        
    }
    else if (function_option == 5)
    {
        //  ADI_GetNumSamplesInRecord  <>  getNSamplesInRecord
        //  ========================================================
        //  [result_code,n_samples] = sdk_mex(5,file_handle,record_idx_0b,channel_idx_0b);
        
        fileH          = getFileHandle(prhs);
        
        long record   = getLongInput(prhs,2);
        long channel  = getLongInput(prhs,3);
        long nSamples = 0;
        
        //ADIResultCode ADI_GetNumSamplesInRecord(ADI_FileHandle fileH, long channel, long record, long* nSamples);
        out_result[0] = ADI_GetNumSamplesInRecord(fileH,channel,record,&nSamples);
        setLongOutput(plhs,1,nSamples);
    }
    else if (function_option == 6)
    {
        //  ADI_CreateCommentsAccessor  <>  getCommentAccessor
        //  ========================================================
        //  [result_code,comments_h] = sdk_mex(6,file_handle,record_idx_0b);
        
        ADI_CommentsHandle commentsH(0);
        fileH         = getFileHandle(prhs);
        long record   = getLongInput(prhs,2);
        
        //ADIResultCode ADI_CreateCommentsAccessor(ADI_FileHandle fileH, long record, ADI_CommentsHandle* commentsH);
        result = ADI_CreateCommentsAccessor(fileH,record,&commentsH);
        out_result[0] = result;
        
        int *p_c;
        plhs[1]    = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
        p_c = (int *) mxGetData(plhs[1]);
        if (result == 0)
            p_c[0] = (int)commentsH;
        else
            p_c[0] = 0;
    }
    else if (function_option == 7)
    {
        //  ADI_CloseCommentsAccessor   <>   closeCommentAccessor
        //  ========================================================
        //  result_code = sdk_mex(7,comments_h);
        
        ADI_CommentsHandle commentsH = getCommentsHandle(prhs);
        
        //ADIResultCode ADI_CloseCommentsAccessor(ADI_CommentsHandle *commentsH);
        out_result[0] = ADI_CloseCommentsAccessor(&commentsH);
    }
    else if (function_option == 8)
    {
        //  ADI_GetCommentInfo   <>   getCommentInfo
        //  ====================================================
        //  [result_code,comment_string,comment_length,tick_pos,channel,comment_num] = sdk_mex(8,comment_h)
        
        
        ADI_CommentsHandle commentsH = getCommentsHandle(prhs);
        
        wchar_t *messageOut = getStringOutputPointer(plhs,1);
        long tickPos    = 0;
        long channel    = 0;
        long commentNum = 0;
        long textLen    = 0;
        
        
       //ADIResultCode ADI_GetCommentInfo(ADI_CommentsHandle commentsH, long *tickPos, long *channel, long *commentNum, wchar_t* text,long maxChars, long *textLen);
       //          tickPos                 - receives the tick position of the comment in the record [outparam]
       //          commentNum              - receives the number of the comment [outparam]
       //          channel                 - receives the channel of the comment (-1 for all channel comments) [outparam]
       //          text                    - buffer to receive null terminated text for the comment (optional, may be NULL) [outparam]
       //          maxChars                - the size of the text buffer in wchar_t s. The text will be truncated to fit in this size
       //          textLen                 - receives the number of characters needed to hold the full comment text, 
       //                                    even if parameter text is NULL (optional, may be NULL) [outparam]
        
        out_result[0] = ADI_GetCommentInfo(commentsH,&tickPos,&channel,&commentNum,messageOut,MAX_STRING_LENGTH,&textLen);
    
        setLongOutput(plhs,2,textLen);
        setLongOutput(plhs,3,tickPos);
        setLongOutput(plhs,4,channel);
        setLongOutput(plhs,5,commentNum);
        
    }
    else if (function_option == 9)
    {
        
        //  ADI_NextComment  <>  advanceComments
        //  ==================================================
        //  result_code = adinstruments.sdk_mex(9,comments_h);
        //
        //  Returns kResultNoData if there are no more comments ...
        
        ADI_CommentsHandle commentsH = getCommentsHandle(prhs);

        //ADIResultCode ADI_NextComment(ADI_CommentsHandle commentsH);
        out_result[0] = ADI_NextComment(commentsH);
    }
    else if (function_option == 10)
    {
        //  ADI_GetSamples   <>
        //  =================================================
        
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
        //  ADI_GetUnitsName   <>
        //  =======================================
        
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
        //  ADI_GetChannelName   <>
        
        
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
    else if (function_option == 14)
    {
        //  ADI_GetErrorMessage
        //  ==============================================================
        //  err_msg = sdk_mex(14,error_code)
        
        long textLen        = 0;
        wchar_t *messageOut = getStringOutputPointer(plhs,1);
        
        ADIResultCode code  = (ADIResultCode)getLongInput(prhs,1);
        
        //ADIResultCode ADI_GetErrorMessage(ADIResultCode code, wchar_t* messageOut, long maxChars, long *textLen);
        out_result[0] = ADI_GetErrorMessage(code, messageOut, MAX_STRING_LENGTH, &textLen);        
        setLongOutput(plhs,2,textLen);
        
    }
    else
    {
        out_result[0] = 3;
    }
    
}