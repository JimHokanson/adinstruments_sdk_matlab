classdef (Hidden) comment_handle < handle
    %
    %   Class:
    %   adinstruments.comment_handle
    %
    %   This contains a handle that is needed by the SDK to get comments
    %   for a particular record. Methods in this class can be used to
    %   extract actual comments from a record.
    %
    %   See Also:
    %   adinstruments.comment
    
    
    properties
       pointer_value %Pointer to the a commenct accessor object in the mex 
       %code. This gets cast to ADI_CommentsHandle in the mex code. This
       %shouldn't be changed ...
       
       is_valid = false %A handle may not be valid if there are no comments
       %for a given record
       record
       tick_dt
    end
    
    methods
        function obj = comment_handle(pointer_value,is_valid,record_id,tick_dt)
            %
            %   obj = adinstruments.comment_handle(pointer_value,is_valid)
            
           obj.pointer_value = pointer_value;
           obj.is_valid      = is_valid;
           obj.record        = record_id;
           obj.tick_dt       = tick_dt;
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

