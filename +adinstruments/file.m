classdef file < sl.obj.display_class
    %
    %   Class:
    %   adinstruments.file
    %
    %   This is the root class for a Labchart file. It holds meta
    %   data and classes with more meta data. The channel classes can
    %   be used to actually get data.
    %
    %   JAH NOTE: This class was hidden to indicate that it should be
    %   constructed from readFile, but this screws up the class display :/
    %
    %   See Also:
    %   adinstruments.readFile
    
    properties
        file_path  %Full path to the file from which this class was populated.
    end
    
    properties
        n_records
        n_channels %# of channels in the file (across all records). This may
        %be reduced if some channels have no data and the input options to 
        %the constructor specify to remove empty channels.
        records       %adinstruments.record
        channel_specs %adinstruments.channel These classes hold information
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
            %    This should be created by adinstruments.readFile
            %
            %   Inputs:
            %   -------
            %   file_path : str
            %       The path of the file (for reference).
            %   file_h : 
            %       
            %   in : adinstruments.file_read_options
            %       Options for reading the file
            %
            %    See Also:
            %    adinstruments.readFile
            
            obj.file_path   = file_path;
            
            obj.n_records  = sdk.getNumberOfRecords(file_h);
            temp_n_channels = sdk.getNumberOfChannels(file_h);
            
            %Get record objects
            %-------------------------------------------
            temp = cell(1,obj.n_records);
            
            for iRec = 1:obj.n_records
                temp{iRec} = adinstruments.record(file_h,sdk,iRec);
            end
            
            obj.records = [temp{:}];
            
            %Get channel objects
            %-------------------------------------------
            temp = cell(1,temp_n_channels);
            
            for iChan = 1:temp_n_channels
                temp{iChan} = adinstruments.channel(file_h,sdk,iChan,obj.records);
            end
            
            obj.channel_specs = [temp{:}];
            
            if in.remove_empty_channels
                obj.channel_specs = obj.channel_specs.removeEmptyObjects();
            end
            
            obj.n_channels = length(obj.channel_specs);
        end
    end
    methods
        function summarizeRecords(obj)
            %NYI
            %For each record:
            %# of comments
            %which channels contain data
            %duration of the record
            keyboard
        end
        function chan = getChannelByName(obj,name,varargin)
            %
            %
            %   chan = ad_sdk.adinstruments.getChannelByName(obj,name,varargin)
            %
            %   See Also:
            %   adinstruments.channel.getChannelByName()
            
            in.case_sensitive = false;
            in.partial_match  = true;
            in = sl.in.processVarargin(in,varargin);
            
            temp = obj.channel_specs;
            if isempty(temp)
                error('Requested channel: %s, not found',name)
            end
            
            chan = temp.getChannelByName(name,in);
            
        end
    end
    
    %TODO: These should be in their own class
    %adinstruments.io.mat.file &
    %adinstruments.io.h5.file
    %
    %Currently the SDK takes care of the loading, which bridges the gap
    %of knowledge of the file contents ... i.e. this file knows write
    %contents but the SDK needs to know how to read
    %File Methods
    methods
        function save_path = exportToHDF5File(obj,save_path,conversion_options)
            %
            %   Exports contents to a HDF5 file.
            
            if nargin < 3 || isempty(conversion_options)
                conversion_options = adinstruments.h5_conversion_options;
            end
            
            if ~exist('save_path','var') || isempty(save_path)
               save_path = sl.dir.changeFileExtension(obj.file_path,'h5');
            end
            
            if strcmp(save_path,obj.file_path)
               error('Conversion path and file path are the same') 
            end
            
            if exist(save_path,'file')
               delete(save_path); 
            end
            
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
            %   This is rediculously SLOW. Unfortunately we don't have much
            %   control over how mat files are saved, even though the
            %   underlying HDF5 format provides tons of flexibility. To
            %   remedy this problem the HDF5 conversion code was created.
            
            if nargin < 3 || isempty(conversion_options)
                conversion_options = adinstruments.h5_conversion_options;
            end
            
            if ~exist('save_path','var') || isempty(save_path)
               save_path = sl.dir.changeFileExtension(obj.file_path,'mat');
            end
            
            if strcmp(save_path,obj.file_path)
               error('Conversion path and file path are the same') 
            end
            
            if exist(save_path,'file')
               delete(save_path); 
            end
            
            %http://www.mathworks.com/help/matlab/ref/matfile.html
            m = matfile(save_path);
            
            m.file_version = 1;
            m.file_meta    = struct('n_records',obj.n_records,'n_channels',obj.n_channels);
            
            obj.records.exportToMatFile(m,conversion_options);
            obj.channel_specs.exportToMatFile(m,conversion_options)
            
        end
    end
    
end

