classdef (Hidden) file_writer < handle
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
        current_record = NaN  %NaN - not recording
        last_record = 0  %will always point to last record completed
        record_durations %???? We can get this for
        record_dts %We'll log this for every record
        channels = {} %{adi.channel_writer}
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
    
    properties
       recorded_file 
    end
    
    methods 
        function value = get.recorded_file(obj)
           value = []; 
        end
    end
    
    properties (Hidden)
        is_new %Whether or not the file existed when created
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
            obj.is_new = is_new;
            if ~is_new
               temp_file = adi.file(file_path,file_h,adi.sdk,adi.file_read_options);
               obj.last_record = temp_file.n_records;
               %TODO: Do we want to instantiate writers for all the
               %channels ???? - Yes
               %
               
               records = temp_file.records;
               obj.record_durations = [records.duration];
               obj.record_dts = [records.tick_dt];
            end
        end
        function comment_number = addComment(obj,record,comment_time,comment_string,varargin)
            %
            %   comment_number = addComment(obj,tick_position,comment_string,varargin)
            %
            %   Optional Inputs:
            %   ----------------
            %   record : 
            %       -1 means current record
            %   
            %   channel : 
            
            in.channel = -1;
            in = adi.sl.in.processVarargin(in,varargin);
            
            %TODO: Check that record makes sense
            %If -1, check that we are in a record
            %otherwise, make sure record is between 1 and n records
            if record == -1
                record = obj.curent_record;
            end
            tick_position = round(comment_time/obj.record_dts(record));
            
            comment_number = adi.sdk.addComment(obj.file_h,in.channel,record,tick_position,comment_string);
        end
        function deleteComment(obj,comment_number)
            adi.sdk.deleteComment(obj.file_h,comment_number)
        end
        function new_chan = addChannel(obj,id,name,fs,units)
            %
            %   id :
            %       Channel number, starting at 1
            new_chan = adi.channel_writer(obj,id,name,fs,units);
            obj.channels{id} = new_chan;
        end
        function startRecord(obj,varargin)
            %
            %   Optional Inputs:
            %   ----------------
            %
            %   I think 'old_record' was meant to allow instantiating
            %   things based on the previous record
            
            in.record_to_copy = [];
            %What are the units on trigger time???
            %This should probably be afer the last record, rather than now
            in.trigger_time = [];
            in.fractional_seconds = 0;
            in.trigger_minus_rec_start = 0;
            in = adi.sl.in.processVarargin(in,varargin);
            
            if obj.in_record_mode
                error('Unable to start a record when in record mode already')
            end
            
            obj.current_record = obj.last_record + 1;
            
            if ~isempty(in.record_to_copy)
               %TODO: Populate in based on these properties ... 
            end
            in = rmfield(in,'record_to_copy');
            
            if isempty(in.trigger_time)
                %If record 2, add duration of record 1 to this value
                if obj.current_record > 1
                    %Add duration of last record to last record start time
                else
                    in.trigger_time = sl.datetime.matlabToUnix(now);
                end
            end

            all_chans = [obj.channels{:}];
            
            all_chans.initializeRecord(obj.current_record);
            
            adi.sdk.startRecord(obj.data_writer_h,in);
            
            
            
            
            %TODO: Check if the channel is enabled or not for determining
            %which has the highest fs
            highest_fs = max([all_chans.fs]);
            obj.record_dts = [obj.record_dts 1/highest_fs];
        end
        function stopRecord(obj)
            obj.last_record = obj.current_record;
            obj.current_record = NaN;
            adi.sdk.finishRecord(obj.data_writer_h)
            
            %TODO: Get duration. I'm not sure how Labchart is doing
            %this when the channels disagree with each other ...
            
            obj.record_durations = [obj.record_durations NaN];
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

