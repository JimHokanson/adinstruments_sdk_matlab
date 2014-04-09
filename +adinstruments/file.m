classdef file < sl.obj.handle_light
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
        function obj = file(file_path,file_handle)
           %
           %    Created by the sdk
           
           obj.file_path   = file_path;
           obj.file_handle = file_handle;
           
           obj.n_records  = adinstruments.sdk.getNumberOfRecords(file_handle);
           obj.n_channels = adinstruments.sdk.getNumberOfChannels(file_handle);
           
           temp = cell(1,obj.n_records);
           
           for iRec = 1:obj.n_records
              %NOTE: pass in id as 0 based 
              temp{iRec} = adinstruments.record(iRec-1,file_handle); 
           end
           
           obj.records = [temp{:}];
           
           temp = cell(1,obj.n_channels);
           
           for iChan = 1:obj.n_channels
              temp{iChan} = adinstruments.channel(file_handle,iChan-1,obj.n_records);
           end
           
           keyboard
           
% % %            %Some more random testing, this will be moved ...
% % %            obj.temp_secs_per_tick = adinstruments.sdk.getTickPeriod(file_handle,3,0);
% % %            obj.temp_n_samples     = adinstruments.sdk.getNSamplesInRecord(file_handle,3,0);
% % %            
% % %            
% % %            n_ticks_in_record = adinstruments.sdk.getNTicksInRecord(file_handle,3);
% % %            
% % %            %JAH: At this point
% % %            keyboard
% % % 
% % %            wtf = adinstruments.sdk.getChannelData(file_handle,3,0,0,9143450,true);
           
        end
    end
    methods
          %This is causing a prog crash for some reason
        function delete(obj)
           %TODO: On delete, close file in mex
           
           %I think the problem is if the mex file clears then 
           %this calls the new mex file ...
           %- then you get a seg fault
           fprintf(2,'Deleting file object! (temp message, will remove)\n');
           adinstruments.sdk.closeFile(obj.file_handle);
        end
    end
    
end

