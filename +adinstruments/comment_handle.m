classdef (Hidden) comment_handle < handle
    %
    %   Class:
    %   adinstruments.comment_handle
    %
    %   TODO: Could add methods here which point to the SDK
    
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
            if ~obj.is_valid
                return
            end 
            
           adinstruments.sdk.closeCommentAccessor(obj.pointer_value);
        end
        function has_another_comment = advanceCommentPointer(obj)
           has_another_comment = adinstruments.sdk.advanceComments(obj); 
        end
        function cur_comment = getCurrentComment(obj)
           cur_comment = adinstruments.sdk.getCommentInfo(obj);
        end
        function close(obj)
           adinstruments.sdk.closeCommentAccessor(obj.pointer_value);
           obj.is_valid = false;
        end
    end
    
    
end

