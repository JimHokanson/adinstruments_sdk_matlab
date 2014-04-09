classdef channel < handle
    %
    %   Class: adinstruments.channel
    
    properties
       id 
       name
       units
       n_samples
       dt
       fs
    end
    
    properties (Hidden)
       n_records 
    end
    
    methods
        function obj = channel(file_h,id,n_records)
            %
            %   obj = adinstruments.channel(file_h,id,n_records)
            %   
            
           obj.id = id;
           obj.n_records = n_records;
           
           sdk = adinstruments.sdk;
           
           temp_tick_period = zeros(1,n_records);
           temp_n_samples   = zeros(1,n_records);
           temp_units       = cell(1,n_records);
           
           obj.name = sdk.getChannelName(file_h,id);
           
           for iRecord = 1:n_records
              temp_tick_period(iRecord) = sdk.getTickPeriod(file_h,iRecord-1,id);
              temp_n_samples(iRecord)   = sdk.getNSamplesInRecord(file_h,iRecord-1,id);
              temp_units{iRecord}       = sdk.getUnits(file_h,iRecord-1,id);
           end
           
           obj.units = temp_units;
           obj.n_samples = temp_n_samples;
           obj.dt = temp_tick_period;
           obj.fs = 1./(obj.dt);
           
        end
    end
    
end

