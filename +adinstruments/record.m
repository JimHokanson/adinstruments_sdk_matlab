classdef (Hidden) record < sl.obj.handle_light
    %
    %   Class:
    %   adinstruments.record
    
    properties
        record_id   %0 based id
        n_ticks     %# of samples of highest sampling rate channel
        comments    %adinstruments.comment
        dt_tick
        fs_tick
    end
    
    properties (Hidden)
       file_h %adinstruments.file_handle
    end
    
    methods
        function obj = record(record_id,file_h)
           obj.file_h    = file_h;
           obj.record_id = record_id;
           
           obj.n_ticks  = adinstruments.sdk.getNTicksInRecord(file_h,record_id);
           
           obj.comments = adinstruments.sdkw.getAllCommentsForRecord(file_h,record_id);
        end
    end
    
end

