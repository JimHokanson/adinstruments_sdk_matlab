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
       closed = false
    end
    
    methods
        function obj = data_writer_handle(pointer_value)
            obj.pointer_value = pointer_value;
        end
        function close(obj)
            if ~obj.closed
                adi.sdk.closeWriter(obj.pointer_value)
                obj.closed = true;
            end 
        end
        function delete(obj)
            obj.close();
        end
    end
    
end

