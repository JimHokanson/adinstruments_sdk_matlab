classdef (Hidden) file_handle < sl.obj.display_class
    %
    %   Class:
    %   adi.file_handle
    %
    %   This class is simply meant to hold the reference to an open file.
    %   When no one holds it the file will be closed.
    
    properties
        pointer_value %Pointer to the file object in the mex code. This gets
        %cast to ADI_FileHandle in the mex code.
    end
    
    methods
        function obj = file_handle(pointer_value)
            obj.pointer_value = pointer_value;
        end
        function delete(obj)
            %
            %
            
            %adi.sdk.closeFile(obj.pointer_value);
        end
    end
    
end

