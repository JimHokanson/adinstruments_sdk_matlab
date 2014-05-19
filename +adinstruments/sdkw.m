classdef sdkw
    %
    %   Class: 
    %   adinstruments.sdkw
    %
    %   sdkw => sdk wrapper   
    %
    %   These are meant to be methods that the sdk does not implement but
    %   that are relatively straightforward, which you might sort of expect
    %   to be SDK methods.
    
    properties 
    end
    
    methods (Static)
        function comments = getAllCommentsForRecord(file_h,record_id,tick_dt)
            %
            %
            %   comments = adinstruments.sdkw.getAllCommentsForRecord(file_handle,record_obj)
            %
            %   Inputs
            %   -----------
            %   file_handle : adinstruments.file_handle
            %   record_id   : 
            %   tick_dt     : 
            %
            %   See Also:
            %   adinstruments.record
                        
            %NOTE: These comments seem to be returned ordered by time, not
            %by ID.
            
            MAX_NUMBER_COMMENTS = 1000; %NOTE: Overflow of this value
            %just causes things to slow down, it is not a critical error.
            
            sdk = adinstruments.sdk;
            
            temp_comments_ca = cell(1,MAX_NUMBER_COMMENTS);
            comments_h = sdk.getCommentAccessor(file_h,record_id,tick_dt);

            if ~comments_h.is_valid
               comments = [];
               return
            end
            
            %Once the accessor is retrieved, the first comment can be accessed.
            temp_comments_ca{1} = comments_h.getCurrentComment();
            
            cur_comment_index = 1;
            while comments_h.advanceCommentPointer()
               cur_comment_index = cur_comment_index + 1;
               temp_comments_ca{cur_comment_index} = comments_h.getCurrentComment();
            end
            
            comments = [temp_comments_ca{1:cur_comment_index}];
            
            comments_h.close();
        end
    end
    
end

