classdef sdkw
    %
    %   Class: adinstruments.sdkw
    %
    %   sdkw => sdk wrapper   
    %
    %   These are meant to be methods that the sdk does not implement but
    %   that are relatively straightforward, which you might sort of expect
    %   to be SDK methods.
    
    properties 
    end
    
    methods (Static)
        function comments = getAllCommentsForRecord(file_handle,record_0b)
            %
            %
            %   comments = adinstruments.sdkw.getAllCommentsForRecord(file_handle,record_0b)
            %
            
            %TODO: Add sort by time or id 
            
            MAX_NUMBER_COMMENTS = 1000; %NOTE: Overflow of this value
            %just causes things to slow down, not a critical error
            
            sdk = adinstruments.sdk;
            
            temp_comments_ca = cell(1,MAX_NUMBER_COMMENTS);
            comments_h = sdk.getCommentAccessor(file_handle,record_0b);
            
            %NOTE: If the above call fails, it returns 0, let's change that
            %interface, create two outputs ...
            
            %TODO: Replace with object and prop for testing ...
            if comments_h == 0
               comments = [];
               return
            end
            
            %Once the accessor is retrieved, the first comment can be
            %accessed.
            temp_comments_ca{1} = sdk.getCommentInfo(comments_h);
            
            cur_comment_index = 1;
            while sdk.advanceComments(comments_h)
               cur_comment_index = cur_comment_index + 1;
               %fprintf(2,'Getting comment: %d\n',cur_comment_index);
               temp_comments_ca{cur_comment_index} = sdk.getCommentInfo(comments_h);
            end
            
            comments = [temp_comments_ca{1:cur_comment_index}];
            
            adinstruments.sdk.closeCommentAccessor(comments_h);
        end
    end
    
end

