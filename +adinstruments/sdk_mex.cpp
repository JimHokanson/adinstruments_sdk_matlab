/*
 *
 *      mex sdk_test.cpp ADIDatIOWin.lib
 *
 *
 */

#include "mex.h"
#include "ADIDatCAPI_mex.h"
#include <string>
#include <iostream>
#include <sstream>

void getWCHAR(char *orig, wchar_t *new_string)
{
//http://msdn.microsoft.com/en-us/library/ms235631%28VS.80%29.aspx
    
    
    
    size_t origsize = strlen(orig) + 1;
    const size_t newsize = 1000; //MS example uses 100, let's use 1000!
    size_t convertedChars = 0;
    wchar_t wcstring[newsize];
    mbstowcs_s(&convertedChars, wcstring, origsize, orig, _TRUNCATE);
    wcscat_s(wcstring, L" (wchar_t *)");
    new_string = wcstring;
}

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray*prhs[] )
{
    
    double option;
    long nRecords = 0;
    //long *nChannels;
    int *x, *y;
    int file_handle_value;
    //http://msdn.microsoft.com/en-us/library/ms235631%28VS.80%29.aspx
    
    //http://www.mathworks.com/matlabcentral/newsreader/view_thread/286207
    //C:\Data\GSK\Wistar Control\Control CMG\140204
    //std::string temp = "C:\\Data\\GSK\\Wistar Control\\Control CMG\\140204\\140204 control cmg.adicht";
    //std::string temp = "140204 control cmg.adicht";
    //wchar_t* path = (wchar_t*)temp.c_str();
    wchar_t *path = L"C:\\Data\\GSK\\Wistar Control\\Control CMG\\140204\\140204 control cmg.adicht";
    
    ADIResultCode result;
    
    
    //http://stackoverflow.com/questions/4470553/initialization-parenthesis-vs-equals-sign
    ADI_FileHandle fileH(0); //Pointer to ADI_FileHandle__
    
    //Outputs
    //===================================
    //TODO: This could change if 64 bit ...
    plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
    
    // edit([matlabroot '/extern/examples/mex/explore.c']);
    x = (int *) mxGetData(plhs[0]);
    
    option = mxGetScalar(prhs[0]);
    
    //option = mxGetPr(prhs[0])[0];
    
    if (option == 0)
    {
        //  ADI_OpenFile
        //
        //  [file_handle,str] = sdk_mex(0,file_path)
        //
        //  
        
        char *c_file_path = mxArrayToString(prhs[1]);
        wchar_t *w_file_path;
        
        getWCHAR(c_file_path,w_file_path);
        
        //Why doesn't this print????
        //-----------------------------------
        //std::wostringstream wsout;
        //wsout << w_file_path << std::endl;
        //printf("path: %s",wsout.str().c_str());
        
 
        result = ADI_OpenFile(path, &fileH, kOpenFileForReadOnly);

        if (result == 0)
        {
            printf("unused: %d\n",fileH->unused);
            //TODO: Implement pointer size checking
            printf("pointer_value: %d\n",fileH);
            x[0] = (int)fileH;
        }
        else {
          //TODO: return error msg as well ...   
          x[0] = 0   
        }
        
    }
    else if (option == 1)
    {
        //TODO: Make this a function ...
        y = (int *)mxGetData(prhs[1]);
        file_handle_value = y[0];
        fileH  = ADI_FileHandle(file_handle_value);
        //-----------------------------------------
        printf("pointer_value: %d\n",fileH);
        
        result = ADI_GetNumberOfRecords(fileH,&nRecords);
        if (result == 0)
        {
            printf("Hooray\n");
            printf("Result: %d, nRecords: %d\n",result,nRecords);
        }
        else 
        {
            printf("Result 2: %x\n",result);
        }
        
        x[0] = 1;
    }
    else
    {
        x[0] = 3; 
    }
    
    
    
    
    //result = ADI_GetNumberOfRecords(fileH,nRecords);
    //printf("Result: %d\n",result);
    //printf("Result: %d, nRecords: %d\n",result,*nRecords);
    
    
    //DLLEXPORT ADIResultCode ADI_GetNumberOfRecords(ADI_FileHandle fileH, long* nRecords);
    
    //ADIResultCode ADI_CloseFile(ADI_FileHandle* fileH);

}