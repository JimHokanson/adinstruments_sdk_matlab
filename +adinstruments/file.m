classdef (Hidden) file < sl.obj.handle_light
    %
    %   Class:
    %   adinstruments.file
    
    properties
       file_path
    end
    
    properties
       n_records
       n_channels
       records
       channel_specs
    end
    
    properties
       %These will be changed ...
       temp_secs_per_tick
       temp_n_samples
    end
    
    %Make read only?
    properties
       file_handle %int32 or int64 - depends on bits ...
       comment_accessor
    end
    
    methods
        function obj = file(file_path,file_h)
           %
           %    Created by the sdk
           
           obj.file_path   = file_path;
           obj.file_handle = file_h;
           
           obj.n_records  = adinstruments.sdk.getNumberOfRecords(file_h);
           obj.n_channels = adinstruments.sdk.getNumberOfChannels(file_h);
           
           temp = cell(1,obj.n_records);
           
           for iRec = 1:obj.n_records
              %NOTE: pass in id as 0 based 
              temp{iRec} = adinstruments.record(iRec-1,file_h); 
           end
           
           obj.records = [temp{:}];
           
           temp = cell(1,obj.n_channels);
           
           for iChan = 1:obj.n_channels
              temp{iChan} = adinstruments.channel(file_h,iChan-1,obj.n_records);
           end
           
           obj.channel_specs = [temp{:}];           
        end
    end
    
end

