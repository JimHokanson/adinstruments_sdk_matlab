classdef file_writer < handle
    %
    %   Class:
    %   adi.file_writer
    %
    %   See Also:
    %   adi.sdk.commitFile
    %   adi.sdk.closeWriter
    %   adi.sdk.addComment
    %   adi.sdk.deleteComment
    %   adi.createFile
    
    %{
    TODO: I need to determine how this interface should be organized.
    I'd like to generate a set of commands that the user would execute then
    implement those commands.
    
    1) create file
    2) initialize channels
    3) start record
    4) add comments
    5) stop record
    6) repeat steps 2 - 5
    7) commit and close file - ??? does it help to commit more frequently?
    
    %}
    properties
        file_path
        current_record
        current_channel_names
    end
    
    properties (Hidden)
        file_h
        data_writer_h
    end
    
    methods
        function obj = file_writer(file_path,file_h,data_writer_h)
            %
            %   Call adi.createFile() to initialize this object
            %   
            %   obj = adi.file_writer(file_path,file_h)
            %
            %   See Also:
            %   adi.createFile
            
            obj.file_path = file_path;
            obj.file_h = file_h;
            obj.data_writer_h = data_writer_h;
            
        end
        function addComment()
           adi.sdk.addComment(channel,record,tick_position,comment_string) 
        end
        function deleteComment()
            
        end
        %methods 
        %addRecord
        %addChannel
    end
    
end

