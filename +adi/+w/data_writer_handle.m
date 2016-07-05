classdef (Hidden) data_writer_handle < handle
    %
    %   Class:
    %   adi.data_writer_handle
    %
    %   See Also:
    %   ---------
    %   adi.createFile
    %   adi.file_handle
    
    properties
       pointer_value
    end
    
    methods
        function obj = data_writer_handle(pointer_value)
            obj.pointer_value = pointer_value;
        end
        function delete(obj)
            %TODO: Why is this throwing an error on closing
            try
                adi.sdk.closeWriter(obj.pointer_value) 
            catch
            end
        end
    end
    
end

