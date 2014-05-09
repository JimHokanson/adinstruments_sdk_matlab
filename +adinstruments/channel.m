classdef channel < sl.obj.display_class
    %
    %   Class:
    %   adinstruments.channel
    
    properties
        id
        name
        
        scale = 1 %NYI, on data retrieval use this to scale
        
        %These properties are on a per record basis ...
        units
        n_samples
        dt
        fs
        
    end
    
    properties (Hidden)
        n_records
        file_h
        tick_dt
    end
    
    methods
        function obj = channel(file_h,id,n_records,tick_dt)
            %x adinstruments.channel constructor
            %
            %   obj = adinstruments.channel(file_h,id,n_records,tick_dt)
            %
            %
            
            obj.id        = id;
            obj.n_records = n_records;
            obj.file_h    = file_h;
            obj.tick_dt   = tick_dt;
            
            sdk = adinstruments.sdk;
            
            temp_sample_period = zeros(1,n_records);
            temp_n_samples     = zeros(1,n_records);
            temp_units         = cell(1,n_records);
            
            obj.name = sdk.getChannelName(file_h,id);
            
            for iRecord = 1:n_records
                temp_sample_period(iRecord) = sdk.getSamplePeriod(file_h,iRecord,id);
                temp_n_samples(iRecord)     = sdk.getNSamplesInRecord(file_h,iRecord,id);
                temp_units{iRecord}         = sdk.getUnits(file_h,iRecord,id);
            end
            
            obj.units     = temp_units;
            obj.n_samples = temp_n_samples;
            obj.dt        = temp_sample_period;
            obj.fs        = 1./(obj.dt);
        end
        function printChannelNames(objs)
            %printChannelNames  Prints all channel names to the command window
            %
            %   printChannelNames(objs)
            
            for iObj = 1:length(objs)
                fprintf('%s\n',objs(iObj).name);
            end
        end
        function chan = getChannelByName(objs,name,varargin)
            %getChannelByName  Finds and returns a channel object by name
            %
            %    chan = getChannelByName(objs,name)
            %
            %    Inputs
            %    ===========================================================
            %    name :
            %
            %    Optional Inputs
            %    ===========================================================
            %    case_sensitive : (default false)
            %    partial_match  : (default true), if true the name
            %
            %    See Also:
            %    ad_sdk.adinstruments.getChannelByName

            in.case_sensitive = false;
            in.partial_match  = true;
            in = sl.in.processVarargin(in,varargin);
            
            all_names = {objs.name};
            if ~in.case_sensitive
                all_names = lower(all_names);
                name      = lower(name);
            end
            
            if in.partial_match
                I = find(cellfun(@(x) sl.str.contains(x,name),all_names));
            else
                %sl.str.findSingularMatch
                I = find(strcmp(all_names,name));
            end
            
            if isempty(I)
                error('Unable to find channel with name: %s',name)
            elseif length(I) > 1
                error('Multiple matches for channel name found')
            end
            chan = objs(I);
        end
        function getRecordPlotter(objs)
           %
           %
           %    I think for this method I wanted to be able to plot a
           %    single channel with some nice markup
        end
        function [data,time] = getAllData(obj,record,get_as_samples)
            %x Returns all data of the 
            %
            %    [data,time] = getAllData(obj,record,*get_as_samples)
            %
            %    Inputs
            %    ==========================================================
            %    get_as_samples: (default true), see description in:
            %        getDataSubset()
            
            if ~exist('get_as_samples','var') || isempty(get_as_samples)
                get_as_samples = true;
            end
            
            index = record;
            
            n_samples_get = obj.n_samples(index);
            if n_samples_get == 0;
                data = [];
                time = [];
            else
                data = adinstruments.sdk.getChannelData(...
                    obj.file_h,record,obj.id,1,n_samples_get,get_as_samples);
            end
            
            if nargout == 2
                time = (0:(length(data)-1)).*obj.dt(index);
            end
            
        end
        function data = getDataSubset(obj,record,start_sample,n_samples,get_as_samples)
            %
            %    data = getDataSubset(obj,record,start_sample,n_samples,*get_as_samples)
            %
            %    Inputs:
            %    =======================================================
            %    record       : record # from which to retrieve data
            %    start_sample : (1 based),
            %
            %    get_as_samples : (default true), If false then the channel
            %    is upsampled to the highest sampling rate used. The
            %    returned data is upsampled using (linear interp or sample &
            %    hold????)
            
            if ~exist('get_as_samples','var') || isempty(get_as_samples)
                get_as_samples = true;
            end
            
            %TODO: Check inputs ...
            %record
            %n_samples
            
            data = adinstruments.sdk.getChannelData(...
                obj.file_h,record,obj.id,start_sample,n_samples,get_as_samples);
        end
    end
    
end

