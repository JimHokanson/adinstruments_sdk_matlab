classdef (Hidden) data_writer_handle < handle
    %
    %   Class:
    %   adinstruments.data_writer_handle
    
    properties
       pointer_value
    end
    
    methods
        function obj = data_writer_handle(pointer_value)
            obj.pointer_value = pointer_value;
        end
    end
    
end

