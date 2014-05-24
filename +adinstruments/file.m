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
        n_channels
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
            %    See Also:
            %    adinstruments.readFile
            
            obj.file_path   = file_path;
            
            obj.n_records  = sdk.getNumberOfRecords(file_h);
            obj.n_channels = sdk.getNumberOfChannels(file_h);
            
            %Get record objects
            %-------------------------------------------
            temp = cell(1,obj.n_records);
            
            for iRec = 1:obj.n_records
                temp{iRec} = adinstruments.record(iRec,file_h);
            end
            
            obj.records = [temp{:}];
            
            %Get channel objects
            %-------------------------------------------
            temp = cell(1,obj.n_channels);
            
            for iChan = 1:obj.n_channels
                temp{iChan} = adinstruments.channel(file_h,iChan,obj.records);
            end
            
            obj.channel_specs = [temp{:}];
            
            if in.remove_empty_channels
               obj.channel_specs = obj.channel_specs.removeEmptyObjects(); 
            end
        end
    end
    methods
        function summarizeRecords(obj)
            %For each record:
            %# of comments
            %which channels contain data
            %duration of the record
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
        function exportToMatFile(obj,save_path)
           %NYI 
        end
    end
    
end

