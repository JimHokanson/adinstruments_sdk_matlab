/*
 *
 *      mex sdk_test.cpp ADIDatIOWin.lib
 *
 *
 */

#include "mex.h"
#include "ADIDatCAPI_mex.h"
#include <string>


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
    plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
    
    // edit([matlabroot '/extern/examples/mex/explore.c']);
    x = (int *) mxGetData(plhs[0]);
    
    option = mxGetScalar(prhs[0]);
    
    //option = mxGetPr(prhs[0])[0];
    
    if (option == 0)
    {
        
        //fileH  = ADI_FileHandle(0);

        result = ADI_OpenFile(path, &fileH, kOpenFileForReadOnly);

        //printf("Result: [s[%d]]
        //printf("Result: %x\n",result);

        if (result == 0)
        {
            printf("unused: %d\n",fileH->unused);
            //Size 4 - not sure if this will change to 8 ...
            //Might need to have a check ...
            //printf("pointer size: %d\n",sizeof(fileH));
            printf("pointer_value: %d\n",fileH);
        }
        x[0] = (int)fileH;
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