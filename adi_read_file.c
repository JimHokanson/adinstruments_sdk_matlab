/*



 */

#include "mex.h"


void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray*prhs[] )
{
    
	//A better implementation might use mexCallMATLAB
	
    //When displaying the output, instead of assigning to variable, there
    //is a > symbol which indicates which file in the stack is currently
    //active. We only need this one line, then the rest of the code can be
    //Matlab code.
	mexEvalString("DEBUG_STR_UNIQUE_NAME = evalc('dbstack');");
	
	mexEvalString("sl.stack.goDebugHelper(DEBUG_STR_UNIQUE_NAME);");
    
    //Since we create the variable in the caller, we clear it here.
    //Hopefully this variable name was not present before. Note, with 
    //better coding we do all of this in the mex workspace and guarantee
    //that we have no variable name conflicts.
    mexEvalString("clear('DEBUG_STR_UNIQUE_NAME');");
	
	//Example mexCallMATLAB code
   /*
    mexCallMATLAB(1,NULL,0, NULL, "disp");
    
    
    mexCallMATLAB(2, lhs, 1, &x, "eig");
    
    
    mexCallMATLAB(0,NULL,1, &lhs[1], "disp");
    
    
    invertd(mxGetPr(lhs[1]), mxGetPi(lhs[1]));
    
    mexCallMATLAB(0,NULL,1, &lhs[1], "disp");
    */
}