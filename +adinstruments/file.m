classdef file < sl.obj.handle_light
    %
    %   Class:
    %   adinstruments.file
    
    properties
       file_path
    end
    
    properties
        
    end
    
    %Make read only?
    properties
       file_handle %int32 or int64 - depends on bits ... 
    end
    
    methods
        function delete(obj)
           %TODO: On delete, close file in mex
           adinstruments.sdk.closeFile(obj.file_handle);
        end
    end
    
end

