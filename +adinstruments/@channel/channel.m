classdef channel < sl.obj.display_class
    %
    %   Class:
    %   adinstruments.channel
    
    properties
        id    %Internal number (1 based)
        name
        
        %These properties are on a per record basis ...
        %-----------------------------------------------
        units
        n_samples
        dt
        fs
        
    end
    
    properties (Hidden)
        n_records
        file_h
        tick_dt
        record_handles
        sdk
    end
    
    properties (Dependent)
       downsample_amount 
    end
    
    methods
        function value = get.downsample_amount(obj) 
           value = obj.dt./obj.tick_dt; 
        end
    end
    
    methods
        function obj = channel(file_h,sdk,channel_id,record_handles)
            %x adinstruments.channel constructor
            %
            %   obj = adinstruments.channel(file_h,id,n_records,tick_dt)
            %
            %
            
            obj.sdk            = sdk;
            obj.id             = channel_id;
            obj.n_records      = length(record_handles);
            obj.file_h         = file_h;
            obj.tick_dt        = [record_handles.tick_dt];
            obj.record_handles = record_handles;
            
            temp_sample_period = zeros(1,obj.n_records);
            temp_n_samples     = zeros(1,obj.n_records);
            temp_units         = cell(1,obj.n_records);
            
            obj.name = sdk.getChannelName(file_h,channel_id);
            
            for iRecord = 1:obj.n_records
                temp_sample_period(iRecord) = sdk.getSamplePeriod(file_h,iRecord,channel_id);
                temp_n_samples(iRecord)     = sdk.getNSamplesInRecord(file_h,iRecord,channel_id);
                temp_units{iRecord}         = sdk.getUnits(file_h,iRecord,channel_id);
            end
            
            obj.units     = temp_units;
            obj.n_samples = temp_n_samples;
            obj.dt        = temp_sample_period;
            obj.fs        = 1./(obj.dt);
        end
        function comment_objs = getRecordComments(obj,record_id)
           %x Small helper to get the comments for a given record
           
           %I'm not thrilled that this is here ...
           comment_objs = obj.record_handles(record_id).comments; 
        end
% % %         function idx_bounds = getIndexBoundsGivenTimeBounds(obj,time_bounds,record_id)
% % %            %
% % %            %    
% % %            %    This may or may not be used ...
% % %            
% % %            idx_bounds = [floor(time_bounds(1)/obj.dt(record_id)) ceil(time_bounds(2)/obj.dt(record_id))];
% % %            
% % %            %  data = getDataSubset(obj,record_id,idx_bounds(1),idx_bounds(2)-idx_bounds(1)+1,true);
% % %         end
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
        function objs_with_data = removeEmptyObjects(objs)
            %x Removes channels with no data in them
            
            n_objs    = length(objs);
            keep_mask = false(1,n_objs);
            for iObj = 1:n_objs
                keep_mask(iObj) = sum(objs(iObj).n_samples) ~= 0;
            end
            objs_with_data = objs(keep_mask);
        end
        
        %I'm working on getting rid of this ...
        %--------------------------------------------
        function pobjs = getChannelPlotter(objs)
            %x Returns a channel plotter object for plotting data nicely
            %
            %    I think for this method I wanted to be able to plot a
            %    single channel with some nice markup:
            %        - units
            %        - plot large data quickly
            %        - change gain
            %        - overlay comments
            %        -
            n_objs = length(objs);
            temp = cell(1,n_objs);
            for iObj = 1:n_objs
                temp{iObj} = adinstruments.channel_plotter(objs(iObj));
            end
            
            pobjs = [temp{:}];
        end
        function data_object = getDataObject(obj,record_id,varargin)
           %    Returns a nice class that helps in working with the data
           %
           
           data_object = adinstruments.channel_data(obj,record_id,varargin{:});
        end
        function [data,time] = getAllData(obj,record_id,varargin)
            %x Returns all data of the
            %
            %    [data,time] = getAllData(obj,record,*get_as_samples)
            %
            %    Inputs
            %    ==========================================================
            %    get_as_samples: (default true), see description in:
            %        getDataSubset()
            
            in.get_as_samples = true;
            in.leave_raw      = false;
            in = sl.in.processVarargin(in,varargin);
            
            index = record_id;
            
            n_samples_get = obj.n_samples(index);
            if n_samples_get == 0;
                data = [];
                time = [];
            else
                data = obj.sdk.getChannelData(...
                    obj.file_h,record_id,obj.id,1,n_samples_get,...
                        in.get_as_samples,'leave_raw',in.leave_raw);
                
                if isrow(data)
                    data = data';
                end
            end
            
            if nargout == 2
                time = (0:(length(data)-1)).*obj.dt(index);
            end
            
        end
        function data = getDataSubset(obj,record,start_sample,n_samples,varargin)
            %x Returns a subset of the collected data
            %
            %    data = getDataSubset(obj,record,start_sample,n_samples,varargin)
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
            
            in.get_as_samples = true;
            in.leave_raw      = false;
            in = sl.in.processVarargin(in,varargin);
            
            
            %TODO: Check inputs ...
            %record
            %n_samples
            
            data = obj.sdk.getChannelData(...
                obj.file_h,record,obj.id,start_sample,n_samples,in.get_as_samples,'leave_raw',in.leave_raw);
            
                if isrow(data)
                    data = data';
                end
            
        end

        function exportToMatFile(objs,m)
            
           MAX_SAMPLES_AT_ONCE = 1e7;
           
           m.channel_version = 1;
           
           m.channel_meta = struct(...
               'id',        {objs.id},...
               'name',      {objs.name},...
               'units',     {objs.units},...
               'n_samples', {objs.n_samples},...
               'dt',        {objs.dt});
           
           %NOTE: It would be nice to be able to save the raw data ...
           %-----------------------------------
           m.data_version = 1;
           
           %NOTE: We can't go deeper than a single element :/
           
           n_objs    = length(objs);
           n_records = objs(1).n_records; %#ok<PROP>
           for iChan = 1:n_objs
               cur_chan = objs(iChan);
               for iRecord = 1:n_records %#ok<PROP>
                  cur_n_samples = cur_chan.n_samples(iRecord);
                  chan_name = sprintf('data__chan_%d_rec_%d',iChan,iRecord);
                  if cur_n_samples < MAX_SAMPLES_AT_ONCE
                     %(obj,record_id,get_as_samples) 
                     m.(chan_name) = cur_chan.getAllData(iRecord,'leave_raw',true);
                  else
                      
                     start_I = 1:MAX_SAMPLES_AT_ONCE:cur_n_samples;
                     end_I   = MAX_SAMPLES_AT_ONCE:MAX_SAMPLES_AT_ONCE:cur_n_samples;
                     
                     if length(end_I) < length(start_I)
                         end_I(end+1) = cur_n_samples; %#ok<AGROW>
                     end
                     
                     m.(chan_name)(cur_n_samples,1) = 0; %Initialize output
                     for iChunk = 1:length(start_I)
                        cur_start = start_I(iChunk);
                        cur_end   = end_I(iChunk);
                        n_samples_get = cur_end-cur_start + 1;
                        m.(chan_name)(cur_start:cur_end,1) = cur_chan.getDataSubset(iRecord,cur_start,n_samples_get,'leave_raw',true);
                     end
                  end
               end 
           end
        end
    end
    
end

