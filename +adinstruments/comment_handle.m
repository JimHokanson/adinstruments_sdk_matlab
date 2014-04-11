classdef comment_handle < handle
    %
    %   Class:
    %   adinstruments.comment_handle
    %
    %   TODO: Could add methods here which point to the SDK
    %
    properties
       pointer_value %Pointer to the a commenct accessor object in the mex 
       %code. This gets cast to ADI_FileHandle in the mex code.
    end
    
    methods
        function obj = file_handle(pointer_value)
           obj.pointer_value = pointer_value;
        end
        function delete(obj)
           adinstruments.sdk.closeFile(obj.pointer_value);
        end
    end
    
    
end

