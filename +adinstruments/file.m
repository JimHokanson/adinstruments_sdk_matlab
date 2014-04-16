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
       records       %adinstruments.record
       channel_specs %adinstruments.channel
    end

    methods
        function obj = file(file_path,file_h)
           %
           %    Created by the sdk
           %
           %    See Also:
           %    
           
           obj.file_path   = file_path;
           
           obj.n_records  = adinstruments.sdk.getNumberOfRecords(file_h);
           obj.n_channels = adinstruments.sdk.getNumberOfChannels(file_h);
           
           %Get record objects
           %-------------------------------------------
           temp = cell(1,obj.n_records);
           
           for iRec = 1:obj.n_records
              %NOTE: pass in id as 0 based 
              temp{iRec} = adinstruments.record(iRec-1,file_h); 
           end
           
           obj.records = [temp{:}];
           
           %Get channel objects
           %-------------------------------------------
           temp = cell(1,obj.n_channels);
           
           for iChan = 1:obj.n_channels
              %NOTE: pass in id as 0 based 
              temp{iChan} = adinstruments.channel(file_h,iChan-1,obj.n_records);
           end
           
           obj.channel_specs = [temp{:}];           
        end
    end
    
end

