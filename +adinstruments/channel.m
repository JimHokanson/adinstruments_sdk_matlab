classdef (Hidden) channel < handle
    %
    %   Class: adinstruments.channel
    %
    %
    %   TODOs
    %   ===================================================
    %   1) The call to tick period needs to be replace with a call to
    %   getting the sampling frequency
    
    properties
       id 
       name
       
       %These properties are on a per record basis ...
       units
       n_samples
       dt
       fs
    end
    
    properties (Hidden)
       n_records
       file_h
    end
    
    methods
        function obj = channel(file_h,id,n_records)
            %
            %   obj = adinstruments.channel(file_h,id,n_records)
            %   
            
           obj.id = id;
           obj.n_records = n_records;
           obj.file_h = file_h;
           
           sdk = adinstruments.sdk;
           
           temp_sample_period = zeros(1,n_records);
           temp_n_samples     = zeros(1,n_records);
           temp_units         = cell(1,n_records);
           
           obj.name = sdk.getChannelName(file_h,id);
           
           for iRecord = 1:n_records
              temp_sample_period(iRecord) = sdk.getSamplePeriod(file_h,iRecord-1,id);
              temp_n_samples(iRecord)     = sdk.getNSamplesInRecord(file_h,iRecord-1,id);
              temp_units{iRecord}         = sdk.getUnits(file_h,iRecord-1,id);
           end
           
           obj.units     = temp_units;
           obj.n_samples = temp_n_samples;
           obj.dt        = temp_sample_period;
           obj.fs        = 1./(obj.dt);
        end
        function printChannelNames(objs)
           for iObj = 1:length(objs)
              fprintf('%s\n',objs(iObj).name); 
           end
        end
        function obj = getChannelByName(objs,name)
           %
           %    obj = getChannelByName(objs,name)
           %    
           
           I = find(strcmp({objs.name},name));
           if isempty(I)
               error('Unable to find channel with name: %s',name)
           elseif length(I) > 1
               error('Multiple matches for channel name found')
           end
           obj = objs(I);
        end
        function data = getAllData(obj,record,get_as_samples)
           %
           %    data = getAllData(obj,record,get_as_samples)
           %
           
           if ~exist('get_as_samples','var') || isempty(get_as_samples)
               get_as_samples = true;
           end
           
           n_samples_get = obj.n_samples(record + 1);
           if n_samples_get == 0;
               data = [];
           else
           
           data = adinstruments.sdk.getChannelData(...
                    obj.file_h,record,obj.id,0,n_samples_get,get_as_samples);
           end
        end
        function data = getDataSubset(obj,record,start_sample,n_samples,get_as_samples)
           %
           %    data = getData(obj,record,start_sample,n_samples,*get_as_samples)
           %
           %    Inputs:
           %    ================================
           %    get_as_samples : (default true)
           
           if ~exist('get_as_samples','var') || isempty(get_as_samples)
               get_as_samples = true;
           end
           
           %TODO: Check inputs ...
           
           data = adinstruments.sdk.getChannelData(...
                    obj.file_h,record,obj.id,start_sample,n_samples,get_as_samples);
        end
    end
    
end

