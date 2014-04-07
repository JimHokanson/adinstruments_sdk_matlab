classdef record < sl.obj.handle_light
    %
    %   Class:
    %   adinstruments.record
    
    properties
        record_id %0 based id
        n_ticks
    end
    
    properties (Hidden)
       file_handle 
    end
    
    methods
        function obj = record(record_id,file_handle)
           obj.file_handle = file_handle;
           obj.record_id   = record_id;
           
           obj.n_ticks = adinstruments.sdk.getNTicksInRecord(file_handle,record_id);
        end
    end
    
end

