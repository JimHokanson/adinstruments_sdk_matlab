classdef (Hidden) file < handle
    %
    %   Class:
    %   adi.file
    %
    %   ***** This object should be instantiated via adi.readFile  *****
    %
    %   This is the root class for a Labchart file. It holds meta
    %   data and classes with more meta data. The channel classes can
    %   be used to actually get data.
    %
    %   See Also:
    %   adi.readFile
    
    properties
        file_path  %Full path to the file from which this class was populated.
    end
    
    properties (Hidden)
        file_h
    end
    
    properties
        n_records
        n_channels %Number of channels in the file (across all records).
        %This may be reduced if some channels have no data and the
        %input options to the constructor specify to remove empty channels.
        records       %adi.record
        channel_specs %adi.channel These classes hold information
        %about each of the channels used.
    end
    
    properties (Dependent)
        channel_names
    end
    
    methods
        function value = get.channel_names(obj)
            temp = obj.channel_specs;
            if isempty(temp)
                value = {};
            else
                value = {temp.name};
            end
        end
    end
    
    %Constructor
    %--------------------------------
    methods
        function obj = file(file_path,file_h,sdk,in)
            %
            %   This should be created by adi.readFile
            %
            %   Inputs:
            %   -------
            %   file_path : str
            %       The path of the file (for reference).
            %   file_h : adi.file_handle
            %       A reference to the actual file.
            %   sdk: {adi.sdk, adi.h5_file_sdk, mat_file_sdk}
            %       Calls are made to the SDK to interact with the file.
            %   in : adi.file_read_options
            %       Options for reading the file.
            %
            %   See Also:
            %   adi.readFile
            
            obj.file_path = file_path;
            obj.file_h    = file_h;
            
            %Could try switching these to determine what is causing
            %the crash. Is it records or the first call to the sdk after
            %opening? Currently those 2 are the same. Flipping these 2
            %lines could disambiguate the situation.
            obj.n_records   = sdk.getNumberOfRecords(file_h);
            temp_n_channels = sdk.getNumberOfChannels(file_h);
            
            
            
            %Get record objects
            %-------------------------------------------
            temp = cell(1,obj.n_records);
            
            for iRec = 1:obj.n_records
                temp{iRec} = adi.record(file_h,sdk,iRec);
            end
            
            obj.records = [temp{:}];
            
            %Get channel objects
            %-------------------------------------------
            temp = cell(1,temp_n_channels);
            
            for iChan = 1:temp_n_channels
                temp{iChan} = adi.channel(file_h,sdk,iChan,obj.records,file_path);
            end
            
            obj.channel_specs = [temp{:}];
            
            if in.remove_empty_channels
                obj.channel_specs = obj.channel_specs.removeEmptyObjects();
            end
            
            if ~isempty(in.channels_remove)
                mask = ismember(in.channels_remove,obj.channel_names);
                if ~all(mask)
                    warning('JAH:adi:file:missing_remove_channel',...
                        'At least one of the channels specified to be removed were not in the file')
                    %Some of the channels that were requested to be removed
                    %are not in the file
                    %TODO: Print warning message
                end
                
                mask = ismember(obj.channel_names,in.channels_remove);
                obj.channel_specs(mask) = [];
            end
            
            if ~isempty(in.channel_name_mapping)
                old_names = in.channel_name_mapping(1:2:end);
                new_names = in.channel_name_mapping(2:2:end);
                [mask,loc] = ismember(old_names,obj.channel_names);
                %TODO: We can have an option to hide this
                if ~all(mask)
                    warning('JAH:adi:file:missing_remove_channel',...
                        'At least one of the channels specified to be renamed were not in the file')
                    %Some of the channels that were requested to be removed
                    %are not in the file
                    %TODO: Print warning message
                end
                for i = 1:length(mask)
                   if mask(i)
                      chan_obj = obj.channel_specs(loc(i));
                      chan_obj.name = new_names{i};
                   end
                end
                
            end
            
            obj.n_channels = length(obj.channel_specs);
        end
    end
    methods
        function output = isChannelInRecord(obj, channel_num, record)
            %
            %   output = isChannelInRecord(obj, channel_num, record)
            %
            %   Inputs
            %   ------
            %   1 based
            
            channel = obj.channel_specs(channel_num);
            output = channel.isValidForRecord(record);
        end
        function output = channelsInRecord(obj, record_number)
            % get a list of the channels in the given record_number with
            % samples recorded/valid
            
            mask = false(1,obj.n_channels);
            for i = 1:obj.n_channels
                mask(i) = obj.isChannelInRecord(i,record_number);
            end
            
            output = obj.channel_names(mask);
        end
        function all_comments = getAllComments(obj,varargin)
            %
            %   record : adi.record
            %
            %   Optional Inputs
            %   ---------------
            %   output :
            %       - 'obj' default
            %           Returns array of comment objects
            %       - 'table'
            %           Returns information as a table
            
            in.output = 'obj';
            in.use_datetime = false;
            in = adi.sl.in.processVarargin(in,varargin);
            
            all_records = obj.records;
            all_comments = [all_records.comments];
            switch in.output
                case 'obj'
                    %do nothing
                    %
                    %TODO: respect in.use_datetime
                    if in.use_datetime
                        error('Unsupported task')
                    end
                case 'table'
                    c = all_comments;
                    t = table;
                    t.text = string({c.str})';
                    t.id = [c.id]';
                    t.channel = [c.channel]';
                    t.record = [c.record]';
                    t.time = [c.time]';
                    t.absolute_time = [c.absolute_time]';
                    if in.use_datetime
                        t.absolute_time = datetime(t.absolute_time,'ConvertFrom','datenum');
                    end
                    all_comments = t;
            end
        end
        function summarizeRecords(obj)
            %x Not Yet Implemented
            % For each record:
            % # of comments
            % which channels contain data
            % duration of the record
            error('Not yet implemented')
            keyboard
        end
        function chan = getChannelByName(obj,channel_name,varargin)
            %x Returns channel object for a given channel name
            %
            %   chan = ad_sdk.adi.getChannelByName(obj,channel_name,varargin)
            %
            %   See Also:
            %   adi.channel.getChannelByName()
            
            in.case_sensitive = false;
            in.partial_match  = true;
            in.multiple_channel_rule = 'error';
            in = adi.sl.in.processVarargin(in,varargin);
            
            temp = obj.channel_specs;
            if isempty(temp)
                error('Requested channel: %s, not found',channel_name)
            end
            
            chan = temp.getChannelByName(channel_name,in);
        end
        function varargout = getChannelData(obj,...
                channel_number_1b_or_name, ...
                block_number_1b,varargin)
            %
            %
            %   This is really a shortcut call for the following:
            %   chan = obj.getChannelByName(name,varargin)
            %   data = chan.getData(block_number,varargin)
            %
            %   Optional Inputs
            %   ---------------
            %   See adi.channel.getData
            %
            %   See Also
            %   --------
            %   adi.channel.getData
            
            if isnumeric(channel_number_1b_or_name)
                spec = obj.channel_specs(channel_number_1b_or_name);
            else
                spec = obj.getChannelByName(channel_number_1b_or_name);
            end
            
            if nargout == 2
                [data,time] = spec.getData(block_number_1b,varargin{:});
                varargout{1} = data;
                varargout{2} = time;
            else
                data = spec.getData(block_number_1b,varargin{:});
                varargout{1} = data;
            end
        end
    end
    
    %TODO: These should be in their own class
    %adi.io.mat.file &
    %adi.io.h5.file
    %
    %Currently the SDK takes care of the loading, which bridges the gap
    %of knowledge of the file contents ... i.e. this file knows write
    %contents but the SDK needs to know how to read
    %File Methods
    methods
        function save_path = exportToHDF5File(obj,save_path,conversion_options)
            %x Exports contents to a HDF5 file.
            %
            %   This is similiar to the v7.3 mat files but by calling the
            %   HDF5 library functions directly we can control how the data
            %   are saved.
            %
            %   See Also:
            %   adi.record.exportToHDF5File
            %   adi.channel.exportToHDF5File
            
            if nargin < 3 || isempty(conversion_options)
                conversion_options = adi.h5_conversion_options;
            end
            
            if ~exist('save_path','var') || isempty(save_path)
                save_path = adi.sl.dir.changeFileExtension(obj.file_path,'h5');
            else
                save_path = adi.sl.dir.changeFileExtension(save_path,'h5');
            end
            
            if strcmp(save_path,obj.file_path)
                error('Conversion path and file path are the same')
            end
            
            if exist(save_path,'file')
                delete(save_path);
            end
            
            adi.sl.dir.createFolderIfNoExist(fileparts(save_path));
            
            %TODO: I'd eventually like to use the h5m library I'm writing.
            %This would change the calls to h5writteatt
            
            fobj = h5m.file.create(save_path);
            h5m.group.create(fobj,'file');
            
            %TODO: Replace with h5m library when ready
            h5writeatt(save_path,'/','version',1);
            h5writeatt(save_path,'/file','n_records',obj.n_records)
            h5writeatt(save_path,'/file','n_channels',obj.n_channels)
            
            obj.records.exportToHDF5File(fobj,save_path,conversion_options);
            obj.channel_specs.exportToHDF5File(fobj,save_path,conversion_options);
            
        end
        function save_path = exportToMatFile(obj,save_path,conversion_options)
            %
            %   Converts the file to a mat file.
            %
            %   See Also
            %   --------
            %   adi.convert
            %   adi.mat_conversion_options
            
            if nargin < 3 || isempty(conversion_options)
                conversion_options = adi.mat_conversion_options;
            end
            
            if ~exist('save_path','var') || isempty(save_path)
                save_path = adi.sl.dir.changeFileExtension(obj.file_path,'mat');
            else
                save_path = adi.sl.dir.changeFileExtension(save_path,'mat');
            end
            
            if strcmp(save_path,obj.file_path)
                error('Conversion path and file path are the same')
            end
            
            adi.sl.dir.createFolderIfNoExist(fileparts(save_path));
            
            if exist(save_path,'file')
                delete(save_path);
            end
            
            %http://www.mathworks.com/help/matlab/ref/matfile.html
            %m = matfile(save_path);
            
            m = struct;
            m.file_version = 1;
            m.file_meta = struct('n_records',obj.n_records,'n_channels',obj.n_channels);
            
            m = obj.records.exportToMatFile(m,conversion_options);
            m = obj.channel_specs.exportToMatFile(m,conversion_options);
            
            save(save_path,'-struct','m',conversion_options.version);
        end
    end
    
end

