classdef (Hidden) comment_handle < handle
    %
    %   Class:
    %   adinstruments.comment_handle
    %
    %   TODO: Could add methods here which point to the SDK
    %
    properties
       pointer_value %Pointer to the a commenct accessor object in the mex 
       %code. This gets cast to ADI_CommentsHandle in the mex code.
       is_valid = false
       record
    end
    
    methods
        function obj = comment_handle(pointer_value,is_valid,record)
            %
            %   obj = adinstruments.comment_handle(pointer_value,is_valid)
            
           obj.pointer_value = pointer_value;
           obj.is_valid      = is_valid;
           obj.record        = record;
        end
        function delete(obj)
           adinstruments.sdk.closeCommentAccessor(obj.pointer_value);
        end
    end
    
    
end

