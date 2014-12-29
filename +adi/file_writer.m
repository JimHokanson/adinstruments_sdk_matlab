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
        file_path %Where we are writing to
        current_record   %NaN - not recording
        last_record = 0  %will always point to last record completed
        channels = {}
        current_channel_names
    end
    
    properties (Dependent)
        in_record_mode
    end
    
    methods
        function value = get.in_record_mode(obj)
            value = ~isnan(obj.current_record);
        end
    end
    
    properties (Hidden)
        file_h %
        data_writer_h %
    end
    
    methods
        function obj = file_writer(file_path,file_h,data_writer_h,is_new)
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
            
            %TODO: If the file is not new, read in the channel and record
            %specs from the file ...
            
        end
        function addComment(obj,tick_position,comment_string,varargin)
            %
            %
            %   Optional Inputs:
            %   ----------------
            %   record : (default, current record)
            %   channel : 
            
            in.record  = obj.current_record;
            in.channel = -1;
            in = adi.sl.in.processVarargin(in,varargin);
            adi.sdk.addComment(channel,record,tick_position,comment_string)
        end
        function deleteComment(obj,comment_number)
            adi.sdk.deleteComment(obj.file_h,comment_number)
        end
        function new_chan = addChannel(obj,id,name,fs,units)
            new_chan = adi.channel_writer(obj,id,name,fs,units);
            obj.channels{id} = new_chan;
        end
        function startRecord(obj,varargin)
            %
            %   Optional Inputs:
            %   ----------------
            
            in.old_record = [];
            in.trigger_time = now;
            in.fractional_seconds = 0;
            in.trigger_minus_rec_start = 0;
            in = adi.sl.in.processVarargin(in,varargin);
            
            %TODO: Check that a record isn't currently going
            
            if ~isempty(in.old_record)
                %TODO: Update in based on old record
            end
            
            in = rmfield(in,'old_record');
            
            adi.sdk.startRecord(obj.data_writer_h,in);
            obj.current_record = obj.last_record + 1;
        end
        function stopRecord(obj)
            obj.last_record = obj.current_record;
            obj.current_record = NaN;
            adi.sdk.finishRecord(obj.data_writer_h)
        end
        function save(obj)
           adi.sdk.commitFile(obj.data_writer_h) 
        end
        function close(obj)
            %This just closes the writer :/, not the file
           adi.sdk.closeWriter(obj.data_writer_h.pointer_value) 
        end
        %addChannel
    end
    
end

