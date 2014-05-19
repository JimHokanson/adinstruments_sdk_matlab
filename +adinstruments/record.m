classdef (Hidden) record < sl.obj.display_class
    %
    %   Class:
    %   adinstruments.record
    %
    %   A new record is created in a file whenever settings are changed, or
    %   whenever the users stops (then starts) a recording.
    
    properties
        id        %record number (1 based)
        n_ticks   %# of samples of highest sampling rate channel
        comments  %adinstruments.comment
        tick_dt   %The highest sampling rate of any channel in this record.
        tick_fs
    end
    
    properties (Hidden)
       file_h %adinstruments.file_handle
    end
    
    methods
        function obj = record(record_id,file_h)
           obj.file_h = file_h;
           obj.id     = record_id;
                      
           obj.n_ticks  = adinstruments.sdk.getNTicksInRecord(file_h,record_id);
           
           %This is not channel specific, the channel input is not actually
           %used:
           %http://forum.adinstruments.com/viewtopic.php?f=7&t=563
           obj.tick_dt  = adinstruments.sdk.getTickPeriod(file_h,record_id,1);
           obj.tick_fs  = 1./obj.tick_dt;
           
           obj.comments = adinstruments.sdkw.getAllCommentsForRecord(file_h,obj.id,obj.tick_dt);
        end
    end
    
end

